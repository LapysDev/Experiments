#include <windows.h>

/* ... */
typedef struct timer_t {
  struct timestamp_t {
    friend struct timer_t;

    private: LARGE_INTEGER value;
    public:
      constexpr explicit timestamp_t() : value() {}
      explicit timestamp_t(timestamp_t* const timestamp) noexcept(noexcept(::QueryPerformanceCounter(NULL))) :
        value()
      {
        ::QueryPerformanceCounter(&(this -> value));
        timestamp -> value.QuadPart = this -> value.QuadPart;
      }

      constexpr operator LONGLONG() const { return this -> value.QuadPart; }
  };

  private:
    timestamp_t const timestamp;
    LONGLONG const time;

  public:
    explicit timer_t(timestamp_t* const timestamp) noexcept(noexcept(timestamp_t(NULL))) :
      timestamp(timestamp), time(timestamp -> value.QuadPart = this -> timestamp.value.QuadPart - timestamp -> value.QuadPart)
    {}

    constexpr operator LONGLONG() const { return this -> time; }
} timerend;

typedef timerend::timestamp_t timerstart;


// struct timer {
//   friend void timerstart() {
//     LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
//     LARGE_INTEGER Frequency;

//     QueryPerformanceFrequency(&Frequency);
//     QueryPerformanceCounter(&StartingTime);

//     // Activity to be timed

//     QueryPerformanceCounter(&EndingTime);
//     ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;


//     //
//     // We now have the elapsed number of ticks, along with the
//     // number of ticks-per-second. We use these values
//     // to convert to the number of elapsed microseconds.
//     // To guard against loss-of-precision, we convert
//     // to microseconds *before* dividing by ticks-per-second.
//     //

//     ElapsedMicroseconds.QuadPart *= 1000000;
//     ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
//   }

//   void timer() {}
// };
