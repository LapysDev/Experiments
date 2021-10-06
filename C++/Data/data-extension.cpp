#include <cstdio>
#include <cstdlib>
#include <new>

/* ... */
struct Character {
  unsigned age;
  char const *name;

  constexpr Character(char const name[], unsigned const age) noexcept :
    age(age), name(name)
  {}
};

struct Player : public Character {
  char const *nickname;

  constexpr Player(char const nickname[], char const name[], unsigned const age) noexcept :
    Character::Character(name, age),
    nickname(nickname)
  {}
};

/* Main */
int main() {
  Character *characters = NULL;
  Player *players = NULL;

  // ...
  characters = static_cast<Character*>(std::malloc(5u * sizeof(Character)));
  if (NULL == characters) {
    std::fputs("\r\n" "[Error]: Failed to allocate `Character`s", stderr);
    std::exit(EXIT_FAILURE);
  }

  else {
    new (characters + 0) Character("[A] Debby", 37u);
    new (characters + 1) Character("[B] Caroline", 22u);
    new (characters + 2) Character("[C] Stanton", 28u);
    new (characters + 3) Character("[D] Prince", 16u);
    new (characters + 4) Character("[E] Winters", 20u);

    for (Character *iterator = characters + 5; characters != iterator; ) {
      Character *const character = std::launder(--iterator);
      std::printf("[...]: (Character) {age: %u, name: \"%s\"}" "\r\n", character -> age, character -> name);
    }

    // ...
    players = static_cast<Player*>(std::realloc(characters, 5u * sizeof(Player)));
    if (NULL == players) {
      std::fputs("\r\n" "[Error]: Failed to allocate `Player`s", stderr);
      std::exit(EXIT_FAILURE);
    }

    else {
      for (unsigned char index = 5u; index--; ) {
        Character *const character = std::launder(characters + index);

        new (players + index) Player("[[default nickname]]", character -> name, character -> age);
        character -> ~Character();
      }

      for (Player *iterator = players + 5; players != iterator; ) {
        Player *const player = std::launder(--iterator);
        std::printf("[...]: (Player) {age: %u, name: \"%s\", nickname: \"%s\"}" "\r\n", player -> age, player -> name, player -> nickname);
      }
    }
  }

  // ...
  if (NULL != players) {
    for (Player *iterator = players + 5; players != iterator; )
    std::launder(--iterator) -> ~Player();

    std::free(players);
  }

  else if (NULL != characters)
    std::free(characters);

  // ...
  return EXIT_SUCCESS;
}
