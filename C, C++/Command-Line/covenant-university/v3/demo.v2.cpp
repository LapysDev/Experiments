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

        // Initialization > (Shape) (Height, Width)
        Rectangle shape;
            double shapeHeight, shapeWidth;

        // Standard > C (Output, Input)
        std::cout << "Height: ";
        std::cin >> shapeHeight;

        // Shape > Set Height
        shape.setHeight(shapeHeight);

        // Standard > C (Output, Input)
        std::cout << "Width: ";
        std::cin >> shapeWidth;

        // Shape > Set Width
        shape.setWidth(shapeWidth);

        // Standard > C Output
        std::cout << std::endl << "Area: ";
        std::cout << shape.getArea();

        // Return
        return 0;
    }
