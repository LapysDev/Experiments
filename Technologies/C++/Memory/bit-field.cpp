/* Import */
#include <iostream> // Input-Output Stream

/* Class > Boolean */
class Boolean {
    // [...]
    private:
        // Initialization > Value
        unsigned char value : 1;

    // [...]
    public:
        // [Constructor]
        inline Boolean() : value(0u) {}
        inline Boolean(const unsigned char value) : value(!!value) {}

        inline Boolean(Boolean& boolean) : value(boolean.value) {}
        inline Boolean(const Boolean& boolean) : value(boolean.value) {}

        // [Operator]
            // [=]
            inline Boolean& operator =(const unsigned char value) { this -> value = !!value; return *this; }

            inline Boolean& operator =(Boolean& boolean) { this -> value = boolean.value; return *this; }
            inline Boolean& operator =(const Boolean& boolean) { this -> value = boolean.value; return *this; }

            // [+=]
            inline Boolean& operator +=(const unsigned char value) { this -> value += value; return *this; }

            // [<<]
            friend std::ostream& operator <<(std::ostream& outputStream, Boolean& boolean) { outputStream << (boolean.value ? "true" : "false"); return outputStream; }
            friend std::ostream& operator <<(std::ostream& outputStream, const Boolean& boolean) { outputStream << (boolean.value ? "true" : "false"); return outputStream; }

            // [...]
            operator unsigned char() const { return this -> value; }
};

/* Main */
int main(void) {
    // Initialization > Boolean
    Boolean boolean;

    // ...
    std::cout << "Boolean: " << boolean << std::endl;
    std::cout << "Boolean (+= 1): " << (boolean += 1u) << std::endl;
    std::cout << "Boolean (+= 3): " << (boolean += 3u) << std::endl;

    // Return
    return 0;
}
