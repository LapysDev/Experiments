#include <cstdio>
#include <typeinfo>
#include <vector>

/* ... */
struct lambda;
struct lambda_information;

// ...
struct lambda_information {
  lambda const *const lambda;
  std::type_info const &type;

  lambda_information(::lambda const* const lambda, std::type_info const& type) :
    lambda(lambda), type(type)
  {}
};

std::vector<lambda_information> lambdas;

struct lambda {
  int const parameter;
  lambda(int const parameter) : parameter(parameter) {}

  template <auto = []() {}>
  int (*to_function())(int) const {
    return this->to_function([](lambda const* const that, int const x) -> int {
      return that->parameter + x;
    });
  }

  template <typename T>
  int (*to_function(T&& temporary))(int) const {
    static T const persistent {temporary};
    struct container {
      static int actual_function(int const x) {
        for (lambda_information &information : lambdas)
        if (information.type == typeid(T)) return persistent.operator ()(information.lambda, x);

        return *static_cast<int*>(NULL);
      }
    };

    lambdas.emplace_back(this, typeid(T));
    return &container::actual_function;
  }
};

/* Main */
int main() {
  std::printf("[2 + 3]: %i" "\r\n", lambda(2).to_function()(3));
  std::printf("[3 + 3]: %i" "\r\n", lambda(3).to_function()(3));
  std::printf("[4 + 3]: %i" "\r\n", lambda(4).to_function()(3));

  for (lambda_information &information : lambdas)
  std::printf("[...]: \"%s\"" "\r\n", information.type.name());
}
