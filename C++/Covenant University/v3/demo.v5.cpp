/* Library */
    // Input-Output Stream
    #include <iostream>

/* Global Data */
    // Circle
    class Circle {
        // [Private]
        private:
            // Initialization > Radius
            float radius;

        // [Public]
        public:
            // Get Area
            float getArea() {
                // Return
                return (22.0f / 7.0f) * (radius * radius);
            }

            // Set Radius
            void setRadius(float radius) {
                // Modification > Target > Radius
                this -> radius = radius;
            }
    };

/* Function */
    /* Main*/
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to work with a user-programmed C++ class" << std::endl << std::endl;

        // Initialization > Circle (Radius)
        Circle circle;
            float radius;

        // Standard > C (Output, Input)
        std::cout << "Radius: ";
        std::cin >> radius;

        // Circle > Set Radius
        circle.setRadius(radius);

        // Standard > C Output
        std::cout << "Area: ";
        std::cout << circle.getArea();

        // Return
        return 0;
    }
