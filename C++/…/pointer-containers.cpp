#include <array>
#include <functional>
#include <iostream>
#include <string>

/* ... */
// : units
std::array<std::string const, 8u> const demons   = {"Aamon", "Ba'al", "Caim", "Daeva", "Mephistopheles", "O Tokata", "Xaphan", "Yeqon"};
std::array<std::string const, 8u> const gods     = {"Aphrodite (Venus)", "Apollo", "Ares (Mars)", "Artemis (Diana)", "Hades (Pluto)", "Hephaestus (Vulkan)", "Hera (Juno)", "Poseidon (Neptune)"};
std::array<std::string const, 8u> const monarchs = {"Charles II", "Edward I", "Elizabeth I", "Henry V", "Henry VII", "Henry VIII", "Richard I the Lionheart", "William II and III"};

// : reinforce
std::array<std::string const, 8u> const* call  () { return &monarchs; }
std::array<std::string const, 8u> const* summon() { return &gods    ; }
std::array<std::string const, 8u> const* spawn () { return &demons  ; }

// : ...
std::function<std::array<std::string const, 8u> const* ()> request(std::array<std::string const, 8u> const* const units) {
  if (units == &demons  ) return spawn ;
  if (units == &gods    ) return summon;
  if (units == &monarchs) return call  ;

  return *static_cast<std::array<std::string const, 8u> const* (*)()>(NULL);
}

/* Main */
int main() {
  std::array<std::function<std::array<std::string const, 8u> const* ()>, 3u> const reinforcements = {
    request(&demons  ),
    request(&gods    ),
    request(&monarchs)
  };

  for (std::function<std::array<std::string const, 8u> const* ()> const& reinforcement : reinforcements) {
    std::array<std::string const, 8u> const *const units = reinforcement.operator()();

    std::cout.write("\r\n" "Reinforcements arriving...: ", 30u);
    if (units == &demons  ) std::operator <<(std::cout, "demons"  );
    if (units == &gods    ) std::operator <<(std::cout, "gods"    );
    if (units == &monarchs) std::operator <<(std::cout, "monarchs");
    std::endl(std::cout);

    for (std::string const &name : *units)
    std::cout << '\t' << '"' << name << '"' << std::endl;
  }
}
