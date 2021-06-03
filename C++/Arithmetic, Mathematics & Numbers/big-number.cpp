#include <cstddef>
#include <cstdio>
#include <cstdlib>

/* ... */
class BigNumber;
class BigSignedInteger;
class BigUnsignedInteger;

// ...
class BigUnsignedInteger {
	private:
		std::size_t length;
		char *value;

	public:
		BigUnsignedInteger(void) : length(0u), value(NULL) {}
		BigUnsignedInteger(BigUnsignedInteger const&) : length(), value() {}

		template <typename uint_t>
		BigUnsignedInteger(uint_t) : length(), value() {}
};

class BigSignedInteger : public BigUnsignedInteger {};
class BigNumber : public BigSignedInteger {};

/* Main */
int main(void) {
	// ...
	return EXIT_SUCCESS;
}
