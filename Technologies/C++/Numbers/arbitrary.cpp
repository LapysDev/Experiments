/* Import */
#include <stdarg.h> // Standard Arguments
#include <stdlib.h> // Standard Library
#include <string.h> // String

#include <iostream>

/* Definition > ... */
#define BIG_ARRAY__LIMIT 3u

template <typename, size_t = BIG_ARRAY__LIMIT> class BigArray;
class BigNumber;

/* Class */
    /* Big Array
            --- NOTE ---
                #Lapys:
                    - Maximum size of `limit ** limit`.
                    - Would have deferred to `BigArray<type, long double>` since `sizeof(long double) >= sizeof(size_t)` but floating-point types are not allowed as non-type template parameters.

            --- WARN ---
                #Lapys: Of course, there are limitations & restrictions to non-linear arrays pretending to be single dimensional (such as more memory required than a linear array of equal length).
                    This should be inferred as a `LayeredArray` instead which has no prevalent use like those of trees in computing science.
    */
    template <typename type, size_t limit>
    class BigArray {
        // ...
        friend BigNumber;

        // [...]
        private:
            // Definition > (Depth, Value)
            size_t depth; // NOTE (Lapys) -> Number of overflows.
            struct BigArrayObject { // NOTE (Lapys) -> Represents elements in the array; Each object is only surface-deep, gaining depth via child pointer references.
                // ...
                friend BigArray;
                friend BigNumber;

                // [...]
                private:
                    // Definition > (Children, Value)
                    BigArrayObject *children;
                    size_t childrenLength, childrenLimit;
                    BigArrayObject *sibling;
                    type *value;

                // [...]
                public:
                    // [Constructor]
                    constexpr inline BigArrayObject(void) : children{NULL}, childrenLength{0u}, childrenLimit{0u}, sibling{NULL}, value{NULL} {}

                    // [Destructor] --- NOTE (Lapys) -> Resources are expected to be abandoned.
                    ~BigArrayObject(void) { delete[] this -> children; }

                    // Function > ...
                    inline void add(void) noexcept { BigArrayObject::resize(this -> childrenLength + 1u); }
                    inline void add(type& value) noexcept { BigArrayObject::add(); BigArrayObject::set(this -> childrenLength - 1u, value); }
                    template <typename... subtypes> inline void add(type& value, subtypes... values) noexcept { BigArrayObject::add(value); BigArrayObject::add(values...); }
                    inline BigArrayObject& at(size_t const index) const noexcept { return *(this -> children + index); }
                    inline void resize(size_t const size) noexcept { // NOTE (Lapys) -> Expand memory allocated via Fibonacci sequence.
                        if (NULL == this -> children) {
                            this -> children = new BigArrayObject[size] {};
                            this -> childrenLength = size;
                            this -> childrenLimit = size;
                        }

                        else if (this -> childrenLength ^ size) {
                            if (size) {
                                BigArrayObject *evaluation;

                                if (size >= this -> childrenLimit)
                                for (size_t former, iterator = 1u, recent = 0u; iterator <= size; ) {
                                    former = iterator;
                                    iterator += recent;
                                    recent = former;
                                    this -> childrenLimit = iterator;
                                }

                                if (this -> childrenLimit > limit) this -> childrenLimit = limit;

                                evaluation = new BigArrayObject[this -> childrenLimit] {};

                                for (size_t iterator = 0u, length = this -> childrenLength > size ? size : this -> childrenLength; iterator ^ length; ++iterator) {
                                    ::memcpy(evaluation + iterator, this -> children + iterator, sizeof(BigArrayObject));
                                    if ((iterator + 1u) ^ length) (evaluation + iterator) -> sibling = evaluation + (iterator + 1u);
                                }

                                delete[] this -> children;

                                this -> children = evaluation;
                                this -> childrenLength = size;
                            }

                            else {
                                delete[] this -> children;

                                this -> children = NULL;
                                this -> childrenLength = 0u;
                                this -> childrenLimit = 0u;
                            }
                        }
                    }
                    inline void set(type& value) noexcept { this -> value = &value; }
                    inline void set(size_t const index, type& value) noexcept { BigArrayObject::at(index).set(value); }
            } value; // NOTE (Lapys) -> Tree of values.

            // Definition > ...
            constexpr inline void add(void) const noexcept;
            inline type& at(size_t const) const noexcept; // WARN (Lapys) -> Maximum input index of `SIZE_MAX`.
            inline type* in(size_t const, size_t...) const noexcept; // NOTE (Lapys) -> Multi-layered indexer of `BigArray::at`.
            constexpr inline void remove(void) const noexcept;
            inline void set(type, size_t const) noexcept;

        // [...]
        public:
            // Definition > (Length, Size)
            struct BigArrayInteger { // NOTE (Lapys) -> `size_t` object with full private and limited public access.
                /* ... */
                friend BigArray;

                // [...]
                private:
                    // Definition > Value
                    size_t value;

                    // [Constructor]
                    inline BigArrayInteger(size_t const value) : value{value} {}
                    inline BigArrayInteger(void) : value{} {}

                    // [Operator] > ...
                    inline size_t& operator =(size_t const value) noexcept { return (this -> value = value); }
                    inline size_t& operator +=(size_t const value) noexcept { return (this -> value += value); }
                    inline size_t& operator -=(size_t const value) noexcept { return (this -> value -= value); }
                    inline size_t& operator *=(size_t const value) noexcept { return (this -> value *= value); }
                    inline size_t& operator /=(size_t const value) noexcept { return (this -> value /= value); }
                    inline size_t& operator %=(size_t const value) noexcept { return (this -> value %= value); }
                    inline size_t& operator ^=(size_t const value) noexcept { return (this -> value ^= value); }
                    inline size_t& operator &=(size_t const value) noexcept { return (this -> value &= value); }
                    inline size_t& operator |=(size_t const value) noexcept { return (this -> value |= value); }
                    inline size_t& operator <<=(size_t const value) noexcept { return (this -> value <<= value); }
                    inline size_t& operator >>=(size_t const value) noexcept { return (this -> value >>= value); }
                    inline size_t operator ++(int const) noexcept { return this -> value++; }
                    inline size_t& operator ++(void) noexcept { return ++(this -> value); }
                    inline size_t operator --(int const) noexcept { return this -> value--; }
                    inline size_t& operator --(void) noexcept { return --(this -> value); }

                // [...]
                public:
                    // [Operator] > [...]
                    inline operator size_t(void) const noexcept { return this -> value; }
            } length, size; // NOTE (Lapys) -> Length: Index of last element on level based on depth; Size: Total number of accessible, indexed elements.

            // [Constructor]
            inline BigArray(void) : depth{1u}, value{}, length{0u}, size{0u} {}
            inline BigArray(BigArray& array) : depth{1u}, value{}, length{0u}, size{0u} { BigArray::copy(array); }
            inline BigArray(BigArray&& array) : depth{1u}, value{}, length{0u}, size{0u} { BigArray::copy(array); }
            inline BigArray(BigArray const& array) : depth{1u}, value{}, length{0u}, size{0u} { BigArray::copy(array); }
            inline BigArray(BigArray const&& array) : depth{1u}, value{}, length{0u}, size{0u} { BigArray::copy(array); }
            template <typename... types> inline BigArray(types... values) : depth{1u}, value{}, length{0u}, size{0u} { BigArray::add(values...); }

            // [Destructor]
            inline ~BigArray(void) { BigArray::free(); }

            // (Definition, Function) > ...
            inline void add(type&) noexcept;
            inline void add(type&&) noexcept;
            template <typename subtype, typename... subtypes> inline void add(subtype, subtypes...) noexcept;
            inline void copy(BigArray const&) noexcept;
            template <typename subtype> inline void foreach(subtype (&)(type&, size_t const)) const noexcept;
            inline void free(void) noexcept;
            inline bool includesFromEnd(type&) const noexcept;
            inline bool includesFromEnd(type&&) const noexcept;
            inline bool includesFromStart(type&) const noexcept;
            inline bool includesFromStart(type&&) const noexcept;
            inline size_t indexFromEnd(type&) const noexcept;
            inline size_t indexFromEnd(type&&) const noexcept;
            inline size_t indexFromStart(type&) const noexcept;
            inline size_t indexFromStart(type&&) const noexcept;
            inline void pop(void) noexcept;
            inline void remove(type&) noexcept;
            inline void remove(type&&) noexcept;
            template <typename subtype, typename... subtypes> inline void remove(subtype, subtypes...) noexcept;
            inline void resize(size_t const) noexcept;
            inline void resize(BigNumber const) noexcept;
            inline char const* toString(void) const noexcept {
                char *string;

                return (char const*) string;
            }

            constexpr inline static bool isEmpty(BigArray const& array) noexcept;
            constexpr inline static bool isEmpty(BigArray&& array) noexcept;

            // [Operator] > ...
            inline BigArray& operator =(BigArray& array) { BigArray::copy(array); return *this; }
            inline BigArray& operator =(BigArray&& array) { BigArray::copy(array); return *this; }
            inline BigArray& operator =(BigArray const& array) { BigArray::copy(array); return *this; }
            inline BigArray& operator =(BigArray const&& array) { BigArray::copy(array); return *this; }
            inline type& operator [](size_t const index) const noexcept { return BigArray::at(index); }
            inline operator bool(void) const noexcept { return 0u ^ this -> length.value; }
    };

    /* Big Number --- NOTE (Lapys) -> Does not interact with numeric primitive types. */
    class BigNumber {
        // ...
        template <typename subtype, size_t limit>
        friend class BigArray;

        // [...]
        private:
            // Definition > (Characteristic, Mantissa, Type)
            typedef char type;

            BigArray<type> characteristic;
            BigArray<type> mantissa;
            enum {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;

            // (Definition, Function) > ...
            inline void add(BigNumber&) noexcept;
            inline void decrement(void) noexcept;
            inline void divide(BigNumber&) noexcept;
            inline void exponentiate(BigNumber&) noexcept;
            inline void increment(void) noexcept;
            inline void modulo(BigNumber&) noexcept;
            inline void multiply(BigNumber&) noexcept;
            inline void subtract(BigNumber&) noexcept;

            inline static BigNumber fromNumber(long double const) noexcept;
            inline bool hasSignificantCharacteristic(void) const noexcept { return this -> characteristic.size == 1u && '0' == *(this -> characteristic.value.at(0).value); }
            inline bool hasSignificantMantissa(void) const noexcept { return this -> mantissa.size == 1u && '0' == *(this -> characteristic.value.at(0).value); }

        // [...]
        public:
            // [Constructor]
            inline BigNumber(void) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} {}
            inline BigNumber(double const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(float const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(int const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(long const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(long double const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber(number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(short const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(unsigned int const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(unsigned long const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(unsigned short const number) : characteristic{'0'}, mantissa{'0'}, state{BigNumber::SAFE} { BigNumber const evaluation = BigNumber::fromNumber((long double) number); this -> characteristic = evaluation.characteristic; this -> mantissa = evaluation.mantissa; }
            inline BigNumber(BigNumber& number) : characteristic{number.characteristic}, mantissa{number.mantissa}, state{BigNumber::SAFE} {}
            inline BigNumber(BigNumber&& number) : characteristic{number.characteristic}, mantissa{number.mantissa}, state{BigNumber::SAFE} {}
            inline BigNumber(BigNumber const& number) : characteristic{number.characteristic}, mantissa{number.mantissa}, state{BigNumber::SAFE} {}
            inline BigNumber(BigNumber const&& number) : characteristic{number.characteristic}, mantissa{number.mantissa}, state{BigNumber::SAFE} {}

            // [Operator] > ...
            friend inline BigNumber operator +(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation += numberA; evaluation += numberB; return evaluation; }
            friend inline BigNumber operator +(BigNumber const& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation += numberA; evaluation += numberB; return evaluation; }
            friend inline BigNumber operator +(BigNumber&& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation += numberA; evaluation += numberB; return evaluation; }
            friend inline BigNumber operator +(BigNumber&& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation += numberA; evaluation += numberB; return evaluation; }
            friend inline BigNumber operator -(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation -= numberA; evaluation -= numberB; return evaluation; }
            friend inline BigNumber operator -(BigNumber const& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation -= numberA; evaluation -= numberB; return evaluation; }
            friend inline BigNumber operator -(BigNumber&& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation -= numberA; evaluation -= numberB; return evaluation; }
            friend inline BigNumber operator -(BigNumber&& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation -= numberA; evaluation -= numberB; return evaluation; }
            friend inline BigNumber operator *(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation *= numberA; evaluation *= numberB; return evaluation; }
            friend inline BigNumber operator *(BigNumber const& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation *= numberA; evaluation *= numberB; return evaluation; }
            friend inline BigNumber operator *(BigNumber&& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation *= numberA; evaluation *= numberB; return evaluation; }
            friend inline BigNumber operator *(BigNumber&& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation *= numberA; evaluation *= numberB; return evaluation; }
            friend inline BigNumber operator /(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation /= numberA; evaluation /= numberB; return evaluation; }
            friend inline BigNumber operator /(BigNumber const& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation /= numberA; evaluation /= numberB; return evaluation; }
            friend inline BigNumber operator /(BigNumber&& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation /= numberA; evaluation /= numberB; return evaluation; }
            friend inline BigNumber operator /(BigNumber&& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation /= numberA; evaluation /= numberB; return evaluation; }
            friend inline BigNumber operator %(BigNumber const& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation %= numberA; evaluation %= numberB; return evaluation; }
            friend inline BigNumber operator %(BigNumber const& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation %= numberA; evaluation %= numberB; return evaluation; }
            friend inline BigNumber operator %(BigNumber&& numberA, BigNumber const& numberB) noexcept { BigNumber evaluation; evaluation %= numberA; evaluation %= numberB; return evaluation; }
            friend inline BigNumber operator %(BigNumber&& numberA, BigNumber&& numberB) noexcept { BigNumber evaluation; evaluation %= numberA; evaluation %= numberB; return evaluation; }
            inline BigNumber& operator =(BigNumber const& number) noexcept { this -> characteristic = number.characteristic; this -> mantissa = number.mantissa; return *this; }
            inline BigNumber& operator =(BigNumber&& number) noexcept { this -> characteristic = number.characteristic; this -> mantissa = number.mantissa; return *this; }
            inline BigNumber& operator +=(BigNumber const& number) noexcept { BigNumber::add((BigNumber&) number); return *this; }
            inline BigNumber& operator +=(BigNumber&& number) noexcept { return BigNumber::operator +=((BigNumber const&) number); }
            inline BigNumber& operator -=(BigNumber const& number) noexcept { BigNumber::subtract((BigNumber&) number); return *this; }
            inline BigNumber& operator -=(BigNumber&& number) noexcept { return BigNumber::operator -=((BigNumber const&) number); }
            inline BigNumber& operator *=(BigNumber const& number) noexcept { BigNumber::multiply((BigNumber&) number); return *this; }
            inline BigNumber& operator *=(BigNumber&& number) noexcept { return BigNumber::operator *=((BigNumber const&) number); }
            inline BigNumber& operator /=(BigNumber const& number) noexcept { BigNumber::divide((BigNumber&) number); return *this; }
            inline BigNumber& operator /=(BigNumber&& number) noexcept { return BigNumber::operator /=((BigNumber const&) number); }
            inline BigNumber& operator %=(BigNumber const& number) noexcept { BigNumber::modulo((BigNumber&) number); return *this; }
            inline BigNumber& operator %=(BigNumber&& number) noexcept { return BigNumber::operator %=((BigNumber const&) number); }
            inline bool operator ==(BigNumber const&) const noexcept { return false; } // CHECKPOINT (Lapys)
            inline bool operator ==(BigNumber&& number) const noexcept { return BigNumber::operator ==((BigNumber const&) number); }
            inline bool operator !=(BigNumber const& number) const noexcept { return false == BigNumber::operator ==(number); }
            inline bool operator !=(BigNumber&& number) const noexcept { return false == BigNumber::operator ==(number); }
            inline BigNumber operator ++(int const) noexcept { BigNumber evaluation = *this; BigNumber::increment(); return evaluation; }
            inline BigNumber& operator ++(void) noexcept { BigNumber::increment(); return *this; }
            inline BigNumber operator --(int const) noexcept { BigNumber evaluation = *this; BigNumber::decrement(); return evaluation; }
            inline BigNumber& operator --(void) noexcept { BigNumber::increment(); return *this; }

            template <typename subtype, size_t limit>
            inline operator bool(void) const noexcept { return BigNumber::hasSignificantCharacteristic() && BigNumber::hasSignificantMantissa(); }
    };

/* Modification */
    /* Big Array */
        // Add
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::add(type& argument) noexcept {
            if (this -> length == limit) {
                ++(this -> depth);
                this -> length = 0u;
            }

            if (this -> depth == 1u) {
                ++(this -> length);
                ++(this -> size);

                (this -> value).add(argument);
            }

            else if (this -> size) {
                BigArrayObject *value = &(this -> value);
                for (size_t level = 2u; this -> depth ^ level; ++level) value = &(value -> at(0u));

                for (size_t iterator = 0u; value -> childrenLength ^ iterator; ++iterator) {
                    BigArrayObject& subvalue = value -> at(iterator);

                    if (subvalue.childrenLength ^ limit) {
                        ++(this -> length);
                        ++(this -> size);

                        subvalue.add(argument);
                        if (subvalue.childrenLength == limit) this -> length = 0u;

                        break;
                    }
                }
            }
        }

        template <typename type, size_t limit> constexpr inline void BigArray<type, limit>::add(void) const noexcept {}
        template <typename type, size_t limit> inline void BigArray<type, limit>::add(type&& value) noexcept { BigArray::add((type&) value); }
        template <typename type, size_t limit> template <typename subtype, typename... subtypes> inline void BigArray<type, limit>::add(subtype value, subtypes... values) noexcept { BigArray::add(value); BigArray::add(values...); }

        // At
        template <typename type, size_t limit>
        inline type& BigArray<type, limit>::at(size_t const index) const noexcept {}

        // Copy
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::copy(BigArray<type, limit> const&) noexcept {}

        // For Each
        template <typename type, size_t limit>
        template <typename subtype>
        inline void BigArray<type, limit>::foreach(subtype (&handler)(type&, size_t const)) const noexcept {}

        // Free
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::free(void) noexcept {}

        // Includes From End
        template <typename type, size_t limit>
        inline bool BigArray<type, limit>::includesFromEnd(type& value) const noexcept { return false; }

        template <typename type, size_t limit>
        inline bool BigArray<type, limit>::includesFromEnd(type&& value) const noexcept { return false; }

        // Includes From Start
        template <typename type, size_t limit>
        inline bool BigArray<type, limit>::includesFromStart(type& value) const noexcept { return false; }

        template <typename type, size_t limit>
        inline bool BigArray<type, limit>::includesFromStart(type&& value) const noexcept { return false; }

        // In
        template <typename type, size_t limit>
        inline type* BigArray<type, limit>::in(size_t const index, size_t indices...) const noexcept {}

        // Index From End
        template <typename type, size_t limit>
        inline size_t BigArray<type, limit>::indexFromEnd(type& value) const noexcept { return 0u; }

        template <typename type, size_t limit>
        inline size_t BigArray<type, limit>::indexFromEnd(type&& value) const noexcept { return 0u; }

        // Index From Start
        template <typename type, size_t limit>
        inline size_t BigArray<type, limit>::indexFromStart(type& value) const noexcept { return 0u; }

        template <typename type, size_t limit>
        inline size_t BigArray<type, limit>::indexFromStart(type&& value) const noexcept { return 0u; }

        // Is Empty --- MINIFY (Lapys)
        template <typename type, size_t limit> constexpr inline bool BigArray<type, limit>::isEmpty(BigArray const& array) noexcept { return 0u == array.size; }
        template <typename type, size_t limit> constexpr inline bool BigArray<type, limit>::isEmpty(BigArray&& array) noexcept { return BigArray::isEmpty((BigArray const&) array); }

        // Pop
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::pop(void) noexcept {}

        // Remove
        template <typename type, size_t limit>
        constexpr inline void BigArray<type, limit>::remove(void) const noexcept {}

        template <typename type, size_t limit>
        inline void BigArray<type, limit>::remove(type& value) noexcept {}

        template <typename type, size_t limit>
        inline void BigArray<type, limit>::remove(type&& value) noexcept {}

        template <typename type, size_t limit>
        template <typename subtype, typename... subtypes>
        inline void BigArray<type, limit>::remove(subtype value, subtypes... values) noexcept { BigArray::remove(value); BigArray::remove(values...); }

        // Resize
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::resize(size_t const length) noexcept {}

        template <typename type, size_t limit>
        inline void BigArray<type, limit>::resize(BigNumber const length) noexcept {}

        // Set
        template <typename type, size_t limit>
        inline void BigArray<type, limit>::set(type value, size_t const index) noexcept {}

    /* Big Number */
        // Add
        inline void BigNumber::add(BigNumber&) noexcept {}

        // Decrement
        inline void BigNumber::decrement(void) noexcept {}

        // Divide
        inline void BigNumber::divide(BigNumber&) noexcept {}

        // Exponentiate
        inline void BigNumber::exponentiate(BigNumber&) noexcept {}

        // From Number
        inline BigNumber BigNumber::fromNumber(long double const) noexcept { return BigNumber{}; }

        // Increment
        inline void BigNumber::increment(void) noexcept {}

        // Modulo
        inline void BigNumber::modulo(BigNumber&) noexcept {}

        // Multiply
        inline void BigNumber::multiply(BigNumber&) noexcept {}

        // Subtract
        inline void BigNumber::subtract(BigNumber&) noexcept {}

/* Main */
int main(void) {
    BigArray array;

    // Return
    return EXIT_SUCCESS;
}
