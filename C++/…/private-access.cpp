#include <cstdio>

/* ... */
class User {
  private: int data;
  public: User() : data(42) {}
};

// ...
template <int User::* member>
struct Facebook {
  friend int& steal(User& user) {
    return user.*member;
  }
};

template struct Facebook<&User::data>;
int& steal(User&);

/* Main */
int main() {
  User user;
  std::printf("%i", steal(user));
}
