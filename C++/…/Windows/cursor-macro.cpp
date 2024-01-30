#define _WIN32_WINNT 0x0500

/* Import */
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>

#include <stdint.h>
#include <windows.h>

/* ... */
struct Point {
  struct Button final {
    static Button const EXTENDED[5];
    static Button const PRIMARY;
    static Button const SECONDARY;

    private:
      uint_least8_t value;

    public:
      constexpr Button() noexcept : value{} {}
      constexpr Button(uint_least8_t const value) noexcept : value{value} {}

      // ...
      constexpr operator uint_least8_t&      ()       noexcept { return this -> value; }
      constexpr operator uint_least8_t const&() const noexcept { return this -> value; }
  };

  uint_least8_t  buttons;
  uintmax_t      timestamp;
  uint_least16_t x;
  uint_least16_t y;

  // ...
  constexpr inline Point() noexcept :
    buttons{0x00u}, timestamp{0u}, x{0u}, y{0u}
  {}
};
  Point::Button const Point::Button::EXTENDED[5] = {0x04u, 0x08u, 0x10u, 0x20u, 0x40u};
  Point::Button const Point::Button::PRIMARY   {0x01u};
  Point::Button const Point::Button::SECONDARY {0x02u};

namespace Program {
  [[noreturn]] static void exit(int const) noexcept {
    std::fwrite("\r\n" "[Pointer Recorder]: Exiting...", sizeof(char const), 32u + 1u, stdout);
    std::exit(EXIT_SUCCESS); // --> std::free(points);
  }
}

// ... ->> Approximation of Coordinated Universal Time
constexpr uintmax_t timestamp(SYSTEMTIME const& time) noexcept {
  constexpr struct metric_t {
    WORD SYSTEMTIME::* const member;
    uint_least16_t     const maximum;
    uint_least16_t     const scale;
  } metrics[] = {
    {&SYSTEMTIME::wMilliseconds, 999u  , 1u},
    {&SYSTEMTIME::wSecond      , 59u   , 1000u},
    {&SYSTEMTIME::wMinute      , 59u   , 60u},
    {&SYSTEMTIME::wHour        , 23u   , 60u},
    {&SYSTEMTIME::wDay         , 31u   , 24u},
    {&SYSTEMTIME::wMonth       , 12u   , 31u},
    {&SYSTEMTIME::wYear        , 30827u, 12u}
  };

  constexpr std::size_t const metricCount  = sizeof(metrics) / sizeof(metric_t);
  uint_least16_t              metricIncrements[metricCount][metricCount] = {};
  uintmax_t                   milliseconds = 0u;

  /* ... */ {
    uintmax_t currentMaximumMilliseconds = 0u;
    uintmax_t recentMaximumMilliseconds  = 0u;

    // ...
    for (uint_least16_t (*increments)[metricCount] = metricIncrements + (sizeof(metricIncrements) / sizeof(uint_least16_t[metricCount])); increments-- != metricIncrements; )
    for (uint_least16_t *increment = *increments + (sizeof(*increments) / sizeof(uint_least16_t)); increment-- != *increments; ) *increment = 1u;

    for (metric_t const *metric = metrics; NULL != metric && metric != metrics + metricCount; metric += NULL != metric) {
      uintmax_t currentMaximumMetricMilliseconds = metric -> maximum;
      uintmax_t recentMaximumMetricMilliseconds  = currentMaximumMetricMilliseconds;

      // ...
      for (metric_t const *submetric = metrics; metric >= submetric; ++submetric) {
        recentMaximumMetricMilliseconds   = currentMaximumMetricMilliseconds;
        currentMaximumMetricMilliseconds *= submetric -> scale;

        // ...
        if (recentMaximumMetricMilliseconds >= currentMaximumMetricMilliseconds) {
          if (submetric -> scale != 1u)
          break;
        }

        if (recentMaximumMilliseconds >= currentMaximumMilliseconds + currentMaximumMetricMilliseconds) {
          for (++metric; metric-- != metrics; submetric = metrics + metricCount)
          while (submetric-- != metrics) {
            if (1u != metricIncrements[metric - metrics][submetric - metrics]) {
              metricIncrements[metric - metrics][submetric - metrics] = 1u;
              metric = metrics;

              break;
            }
          }

          metric = NULL;
          break;
        }

        // ...
        metricIncrements[metric - metrics][submetric - metrics] = submetric -> scale;
      }

      // ...
      recentMaximumMilliseconds   = currentMaximumMilliseconds;
      currentMaximumMilliseconds += currentMaximumMetricMilliseconds;
    }

    for (metric_t const *metric = metrics + metricCount; metric-- != metrics; ) {
      uintmax_t metricIncrement = 1u;

      for (uint_least16_t *increment = metricIncrements[metric - metrics] + (sizeof(metricIncrements[metric - metrics]) / sizeof(uint_least16_t)); increment-- != metricIncrements[metric - metrics]; )
      metricIncrement *= *increment;

      milliseconds += metricIncrement * time.*metrics[metric - metrics].member;
    }
  }

  return milliseconds;
}

/* Main */
int main() {
  std::size_t pointsCapacity  = 0u;
  bool        pointsFull      = false;
  std::size_t pointsLength    = 0u;
  std::size_t pointsNext      = 0u;
  Point      *points          = NULL;
  bool        recorderToggled = false;
  bool        recording       = true;

  // [Introduction]
  std::signal(SIGINT, &Program::exit);
  std::fputs("[Pointer Recorder]: Hit any key to begin recording pointer movements", stdout);

  if (EOF == std::fgetc(stdin)) {
    std::fputs("\r\n" "[Pointer Recorder]: Unable to record" "\r\n", stderr);
    Program::exit(EXIT_SUCCESS); // --> return EXIT_SUCCESS;
  }

  std::fputs("[Pointer Recorder]: " "Key 'Q' (or 'Esc') to exit and 'R' to record/ play back" "\r\n", stdout);
  while (true) {
    if (::GetAsyncKeyState(0x51) || ::GetAsyncKeyState(VK_ESCAPE))
    Program::exit(EXIT_SUCCESS);

    // ...
    if (::GetAsyncKeyState(0x52))
      recorderToggled = true;

    else if (recorderToggled) {
      pointsFull      = false;
      pointsNext      = 0u;
      pointsLength   *= recording; // ->> Record new `Point`s
      recorderToggled = false;
      recording       = false == recording;

      std::fprintf(stdout, "[Pointer Recorder]: %10.12s" "\r\n", recording ? "Recording..." : "Playing...");
      continue;
    }

    // [Recording]
    if (recording) {
      Point::Button buttons = 0x00u;
      POINT         cursorPosition {};
      Point        *point   = NULL != points ? std::launder(points + pointsNext) : NULL;
      SYSTEMTIME    systemTime     {};

      // ...
      if (FALSE != ::GetCursorPos(&cursorPosition)) {
        if (::GetAsyncKeyState(VK_LBUTTON )) buttons |= Point::Button::PRIMARY;
        if (::GetAsyncKeyState(VK_MBUTTON )) buttons |= Point::Button::EXTENDED[0];
        if (::GetAsyncKeyState(VK_RBUTTON )) buttons |= Point::Button::SECONDARY;
        if (::GetAsyncKeyState(VK_XBUTTON1)) buttons |= Point::Button::EXTENDED[1];
        if (::GetAsyncKeyState(VK_XBUTTON2)) buttons |= Point::Button::EXTENDED[2];

        // Reserve new `Point` if there are none, a button has been pressed/ released, or the cursor position has moved
        if (NULL == point || buttons != point -> buttons || (cursorPosition.x != point -> x || cursorPosition.y != point -> y)) {
          // ... ->> Allocate new `Point`
          if (pointsCapacity == pointsLength) {
            std::size_t const capacity = 0u != pointsCapacity ? (pointsCapacity * 5u) / 2u : sizeof(Point);
            void *const allocation     = std::realloc(points, capacity * sizeof(Point));

            // ...
            if (NULL == allocation) {
              pointsFull = true;
              pointsNext = 0u != pointsLength;
            }

            else {
              points         = static_cast<Point*>(allocation);
              pointsCapacity = capacity;
              pointsFull     = false;
            }
          }

          // ... ->> Add new or cycle through old `Point` locations
          if (false == pointsFull) {
            point      = new (points + pointsNext) Point {};
            pointsNext = ++pointsLength;
          }

          else for (Point *const end = points + (pointsLength - 1u), *iterator = points + (pointsNext == pointsLength ? pointsNext = 1u : ++pointsNext); end != iterator; ++iterator) {
            Point *const destinationPoint = std::launder(iterator + 0);
            Point *const sourcePoint      = std::launder(iterator + 1);

            // ...
            destinationPoint -> buttons   = sourcePoint -> buttons;
            destinationPoint -> timestamp = sourcePoint -> timestamp;
            destinationPoint -> x         = sourcePoint -> x;
            destinationPoint -> y         = sourcePoint -> y;
          }
        }

        // Record new `Point`
        if (NULL != point) {
          ::GetSystemTime(&systemTime);

          point -> buttons   = buttons;
          point -> timestamp = timestamp(systemTime);
          point -> x         = static_cast<uint_least16_t>(cursorPosition.x);
          point -> y         = static_cast<uint_least16_t>(cursorPosition.y);
        }
      }
    }

    // [Playing]
    else {
      Point const *currentPoint = points;
      static INPUT input {};
      Point const *recentPoint;

      // ...
      input.mi.time = 0u;
      input.type    = INPUT_MOUSE;

      for (Point const *const end = points + pointsLength, *iterator = points; end != iterator; ++iterator) {
        recentPoint        = currentPoint;
        input.mi.mouseData = 0u;
        input.mi.dy        = static_cast<LONG>(currentPoint -> y);
        input.mi.dx        = static_cast<LONG>(currentPoint -> x);
        input.mi.dwFlags   = MOUSEEVENTF_ABSOLUTE;
        currentPoint       = iterator;

        // ...
        if      (currentPoint -> buttons & Point::Button::PRIMARY) input.mi.dwFlags |= MOUSEEVENTF_LEFTDOWN;
        else if (recentPoint  -> buttons & Point::Button::PRIMARY) input.mi.dwFlags |= MOUSEEVENTF_LEFTUP;

        if      (currentPoint -> buttons & Point::Button::SECONDARY) input.mi.dwFlags |= MOUSEEVENTF_RIGHTDOWN;
        else if (recentPoint  -> buttons & Point::Button::SECONDARY) input.mi.dwFlags |= MOUSEEVENTF_RIGHTUP;

        if      (currentPoint -> buttons & Point::Button::EXTENDED[0]) input.mi.dwFlags |= MOUSEEVENTF_MIDDLEDOWN;
        else if (recentPoint  -> buttons & Point::Button::EXTENDED[0]) input.mi.dwFlags |= MOUSEEVENTF_MIDDLEUP;

        for (Point::Button const *const subend = Point::Button::EXTENDED + (sizeof(Point::Button::EXTENDED) / sizeof(Point::Button)), *subiterator = Point::Button::EXTENDED; subend != subiterator; ++subiterator) {
          Point::Button const button = *subiterator;

          if (Point::Button::EXTENDED[1] == button || Point::Button::EXTENDED[2] == button) {
            if      (currentPoint -> buttons & button) { input.mi.dwFlags |= MOUSEEVENTF_XDOWN; subiterator = NULL; }
            else if (recentPoint  -> buttons & button) { input.mi.dwFlags |= MOUSEEVENTF_XUP;   subiterator = NULL; }

            if (NULL == subiterator) {
              if (Point::Button::EXTENDED[1] == button) input.mi.mouseData = XBUTTON1;
              if (Point::Button::EXTENDED[2] == button) input.mi.mouseData = XBUTTON2;

              break;
            }
          }
        }

        // ...
        if (FALSE != ::SetCursorPos(currentPoint -> x, currentPoint -> y))
        if (1u == ::SendInput(1u, &input, sizeof(INPUT))) {
          ::Sleep(currentPoint -> timestamp > recentPoint -> timestamp ? currentPoint -> timestamp - recentPoint -> timestamp : 100u);
        }
      }
    }
  }
}
