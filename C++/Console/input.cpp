#include <cstdio>
#include <cstdlib>
#include <new>

/* ... */
class Player {
  friend int main();

  private:
    unsigned char age;
    char *name;

  public:
    Player() : age(0u), name(NULL) {}
    ~Player() { std::free(this -> name); }
};

/* Main */
int main() {
  unsigned char const INVALID_COUNT = 10u;
  unsigned char count = INVALID_COUNT;
  Player *players;

  // ... ->> Count the `Player`s
  std::printf("%32s", "How many players will there be? ");
  switch (std::getchar()) {
    case '0': count = 0u; break;
    case '1': count = 1u; break;
    case '2': count = 2u; break;
    case '3': count = 3u; break;
    case '4': count = 4u; break;
    case '5': count = 5u; break;
    case '6': count = 6u; break;
    case '7': count = 7u; break;
    case '8': count = 8u; break;
    case '9': count = 9u; break;

    case EOF: case '\n': {
      if (INVALID_COUNT == count) {
        std::fputs("\r\n\n" "[InputError]: No input provided", stderr);
        std::exit(EXIT_FAILURE);
      }
    } break;

    default: {
      std::fputs("\r\n\n" "[InputError]: Invalid input", stderr);
      std::exit(EXIT_FAILURE);
    } break;
  }

  // ...
  if (0u == count) {
    std::puts("\r\n" "Alright!");
    std::puts("Enter any key to continue...");

    std::getchar();
  }

  else {
    std::getchar();

    // ... ->> Allocate enough `Player`s in RAM
    players = static_cast<Player*>(std::malloc(count * sizeof(Player)));
    if (NULL == players) {
      std::fputs("\r\n\n" "[MemoryError]: Unable to record players", stderr);
      std::exit(EXIT_FAILURE);
    }

    // ... ->> Record the `Player` data
    for (unsigned char iterator = 0u; count != iterator; ++iterator) {
      Player *const player = new (players + iterator) Player(); // ->> Instantiate `Player` object

      // ... ->> Set `char Player::name[255]`
      std::printf("%.2s" "%19s%hu%2s", 0u == iterator ? "" : "\r\n", "  " "Name for player #", static_cast<unsigned short>(iterator), ": ");
      for (unsigned char capacity = 0u, length = 0u; ; ++length) {
        int const character = std::getchar();

        // ...
        if (capacity == length) {
          capacity = 0u != length ? length * 2u : 16u;
          player -> name = static_cast<char*>(NULL == player ? std::malloc(capacity * sizeof(char)) : std::realloc(player -> name, capacity * sizeof(char)));

          if (NULL == player -> name) {
            std::fputs("\r\n\n" "[MemoryError]: Unable to record player", stderr);
            std::exit(EXIT_FAILURE);
          }
        }

        // ...
        if (EOF == character || '\n' == character) {
          if (length == 0u) {
            std::fputs("\r\n\n" "[InputError]: No input provided", stderr);
            std::exit(EXIT_FAILURE);
          }

          player -> name[length] = '\0';
          break;
        }

        // ...
        player -> name[length] = static_cast<char>(character);

        // ...
        if (length == 64u) {
          std::fputs("\r\n\n" "[InputError]: Input too long", stderr);
          std::exit(EXIT_FAILURE);
        }
      }

      // ... ->> Set `unsigned char Player::age`
      std::printf("%27s", "   " "How aged is the player? ");
      for (unsigned char length = 10u; ; length /= 10u) {
        int const character = std::getchar();

        // ...
        if (EOF == character || '\n' == character) {
          if (length == 10u) {
            std::fputs("\r\n\n" "[InputError]: No input provided", stderr);
            std::exit(EXIT_FAILURE);
          }

          while (length) { length /= 10u; player -> age /= 10u; }
          break;
        }

        // ...
        switch (character) {
          case '0': player -> age += 0u * length; break;
          case '1': player -> age += 1u * length; break;
          case '2': player -> age += 2u * length; break;
          case '3': player -> age += 3u * length; break;
          case '4': player -> age += 4u * length; break;
          case '5': player -> age += 5u * length; break;
          case '6': player -> age += 6u * length; break;
          case '7': player -> age += 7u * length; break;
          case '8': player -> age += 8u * length; break;
          case '9': player -> age += 9u * length; break;
          default: {
            std::fputs("\r\n\n" "[InputError]: Invalid input", stderr);
            std::exit(EXIT_FAILURE);
          }
        }

        // ...
        if (length == 0u) {
          std::fputs("\r\n\n" "[InputError]: Input too long", stderr);
          std::exit(EXIT_FAILURE);
        }
      }
    }

    // ... ->> Announce the `Player`s
    std::printf("%10s", "\r\n" "Alright!");
    std::printf("%10s", "\r\n" "Welcome ");
    for (unsigned char iterator = 0u; count != iterator; ++iterator) {
      Player *const player = players + iterator;

      std::printf("\"%s\" (%hu)" "%.6s", player -> name, static_cast<unsigned short>(player -> age), count == iterator + 1u ? "" : count == iterator + 2u ? ", and " : ", ");
    }

    // ... ->> Release the `Player`s from RAM
    for (unsigned char iterator = 0u; count != iterator; ++iterator) {
      Player *const player = players + iterator;
      player -> ~Player(); // ->> we would `delete` if `new` had actually allocated memory earlier
    }

    std::free(players);
  }

  // ... --> EXIT_SUCCESS
  return EXIT_SUCCESS;
}
