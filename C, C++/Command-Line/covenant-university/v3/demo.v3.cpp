/* Library */
    // Input-Output Stream
    #include <iostream>

/* Global Data */
    // Rectangle
    class Rectangle {
        // [Private]
        private:
            // Initialization > (Height, Width)
            double height = 0,
                width = 0;

        // [Public]
        public:
            // Get Area
            double getArea() {
                // Return
                return (this -> height) * (this -> width);
            }

            // Get Height
            double getHeight(double height) {
                // Return
                return height;
            }

            // Get Width
            double getWidth(double width) {
                // Return
                return width;
            }

            // Set Height
            double setHeight(double height) {
                // Modification > Target > Height
                this -> height = height;

                // Return
                return height;
            }

            // Set Width
            double setWidth(double width) {
                // Modification > Target > Width
                this -> width = width;

                // Return
                return width;
            }
    };

/* Function */
    /* Main*/
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to work with a user-programmed C++ class" << std::endl << std::endl;

        // Initialization > (Rectangle (A, B)) (Height, Width)
        Rectangle rectangleA;
            double rectangleAHeight, rectangleAWidth;
        Rectangle rectangleB;
        double rectangleBHeight, rectangleBWidth;

        // Standard > C (Output, Input)
        std::cout << "Rectangle A Height: ";
        std::cin >> rectangleAHeight;

        // Rectangle A > Set Height
        rectangleA.setHeight(rectangleAHeight);

        std::cout << "Rectangle A Width: ";
        std::cin >> rectangleAWidth;

        // Rectangle A > Set Width
        rectangleA.setWidth(rectangleAWidth);

        // Standard > C Output
        std::cout << std::endl << "Rectangle A Area: ";
        std::cout << rectangleA.getArea();

        // Standard > C Output
        std::cout << std::endl << std::endl << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Rectangle B Height: ";
        std::cin >> rectangleBHeight;

        // Rectangle B > Set Height
        rectangleB.setHeight(rectangleBHeight);

        std::cout << "Rectangle B Width: ";
        std::cin >> rectangleBWidth;

        // Rectangle B > Set Width
        rectangleB.setWidth(rectangleBWidth);

        // Standard > C Output
        std::cout << std::endl << "Rectangle B Area: ";
        std::cout << rectangleB.getArea();

        // Return
        return 0;
    }
