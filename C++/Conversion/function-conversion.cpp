#include <iostream>

struct function_pointer { friend int main(void);
    private:
        void (*value)(void);

        template <class subtype, class... types>
        struct function_t { typedef subtype (*type)(types...); };

        template <class subtype, class... types>
        struct vfunction_t { typedef subtype (*type)(types..., ...); };

    public:
        function_pointer(void);
        template <class type, class... types> function_pointer(type (*const value)(types...)) : value{(void (*)(void)) value} {}
        template <class type, class... types> function_pointer(type (*const value)(types..., ...)) : value{(void (*)(void)) value} {}

        template <class type, class... types> function_pointer& operator =(type (*const value)(types...)) const noexcept { this -> value = (void (*)(void)) value; return *this; }
        template <class type, class... types> function_pointer& operator =(type (*const value)(types..., ...)) const noexcept { this -> value = (void (*)(void)) value; return *this; }

        // inline operator typename function_t<void>::type(void) const noexcept { return (void (*)(void)) this -> value; }
        template <class type> inline operator type*(void) const noexcept { return (void*) this -> value; }
        // template <class... types> inline operator typename function_t<type, types...>::type(void) const noexcept { return (type (*)(types...)) this -> value; }
        // template <class type, class... types> inline operator typename vfunction_t<type, types...>::type(void) const noexcept { return (type (*)(types..., ...)) this -> value; }
};

void print(void) { std::cout << "[...]" << std::endl; }

int main(void) {
    std::cout.write("[PROGRAM INITIATED]", 20u);
    std::endl(std::cout);

    {
        void (*function)(void) = NULL;
        function_pointer pointer {print};

        // function = (void (*)(void)) pointer;
        function = (void (*)(void)) (void*) pointer;
        function();
    }

    std::cout.write("[PROGRAM TERMINATED]", 20u);
    std::flush(std::cout);
}
