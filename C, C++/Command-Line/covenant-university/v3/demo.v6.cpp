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

        // Initialization > (Circle (A, B)) (Radius)
        Circle circleA;
            float circleARadius = 14;
        Circle circleB;
            float circleBRadius = 27;

        // Standard > C Output
        std::cout << "Circle A Radius: ";
        std::cout >> circleARadius;

        // Circle > Set Radius
        circleA.setRadius(circleARadius);

        // Standard > C Output
        std::cout << "Circle A Area: ";
        std::cout << circleA.getArea();

        // Standard > C Output
        std::cout << std::endl << std::endl;

        // Standard > C Output
        std::cout << "Circle B Radius: ";
        std::cout >> circleBRadius;

        // Circle > Set Radius
        circleB.setRadius(circleBRadius);

        // Standard > C Output
        std::cout << "Circle B Area: ";
        std::cout << circleB.getArea();

        // Standard > C Output
        std::cout << std::endl << std::endl;

        // Return
        return 0;
    }
