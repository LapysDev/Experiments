/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library

/* Class > Accessor */
struct accessor {
    // [...]
    private:
        // Initialization > (Accessible, Value)
        bool accessible;
        void *value;

    // [...]
    public:
        // [Constructor]
        inline accessor() : accessible{false}, value{NULL} {}

        // [Destructor]
        ~accessor() { std::free(this -> value); }

        // [Operator]
            // [*]
            inline void operator *() const { return this -> value; }
};

/* Main */
int main(void) {
    // Return
    return 0;
}
