/* Import */
#include <cstddef> // C Standard Definitions
#include <cstdio> // C Standard Input/ Output
#include <cstdint> // C Standard Integers
#include <cstdlib> // C Standard Library

/* Definition > ... */
class BigNumber;
class BigFloat;
class BigSignedInteger;
class BigUnsignedInteger;

/* Class */
/* : Big Number */
class BigNumber {};

/* : Big Unsigned Integer */
class BigUnsignedInteger : public BigNumber {
	protected:
		enum class ALLOCATE : unsigned char { RESIZE = 0x1 };
		enum class ERROR : std::uintptr_t { GET_CONSTRUCTOR_NAME, REPORT_INSUFFICIENT_MEMORY_FOR_DIGITS, REPORT_INSUFFICIENT_MEMORY_FOR_STRING };

		typedef unsigned char byte_t;
		typedef unsigned char digits_t;
		typedef std::size_t index_t, length_t;
		typedef std::uint64_t primitive_t;

		constexpr unsigned char static lengthof(primitive_t const) noexcept;

		constexpr unsigned char static widthof(primitive_t const) noexcept;
		constexpr unsigned char static widthof(primitive_t const, unsigned char const) noexcept;

		constexpr friend unsigned char operator &(ALLOCATE const flagA, ALLOCATE const flagB) noexcept { return static_cast<unsigned char>(flagA) & static_cast<unsigned char>(flagB); }

	private:
		byte_t *value;

		// Method > ...
		// : Exception
		virtual char const* error(ERROR const) const noexcept(false);
		void error(char const[]) const noexcept(false);

		// : Memory
		void allocate(ALLOCATE const, std::size_t const);
		void copy(primitive_t const);
		void release(void) noexcept;

		// : Structure
		constexpr digits_t* getDigitsCollection(void) const noexcept;
		constexpr length_t getLength(void) const noexcept;

		void setDigitsCollection(primitive_t, index_t const, length_t) noexcept;
		constexpr void setLength(length_t const) noexcept;

	public:
		constexpr BigUnsignedInteger(void) noexcept;
		BigUnsignedInteger(primitive_t const);

		char const* toString(void) const noexcept;
};

/* Modification */
/* : Big Unsigned Integer */
	// Constructor
	constexpr BigUnsignedInteger::BigUnsignedInteger(void) noexcept : value{nullptr} {}
	BigUnsignedInteger::BigUnsignedInteger(primitive_t const number) : value{nullptr} { this -> copy(number); }

	// Allocate, Copy, Release --- REDACT (Lapys)
	void BigUnsignedInteger::release(void) noexcept { std::free(this -> value); this -> value = nullptr; }
	void BigUnsignedInteger::allocate(ALLOCATE const flag, std::size_t const size) {
		if (flag & ALLOCATE::RESIZE) {
			void *const allocation = std::realloc(this -> value, size + sizeof(length_t));

			if (nullptr == allocation) this -> error(ERROR::REPORT_INSUFFICIENT_MEMORY_FOR_DIGITS);
			this -> value = reinterpret_cast<byte_t*>(allocation);
		}
	}

	void BigUnsignedInteger::copy(primitive_t const number) {
		unsigned char const length = BigUnsignedInteger::lengthof(number);

		this -> allocate(ALLOCATE::RESIZE, BigUnsignedInteger::widthof(number, length));
		this -> setDigitsCollection(number, 0u, length);
		this -> setLength(length);
	}

	// Error
	char const* BigUnsignedInteger::error(ERROR const flag) const noexcept(false) {
		// ... REDACT (Lapys)
		switch (flag) {
			case ERROR::GET_CONSTRUCTOR_NAME: return "BigUnsignedInteger";
			case ERROR::REPORT_INSUFFICIENT_MEMORY_FOR_DIGITS: this -> error("Additional memory required for `[[constructor name]]` instance"); break;
			case ERROR::REPORT_INSUFFICIENT_MEMORY_FOR_STRING: this -> error("Memory required for `[[constructor name]]::char const[]` string"); break;
		} return nullptr;
	}

	void BigUnsignedInteger::error(char const message[]) const noexcept(false) {
		// Initialization > (Error Message ..., Formats)
		char errorMessage[128], *errorMessageIterator = errorMessage - 1;
		constexpr struct {
			char const *constructorName = "[[constructor name]]";
		} formats = {};

		// Loop --- NOTE (Lapys)
		while ('\0' ^ (*++errorMessageIterator = *message++)) // -> Copy the `message`.
		for ( // -> Search for `format`s.
			char const
				*const *formatsIterator = reinterpret_cast<char const* const*>(&formats),
				*const *const formatsEnd = formatsIterator + (sizeof(formats) / sizeof(char const*));
			formatsEnd != formatsIterator; ++formatsIterator
		) {
			// Initialization > Format Iterator
			char const *formatIterator = nullptr;

			// Loop -> Assert the following `message` sequence is a `format`.
			formatIterator = (*formatsIterator) - 1;
			while ('\0' ^ *++formatIterator) {
				if (*formatIterator == *message) ++message;
				else { message -= formatIterator - *formatsIterator; break; } // -> Not a `format`.
			}

			// Logic -> — is a `format`.
			if ('\0' == *formatIterator) {
				// Logic -> Unique behavior depending on the `format`.
				// : [Constructor Name]
				if (*formatsIterator == formats.constructorName) {
					char const *constructorName = this -> error(ERROR::GET_CONSTRUCTOR_NAME);

					while ('\0' ^ (*++errorMessageIterator = *constructorName++)) continue;
					--errorMessageIterator;
				}

				// Terminate -> Stop searching for `format`s and continue copying the `message`.
				break;
			}
		}

		// Terminate
		std::fprintf(stderr, "[ERROR]: %s" "\r\n" "%c", errorMessage, '\0');
		std::exit(EXIT_FAILURE);
	}

	// To String
	char const* BigUnsignedInteger::toString(void) const noexcept {
		length_t const length = this -> getLength();
		digits_t const *digitsCollectionIterator = this -> getDigitsCollection(), *const digitsCollectionEnd = digitsCollectionIterator + (length ? (length - 1u) / CHAR_BIT : 0u);
		length_t digitsLength = 0u;
		char *string = static_cast<char*>(std::malloc((length ? length : 1u) * sizeof(char) + sizeof(char))), *stringIterator = string;

		*stringIterator = '\0';

		::printf("[length]: %llu" "\r\n", length);
		::printf("[index]: %llu" "\r\n", length ? (length - 1u) / CHAR_BIT : 0u);

		if (0u == length) string[0] = '0', string[1] = '\0';
		else do for (unsigned char iterator = CHAR_BIT; digitsLength != length && iterator--; ) {
			++digitsLength;
			*stringIterator++ = (*digitsCollectionIterator >> iterator) & 1u ? '1' : '0';
		} while (digitsCollectionEnd != digitsCollectionIterator++);

		::printf("[string]: \"%s\"" "\r\n", string);
		::puts("[...]" "\r\n");

		return string;
	}

	// ... (Digits Collection, Length)
	constexpr typename BigUnsignedInteger::length_t BigUnsignedInteger::getLength(void) const noexcept { return nullptr == this -> value ? 0u : *reinterpret_cast<length_t*>(this -> value); }
	constexpr typename BigUnsignedInteger::digits_t* BigUnsignedInteger::getDigitsCollection(void) const noexcept { return this -> value + (sizeof(length_t) * (nullptr != this -> value)); }

	constexpr void BigUnsignedInteger::setLength(length_t const length) noexcept { *reinterpret_cast<length_t*>(this -> value) = length; }
	void BigUnsignedInteger::setDigitsCollection(primitive_t value, index_t const index, length_t length) noexcept {
		digits_t *collection = this -> getDigitsCollection() + (index / CHAR_BIT);

		::printf("[length]: %zu" "\r\n", length);
		::printf("[value (%llu)]: ", value); for (primitive_t iterator = value; iterator; iterator >>= 1uL) ::putchar("01"[iterator & 1uL]); ::printf("%s", "\r\n");

		while (length) {
			unsigned char const sliceLength = length > CHAR_BIT ? CHAR_BIT : length;
			digits_t const slice = value >> (length = length > CHAR_BIT ? length - CHAR_BIT : 0u);

			value ^= slice << length;
			::printf("[length, slice, value]: ");
				::printf("(%u) ", sliceLength);
				for (digits_t iterator = slice; iterator; iterator >>= 1u) { ::putchar("01"[iterator & 1u]); } ::printf("%s", ", ");
				for (primitive_t iterator = value; iterator; iterator >>= 1uL) { ::putchar("01"[iterator & 1uL]); }
			::printf("%s", "\r\n");

			*collection++ = slice;
		}

		::puts("[...]" "\r\n");
	}

	// ... Of
	constexpr unsigned char BigUnsignedInteger::lengthof(primitive_t const number) noexcept { return number ? 1uL + BigUnsignedInteger::lengthof(number >> 1uL) : 0uL; }

	constexpr unsigned char BigUnsignedInteger::widthof(primitive_t const number) noexcept { return BigUnsignedInteger::widthof(number, BigUnsignedInteger::lengthof(number)); }
	constexpr unsigned char BigUnsignedInteger::widthof(primitive_t const, unsigned char const length) noexcept { return (length / CHAR_BIT) + (length % CHAR_BIT ? 1u : 0u); }

/* Main */
int main(void) {
	::puts("[PROGRAM INITIATED]");
	// BigUnsignedInteger {22856898}.toString();
	BigUnsignedInteger {16384}.toString();
    ::puts("[PROGRAM TERMINATED]");
}
