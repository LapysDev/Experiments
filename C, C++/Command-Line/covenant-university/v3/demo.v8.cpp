/* Library */
    // Input-Output Stream
    #include <iostream>

/* Global Data */
    // Person
    class Person {
        // [Private]
        private:
            // Initialization > Age
            int Age = 0;

        // [Public]
        public:
            // Function
                // Get Age
                int get_age() {
                    // Return
                    return this -> Age;
                }

                // Set Age
                void set_age(int n) {
                    // Modification > Target > Age
                    this -> Age = n;
                }
    };

/* Function */
    /* Main*/
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to work with a user-programmed C++ class" << std::endl << std::endl;

        // Initialization > Person (A, B)
        Person personA, personB;
            // Person (A, B) Age
            int personAAge, personBAge;

        // Standard > C (Output, Input)
        std::cout << "Person A > Age: ";
        std::cin >> personAAge;

        std::cout << "Person B > Age: ";
        std::cin >> personBAge;

        // Person (A, B) > Set Age
        personA.set_age(personAAge);
        personB.set_age(personBAge);

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        personAAge > personBAge ?
            std::cout << "Person A is older than Person B" :
            std::cout << "Person B is older than Person A";

        // Return
        return 0;
    }
