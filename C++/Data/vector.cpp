template <class type>
class Vector {
    private:
        type *value;

        inline void allocate(size_t const length) noexcept {
            void *const allocation = ::realloc(this -> value, length * sizeof(type));
            if (NULL != allocation) { this -> value = (type*) allocation; }
        }

        constexpr inline static unsigned char count(void) const noexcept { return 0u; }
        template <class subtype, class... subtypes> constexpr inline static unsigned char count(void) const noexcept { return 1u + Vector::count<subtypes...>(); }

        constexpr void push(type* const value, void (*const Vector<type>::set)(type* const)) {
            Vector::allocate(this -> length + 1u);
            (this ->* set)(this -> value + this -> length++, value);
        }

    protected:
        constexpr inline bool assert(type index[], type* const value) const noexcept { return *index == *value; }
        constexpr inline bool compare(type index[], type* const value) const noexcept { return index == value || 0 == ::memcmp(index, value, sizeof(type)); }

        inline void copy(type index[], type* const value) { *index = *value; }
        constexpr inline void move(type index[], type* const value) noexcept { ::memmove(index, value, sizeof(type)); }

    public:
        struct length_accessor { friend Vector;
            private:
                size_t value;

                constexpr inline size_t& operator =(size_t const value) noexcept { return (this -> value = value); }
                constexpr inline size_t& operator +=(size_t const value) noexcept { return (this -> value += value); }
                constexpr inline size_t& operator -=(size_t const value) noexcept { return (this -> value -= value); }
                constexpr inline size_t& operator *=(size_t const value) noexcept { return (this -> value *= value); }
                constexpr inline size_t& operator /=(size_t const value) noexcept { return (this -> value /= value); }
                constexpr inline size_t& operator &=(size_t const value) noexcept { return (this -> value &= value); }
                constexpr inline size_t& operator |=(size_t const value) noexcept { return (this -> value |= value); }
                constexpr inline size_t& operator ^=(size_t const value) noexcept { return (this -> value ^= value); }
                constexpr inline size_t& operator <<=(size_t const value) noexcept { return (this -> value <<= value); }
                constexpr inline size_t& operator >>=(size_t const value) noexcept { return (this -> value >>= value); }
                constexpr inline size_t& operator ++(void) noexcept { return ++(this -> value); }
                constexpr inline size_t& operator ++(int const) noexcept { return this -> value++; }
                constexpr inline size_t& operator --(void) noexcept { return --(this -> value); }
                constexpr inline size_t& operator --(int const) noexcept { return this -> value--; }

            public:
                constexpr inline length_accessor(void) : value{} {}
                constexpr inline length_accessor(size_t const value) : value{value} {}

                constexpr inline operator size_t(void) const noexcept { return this -> value; }
        } length;

        inline Vector(Vector<type> const& vector) : value{NULL}, length{0u} { Vector::copy(vector); }
        inline Vector(Vector<type>&& vector) : value{vector.value}, length{vector.length} { vector.length = vector.value = 0x0; }
        template <class... subtypes> inline Vector(subtypes... values) : value{NULL}, length{0u} { Vector::allocate(Vector::count<subtypes...>()); Vector::add(values...); }

        inline ~Vector(void) { ::free(this -> value); }

        constexpr inline Vector& add(void) const noexcept { return *this; }
        constexpr Vector& add(type& value) noexcept { Vector::push(&value, Vector::move); return *this; }
        constexpr Vector& add(type&& value) noexcept { Vector::push(&value, Vector::copy); return *this; }
        template <class subtype, class... subtypes> inline Vector& add(subtype value, subtypes... values) { return Vector::add(value), Vector::add(values...); }

        inline Vector& copy(Vector<type> const& vector) noexcept { Vector::resize(vector.length); for (size_t iterator = vector.length; iterator--; ) Vector::move(this -> value + iterator, vector + iterator); }

        constexpr inline Vector& free(void) noexcept { ::free(this -> value); this -> length = this -> value = 0x0; }

        constexpr inline bool includes(type& value) const noexcept { return ~Vector::index(value); }
        constexpr inline bool includes(type&& value) const noexcept { return ~Vector::index((type&&) value); }

        constexpr inline ssize_t index(type& value) const noexcept { for (type *const end = this -> value + this -> length, *iterator = this -> value; end != iterator; ++iterator) { if (Vector::compare(iterator, &value)) return iterator - (this -> value); } return -1; }
        constexpr inline ssize_t index(type&& value) const noexcept { for (type *const end = this -> value + this -> length, *iterator = this -> value; end != iterator; ++iterator) { if (Vector::assert(iterator, &value)) return iterator - (this -> value); } return -1; }

        constexpr inline Vector& remove(type& value) noexcept { ssize_t const index = Vector::index(value); if (~index) { Vector::splice(index); } return *this; }
        constexpr inline Vector& remove(type&& value) noexcept { ssize_t const index = Vector::index((type&&) value); if (~index) { Vector::splice(index); } return *this; }

        constexpr inline Vector& sort(...) noexcept;
        constexpr inline Vector& resize(size_t const length) noexcept { Vector::allocate((this -> length = length)); return *this; }

        constexpr inline Vector& splice(size_t const index) noexcept { if (index < this -> length) { ::memmove(this -> value + index, this -> value + (index + 1u), this -> length - index); } return *this; }

        constexpr inline type* valueOf(void) const noexcept { return this -> value; }

        inline Vector& operator =(Vector<type> const& vector) { Vector::copy(vector); return *this; }
        inline Vector& operator =(Vector<type>&& vector) noexcept { this -> length = vector.length; this -> value = vector.value; vector.length = vector.value = 0x0; return *this; }
        template <class... subtypes> inline Vector& operator =(subtypes... values) { this -> length = 0u; Vector::allocate(Vector::count<subtypes...>()); Vector::add(values...); return *this; }
};
