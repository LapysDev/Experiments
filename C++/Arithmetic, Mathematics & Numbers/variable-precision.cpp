/* Import */
#include <cstddef> // C Standard Definitions
#include <cstdio> // C Standard Input/ Output
#include <cstdint> // C Standard Integers
#include <cstdlib> // C Standard Library
#include <cstring> // C String

/* ... */
#define private public
#define protected public
static char BINARY_FORM_STRING_BUFFER[CHAR_BIT + 1u];
constexpr char (&binaryof(std::uintmax_t number) noexcept)[sizeof(BINARY_FORM_STRING_BUFFER)] {
	char *iterator = BINARY_FORM_STRING_BUFFER + (sizeof(BINARY_FORM_STRING_BUFFER) / sizeof(char));

	for (*--iterator = '\0'; number; number >>= 1uLL) *--iterator = "01"[number & 1uLL];
	while (BINARY_FORM_STRING_BUFFER != iterator) *--iterator = '0';

	return BINARY_FORM_STRING_BUFFER;
}

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
	// [...]
	protected:
		// ... --- NOTE (Lapys)
		enum class ALLOCATE : unsigned char { FIXED = 0x1, RESIZE = 0x2, ZERO = 0x4 };
		constexpr static unsigned char DIGITS_MAX = CHAR_BIT;
		enum class ERROR : std::uintptr_t { GET_CONSTRUCTOR_NAME, REPORT_INSUFFICIENT_MEMORY_FOR_DIGITS, REPORT_INSUFFICIENT_MEMORY_FOR_STRING };

		typedef unsigned char byte_t;
		typedef unsigned char digits_t; // -> Set of `DIGITS_MAX` binary digits (where a digit is 1 bit in memory).
		typedef std::size_t index_t, length_t;
		typedef std::uint64_t primitive_t;

		constexpr friend unsigned char operator &(ALLOCATE const flagA, ALLOCATE const flagB) noexcept { return static_cast<unsigned char>(flagA) & static_cast<unsigned char>(flagB); }
		constexpr friend ALLOCATE operator |(ALLOCATE const flagA, ALLOCATE const flagB) noexcept { return static_cast<ALLOCATE>(static_cast<unsigned char>(flagA) | static_cast<unsigned char>(flagB)); }

		// Method > ...
		constexpr unsigned char static lengthof(primitive_t const) noexcept;

		constexpr unsigned char static widthof(primitive_t const) noexcept;
		constexpr unsigned char static widthof(primitive_t const, unsigned char const) noexcept;

	// [...]
	private:
		// Definition > Value
		byte_t *value;

		// Method > ...
		// : Exception
		virtual char const* error(ERROR const) const noexcept(false);
		void error(char const[]) const noexcept(false);

		// : Memory
		void allocate(ALLOCATE const, std::size_t);
		void copy(primitive_t const);
		void copy(BigUnsignedInteger const&);
		constexpr void move(BigUnsignedInteger&) noexcept;
		void release(void) noexcept;

		// : Structure
		constexpr digits_t* getDigitsCollection(void) const noexcept;
		constexpr length_t getLength(void) const noexcept;

		constexpr void setDigitsCollection(primitive_t, index_t const, length_t) noexcept;
		constexpr void setLength(length_t const) noexcept;

	// [...]
	public:
		// [Constructor, Destructor]
		constexpr BigUnsignedInteger(void) noexcept;
		BigUnsignedInteger(primitive_t const);
		BigUnsignedInteger(BigUnsignedInteger const&);
		constexpr BigUnsignedInteger(BigUnsignedInteger&&) noexcept;

		~BigUnsignedInteger(void) noexcept;

		// Method > ...
		constexpr void decrement(void) noexcept;
		void increment(void);

		constexpr bool isZero(void) const noexcept;

		char const* toString(void) const;
		constexpr char const* toString(char[]) const noexcept;
};

/* Modification */
/* : Big Unsigned Integer */
	// [Constructor]
	constexpr BigUnsignedInteger::BigUnsignedInteger(void) noexcept : value{nullptr} {}
	BigUnsignedInteger::BigUnsignedInteger(primitive_t const number) : value{nullptr} { this -> copy(number); }

	BigUnsignedInteger::BigUnsignedInteger(BigUnsignedInteger const& number) : value{nullptr} { this -> copy(number); }
	constexpr BigUnsignedInteger::BigUnsignedInteger(BigUnsignedInteger&& number) noexcept : value{nullptr} { this -> move(number); }

	// [Destructor]
	BigUnsignedInteger::~BigUnsignedInteger(void) noexcept { if (nullptr != this -> value) this -> release(); }

	// Allocate, Copy, Move, Release --- REDACT (Lapys)
	constexpr void BigUnsignedInteger::move(BigUnsignedInteger& number) noexcept { this -> value = number.value; number.value = nullptr; }
	void BigUnsignedInteger::release(void) noexcept { std::free(this -> value); this -> value = nullptr; }

	void BigUnsignedInteger::allocate(ALLOCATE const flag, std::size_t size) {
		void *const allocation = std::realloc(this -> value, size = (flag & ALLOCATE::FIXED ? (3u * size) / 2u : size) + sizeof(length_t));

		if (nullptr == allocation) this -> error(ERROR::REPORT_INSUFFICIENT_MEMORY_FOR_DIGITS);
		this -> value = reinterpret_cast<byte_t*>(allocation);
		if (flag & ALLOCATE::ZERO) std::memset(this -> getDigitsCollection(), 0x0, size - sizeof(length_t));
	}

	void BigUnsignedInteger::copy(primitive_t const number) {
		unsigned char const length = BigUnsignedInteger::lengthof(number);

		this -> allocate(ALLOCATE::RESIZE, BigUnsignedInteger::widthof(number, length) + sizeof(digits_t));
		this -> setDigitsCollection(number, 0u, length);
		this -> setLength(length);
	}

	void BigUnsignedInteger::copy(BigUnsignedInteger const& number) {
		length_t length = number.getLength();

		this -> allocate(ALLOCATE::RESIZE, length);
		this -> setLength(length);

		length /= DIGITS_MAX;
		for (
			digits_t *digitsCollectionIterator = this -> getDigitsCollection(), *numberDigitsCollectionIterator = number.getDigitsCollection(); length--;
		) digitsCollectionIterator[length] = numberDigitsCollectionIterator[length];
	}

	// Decrement
	constexpr void BigUnsignedInteger::decrement(void) noexcept {}

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

	// Increment
	void BigUnsignedInteger::increment(void) {
		// Logic
		if (this -> isZero()) {
			// ...; Update > Target
			this -> allocate(ALLOCATE::RESIZE, 1u);

			*(this -> getDigitsCollection()) |= (((1u << (DIGITS_MAX - 1u)) - 1u) << 1u) + 1u; // -> this -> setDigitsCollection(1u, 0u, 1u);
			this -> setLength(1u);
		}

		else {
			// Initialization > (Length, Digits Collection ...)
			length_t length = this -> getLength();
			digits_t *const digitsCollectionEnd = this -> getDigitsCollection(), *digitsCollectionIterator = digitsCollectionEnd + ((length - 1u) / DIGITS_MAX);
			unsigned char digitsCollectionLength = length % DIGITS_MAX;

			// ...; Loop
			(0u == digitsCollectionLength) && (digitsCollectionLength = DIGITS_MAX);
			do {
				// Loop > Logic
				for (unsigned char iterator = digitsCollectionLength; iterator; --iterator)
				if (0u == ((*digitsCollectionIterator >> (DIGITS_MAX - iterator)) & 1u)) {
					// ...; Terminate
					*digitsCollectionIterator ^= *digitsCollectionIterator & ((1u << (DIGITS_MAX - iterator + 1u)) - 1u);
					*digitsCollectionIterator |= 1u << (DIGITS_MAX - iterator);

					return;
				}

				// Update > Digits Collection ...
				*digitsCollectionIterator = 0u;
				digitsCollectionLength = DIGITS_MAX;
			} while (digitsCollectionEnd != digitsCollectionIterator--);

			// ...; Update > Target
			this -> allocate(ALLOCATE::RESIZE | ALLOCATE::ZERO, ++length);

			*(this -> getDigitsCollection()) = 1u << (DIGITS_MAX - 1u); // -> this -> setDigitsCollection(1u << (DIGITS_MAX - 1u), 0u, DIGITS_MAX);
			this -> setLength(length);
		}
	}

	// Is ...
	constexpr bool BigUnsignedInteger::isZero(void) const noexcept { return nullptr == this -> value || 0u == this -> getLength(); }

	// To String
	char const* BigUnsignedInteger::toString(void) const {
		char *const string = static_cast<char*>(std::malloc(((this -> getLength() | 1u) * sizeof(char)) + sizeof(char)));
		return nullptr == string ? this -> error(ERROR::REPORT_INSUFFICIENT_MEMORY_FOR_STRING) : this -> toString(string);
	}

	constexpr char const* BigUnsignedInteger::toString(char string[]) const noexcept {
		// Constant > Length
		length_t const length = this -> getLength();

		// Logic > ...
		if (0u == length) { string[0] = '0'; string[1] = '\0'; }
		else {
			// Initialization > (Digits Collection, String) ...
			digits_t const *digitsCollectionIterator = this -> getDigitsCollection();
			digits_t const *const digitsCollectionEnd = digitsCollectionIterator + (length ? (length - 1u) / DIGITS_MAX : 0u);

			char *stringIterator = string;

			// ... Update > String ...
			do {
				for (unsigned char iterator = DIGITS_MAX; iterator-- && length != static_cast<length_t>(stringIterator - string); ++stringIterator)
				*stringIterator = (*digitsCollectionIterator >> iterator) & 1u ? '1' : '0';
			} while (digitsCollectionEnd != digitsCollectionIterator++);

			*stringIterator = '\0';
		}

		// Return
		return string;
	}

	// ... (Digits Collection, Length)
	constexpr typename BigUnsignedInteger::length_t BigUnsignedInteger::getLength(void) const noexcept { return nullptr == this -> value ? 0u : *reinterpret_cast<length_t*>(this -> value); }
	constexpr typename BigUnsignedInteger::digits_t* BigUnsignedInteger::getDigitsCollection(void) const noexcept { return this -> value + (sizeof(length_t) * (nullptr != this -> value)); }

	constexpr void BigUnsignedInteger::setLength(length_t const length) noexcept { *reinterpret_cast<length_t*>(this -> value) = length; }
	constexpr void BigUnsignedInteger::setDigitsCollection(primitive_t value, index_t const index, length_t length) noexcept {
		// Initialization > (Digits ... Iterator, Value Slice ...)
		digits_t *digitsCollectionIterator = this -> getDigitsCollection() + (index / DIGITS_MAX);
		primitive_t valueSlice = 0u;
		unsigned char valueSliceLength = 0u;

		// Update > ... --- NOTE (lapys) -> Set the first set of digits with regards to any misaligned offsets from calculating the `index`.
		valueSliceLength = (DIGITS_MAX < length ? DIGITS_MAX : length) - (index % DIGITS_MAX);
		valueSlice = value >> (length - valueSliceLength);

		*digitsCollectionIterator ^= *digitsCollectionIterator & ((1u << (DIGITS_MAX - (index % DIGITS_MAX))) - 1u);
		*digitsCollectionIterator = length < DIGITS_MAX ? valueSlice << (DIGITS_MAX - length) : (*digitsCollectionIterator | valueSlice);

		length -= valueSliceLength;
		value ^= valueSlice << length;

		// ... Loop > Update > ... --- NOTE (Lapys) -> If sized enough, set successive sets of `DIGITS_MAX` collections from `value`.
		valueSliceLength = DIGITS_MAX;
		while (length > valueSliceLength) {
			valueSlice = value >> (length - valueSliceLength);
			*++digitsCollectionIterator = valueSlice;

			length -= valueSliceLength;
			value ^= valueSlice << length;
		}

		// Logic > ... --- NOTE (Lapys) -> Set the last set of binary digits.
		if (length) {
			valueSliceLength = length;
			valueSlice = value;

			++digitsCollectionIterator;
			*digitsCollectionIterator = (valueSlice << (DIGITS_MAX - valueSliceLength)) | (*digitsCollectionIterator & ((1u << (DIGITS_MAX - valueSliceLength)) - 1u));
		}
	}

	// ... Of
	constexpr unsigned char BigUnsignedInteger::lengthof(primitive_t const number) noexcept { return number ? 1uL + BigUnsignedInteger::lengthof(number >> 1uL) : 0uL; }

	constexpr unsigned char BigUnsignedInteger::widthof(primitive_t const number) noexcept { return BigUnsignedInteger::widthof(number, BigUnsignedInteger::lengthof(number)); }
	constexpr unsigned char BigUnsignedInteger::widthof(primitive_t const, unsigned char const length) noexcept { return (length / DIGITS_MAX) + (length % DIGITS_MAX ? 1u : 0u); }

/* Main */
int main(void) {
	::puts("[PROGRAM INITIATED]");
		// ::printf("#01 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xAABBCCDDEEFF}.toString());
		// ::printf("#02 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFFFFFFF}.toString());
		// ::printf("#03 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFFFFFF}.toString());
		// ::printf("#04 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFFFFF}.toString());
		// ::printf("#05 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFFFF}.toString());
		// ::printf("#06 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFFF}.toString());
		// ::printf("#07 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFFF}.toString());
		// ::printf("#08 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFFF}.toString());
		// ::printf("#09 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFFF}.toString());
		// ::printf("#10 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFFF}.toString());
		// ::printf("#11 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFFF}.toString());
		// ::printf("#12 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xFF}.toString());
		// ::printf("#13 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xF}.toString());
		// ::printf("#14 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xF}.toString());
		// ::printf("#15 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xE}.toString());
		// ::printf("#16 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xD}.toString());
		// ::printf("#17 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xC}.toString());
		// ::printf("#18 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xB}.toString());
		// ::printf("#19 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0xA}.toString());
		// ::printf("#20 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x9}.toString());
		// ::printf("#21 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x8}.toString());
		// ::printf("#22 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x7}.toString());
		// ::printf("#23 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x6}.toString());
		// ::printf("#24 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x5}.toString());
		// ::printf("#25 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x4}.toString());
		// ::printf("#26 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x3}.toString());
		// ::printf("#27 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x2}.toString());
		// ::printf("#28 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x1}.toString());
		// ::printf("#29 [EVAL]: \"%s\"" "\r\n", BigUnsignedInteger {0x0}.toString());

		// for (unsigned char iterator = 0u; iterator ^ 40u; ++iterator) {
		// 	BigUnsignedInteger number = 0xFFFFFFFFFFFFu;
		// 	number.setDigitsCollection(0x0u, iterator, 8u);
		// 	::printf("[EVAL (%u)]: \"%s\"" "\r\n", iterator, number.toString());
		// }

		// BigUnsignedInteger number = 0u;
		// for (std::size_t iterator = 0u; iterator <= ULLONG_MAX; ++iterator) {
		// 	char string[64];
		// 	::printf("[EVAL]: (%zu) \"%s\"" "\r\n", iterator, number.toString(string));
		// 	number.increment();
		// }
    ::puts("[PROGRAM TERMINATED]");
}
