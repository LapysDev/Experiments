/* Library */
    // Input-Output Stream
    #include <iostream>

/* Global Data */
    // Parallelogram
    class Parallelogram {
        // [Private]
        private:
            // Initialization > (Base, Height)
            float base = 0,
                height = 0;

        // [Public]
        public:
            // Get Area
            float getArea() {
                // Return
                return (this -> base) * (this -> height);
            }

            // Set Base-Height
            void setBaseHeight(float base, float height) {
                this -> base = base;
                this -> height = height;
            }
    };

/* Function */
    /* Main*/
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to work with a user-programmed C++ class" << std::endl << std::endl;

        // Initialization > Parallelogram (Base, Height)
        Parallelogram parallelogram;
            float parallelogramBase,
                parallelogramHeight;

        // Standard > C (Output, Input)
        std::cout << "Parallelogram Base: ";
        std::cin >> parallelogramBase;

        // Standard > C (Output, Input)
        std::cout << "Parallelogram Height: ";
        std::cin >> parallelogramHeight;

        // Parallelogram > Set Base-Height
        parallelogram.setBaseHeight(parallelogramBase, parallelogramHeight);

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "Parallelogram Area: ";
        std::cout << parallelogram.getArea();

        // Return
        return 0;
    }
