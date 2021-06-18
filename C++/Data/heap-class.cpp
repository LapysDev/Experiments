/* Import */
#include <cstddef> // C Standard Definitions
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library
#include <cstring> // C String

#include <new>     // New
#include <vector>  // Vector

/* Class */
// : Animal
class Animal {
  private:
    static unsigned char *ARENA;
    static unsigned ARENA_SIZE;

    // ...
    unsigned char* data(void) const;
    unsigned char* functions(void) const;

    unsigned char* self(void) const;

  protected:
    // data members
    unsigned* addressAge(void) const;
    std::vector<Animal const*>* addressFriends(void) const;
    char const** addressName(void) const;

    // virtual function members
    void (Animal:: **addressMakeNoise(void) const)(...) const noexcept;

  public:
    static unsigned char const SIZE =
      // data members
      sizeof(char const*) +
      sizeof(unsigned) +
      sizeof(std::vector<Animal const*>) +

      // function members
      sizeof(void (Animal::*)(...) const noexcept) +

      // address
      sizeof(Animal const*)
    ;

    Animal(char const[] = NULL, unsigned = 0u);
    ~Animal(void);

    // ...
    unsigned getAge(void) const;
    void (Animal::* getMakeNoise(void) const)(...) const noexcept;
    std::vector<Animal const*>& getFriends(void) const;
    char const* getName(void) const;

    void setAge(unsigned);
    void setFriends(std::vector<Animal const*> const&);
    void setName(char const[]);

    // ...
    void makeNoise(...) const noexcept;
    void report(...) const;
};

// : Gazelle
class Gazelle : public Animal {
  public:
    Gazelle(char const[] = NULL, unsigned = 0u);

    void makeNoise(...) const noexcept;
};

/* ============================================================================ */
unsigned Animal::ARENA_SIZE = 128u * Animal::SIZE; // How many `Animal`s we want
unsigned char *Animal::ARENA = static_cast<unsigned char*>(
  // The heap
  std::calloc(Animal::ARENA_SIZE, sizeof(unsigned char))
);

/* Constructor/ Destructor */
Animal::Animal(char const animalName[], unsigned animalAge) {
  // Go through the heap
  for (
    unsigned char *iterator = Animal::ARENA;
    iterator != Animal::ARENA + Animal::ARENA_SIZE;

    // Iterating like this will cause object slicing
    // for derived class instances with more members

    // a byte-by-byte iteration is preferred, instead:
    //   `++iterator`
    iterator += Animal::SIZE
  ) {
    // Register the address onto the heap
    // -- also allocates the `Heap` object
    Animal *&heap = *reinterpret_cast<Animal**>(iterator);
    if (NULL == heap) { heap = this; break; }
  }

  // ...
  if (NULL == this -> self()) {
    // Unable to allocate `Animal` onto heap
  }

  else {
    // Initialize the `Heap` object's members
    // -- much like a constructor member initializer list
    unsigned *age = this -> addressAge();
    std::vector<Animal const*>* friends = this -> addressFriends();
    void (Animal:: **makeNoise)(...) const = this -> addressMakeNoise();
    char const **name = this -> addressName();

    new (age) unsigned(animalAge); // can't change location of members
    new (name) char const*(animalName); // since it's based of `self()` address
    new (friends) std::vector<Animal const*>(); // non-trivial objects are why we initialize

    *makeNoise = &Animal::makeNoise;

    // Initialize the `Heap` object
    // -- much like the constructor-specific code
    this -> getFriends().push_back(this);
  }
}

Animal::~Animal(void) {
  // destructible data members
  std::vector<Animal const*>* friends = this -> addressFriends();

  friends -> ~vector();
  std::memset(this -> self(), 0x0u, Animal::SIZE);
}

Gazelle::Gazelle(char const gazelleName[], unsigned gazelleAge) : Animal::Animal(gazelleName, gazelleAge) {
  void (Animal:: **makeNoise)(...) const = this -> addressMakeNoise();

  *makeNoise = static_cast<void (Animal::*)(...) const noexcept>(&Gazelle::makeNoise);
}

/* Base Addresses */
unsigned char* Animal::data(void) const {
  return this -> self() + sizeof(Animal const*);
}

unsigned char* Animal::functions(void) const {
  return this -> data() + sizeof(char const*) + sizeof(unsigned) + sizeof(std::vector<Animal const*>);
}

unsigned char* Animal::self(void) const {
  // Go through the heap
  for (
    unsigned char *iterator = Animal::ARENA;
    iterator != Animal::ARENA + Animal::ARENA_SIZE;
    iterator += Animal::SIZE
  ) {
    // Get the allocated `Heap` object
    Animal const *&heap = *reinterpret_cast<Animal const**>(iterator);
    if (this == heap) return iterator;
  }

  return NULL;
}

/* Member Addresses */
unsigned* Animal::addressAge(void) const {
  // First member
  return reinterpret_cast<unsigned*>(this -> data());
}

char const** Animal::addressName(void) const {
  // Second member
  return reinterpret_cast<char const**>(
    // each successive member's address is exclusive
    // to prevent data corruption via merged boundaries
    this -> data() + sizeof(unsigned)
  );
}

std::vector<Animal const*>* Animal::addressFriends(void) const {
  // Third member
  return reinterpret_cast<std::vector<Animal const*>*>(
    // the more members there are
    // the more newer members are offset
    this -> data() + sizeof(char const*) + sizeof(unsigned)
  );
}

void (Animal::** Animal::addressMakeNoise(void) const)(...) const noexcept {
  union {
    // Illegal to cast between data & function (member) pointers
    unsigned char *data;
    void (Animal:: **evaluation)(...) const;
  } address;

  // Illegal to type-pun via `union`s (this way)
  address.data = this -> functions();
  return address.evaluation;
}

/* Getter/ Setters */
unsigned Animal::getAge(void) const { return *(this -> addressAge()); }
std::vector<Animal const*>& Animal::getFriends(void) const { return *(this -> addressFriends()); }
void (Animal::* Animal::getMakeNoise(void) const)(...) const noexcept { return *(this -> addressMakeNoise()); }
char const* Animal::getName(void) const { return *(this -> addressName()); }

void Animal::setAge(unsigned age) {  *(this -> addressAge()) = age; }
void Animal::setFriends(std::vector<Animal const*> const& friends) { *(this -> addressFriends()) = friends; }
void Animal::setName(char const name[]) { *(this -> addressName()) = name; }

/* ... */
void Animal::makeNoise(...) const noexcept {
  std::puts("*animal noises*");
}

void Animal::report(...) const {
  std::printf("\"%s\" (age %u) is %p, and friends with ",
    this -> getName(),
    this -> getAge(),
    static_cast<void const*>(this)
  );

  std::vector<Animal const*> &friends = this -> getFriends();
  for (std::size_t iterator = friends.size(); iterator--; ) {
    Animal const *const acquaintance = friends[iterator];

    std::printf("%p%s",
      static_cast<void const*>(acquaintance),
      this == acquaintance ? "" : ", "
    );
  }

  std::printf("%2s", "\r\n");
}

void Gazelle::makeNoise(...) const noexcept {
  std::puts("*gazelle noises*");
}

/* ============================================================================ */
int main(void) {
  Animal const becky = Animal("Becky", 3u);
  Gazelle const zara = Gazelle("Zara", 5u);

  // should be `1` both since all their data is on the heap
  std::printf("[sizeof(Animal)] : %lu" "\r\n", static_cast<unsigned long>(sizeof(Animal) ));
  std::printf("[sizeof(Gazelle)]: %lu" "\r\n", static_cast<unsigned long>(sizeof(Gazelle)));
  std::puts("");

  // ...
  becky.report();                      // member function call
  becky.getFriends().push_back(&zara); // use of data member
  becky.report();                      // member function call
  (becky .* becky.getMakeNoise())();   // virtual member function call

  zara.report();                       // member function call
  (zara  .* zara.getMakeNoise() )();   // virtual member function call
}
