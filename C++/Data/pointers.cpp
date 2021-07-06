#include <cstdio>
#include <cstring>

/* ... */
// : units
char const *const demons  [8] = {"Aamon", "Ba'al", "Caim", "Daeva", "Mephistopheles", "O Tokata", "Xaphan", "Yeqon"};
char const *const gods    [8] = {"Aphrodite (Venus)", "Apollo", "Ares (Mars)", "Artemis (Diana)", "Hades (Pluto)", "Hephaestus (Vulkan)", "Hera (Juno)", "Poseidon (Neptune)"};
char const *const monarchs[8] = {"Charles II", "Edward I", "Elizabeth I", "Henry V", "Henry VII", "Henry VIII", "Richard I the Lionheart", "William II and III"};

// : reinforce
char const* const (*call  ())[8] { return &monarchs; }
char const* const (*summon())[8] { return &gods    ; }
char const* const (*spawn ())[8] { return &demons  ; }

// : ...
char const* const (*(*request(char const* const (*const units)[8]))())[8] {
  if (units == &demons  ) return &spawn ;
  if (units == &gods    ) return &summon;
  if (units == &monarchs) return &call  ;

  return NULL;
}

/* Main */
int main() {
  char const *const (*(*const reinforcements[])())[8] = {
    request(&demons  ),
    request(&gods    ),
    request(&monarchs)
  };

  for (
    char const *const (*(*const *iterator)())[8] = reinforcements + (sizeof(reinforcements) / sizeof(char const* const (*(*const *)())[8]));
    iterator-- != reinforcements;
  ) {
    char const *const (*(*const reinforcement)())[8] = *iterator;
    char const *const (*const units)[8] = (*reinforcement)();

    std::printf("%30s", "\r\n" "Reinforcements arriving...: ");
    if (units == &demons  ) std::printf("%6.8s", "demons"  );
    if (units == &gods    ) std::printf("%4.8s", "gods"    );
    if (units == &monarchs) std::printf("%8.8s", "monarchs");
    std::printf("%2s", "\r\n");

    for (
      char const *const *subiterator = *units + (sizeof(*units) / sizeof(char const*));
      subiterator-- != *units;
    ) {
      char const (*name)[24] = NULL;

      std::memcpy(&name, &*subiterator, sizeof(void*));
      std::printf("\t" "\"%.24s\"" "\r\n", *name);
    }
  }
}
