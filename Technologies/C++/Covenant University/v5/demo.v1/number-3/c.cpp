/* Header Files */
    // Input-Output Stream
    #include <iostream>

    // String
    #include <string>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    // Circle
    class Circle {
        private:
            double radius; string color;

        // [Public]
        public:
            // [Constructor]
            Circle(double r = 1.0, string c = "red") {
                // Modification > Target > (Radius, Color)
                radius = r;
                color = c;
            }

            // Function
                // Get Radius
                double getRadius() { return radius; }

                // Get Color
                string getColor() { return color; }

                // Get Area
                double getArea() { return radius * radius * 3.1416; }
    };

/* Function */
    // Main
    int main() {
        // Initialization > Circle
        Circle circle = Circle(10, "red");

        // Circle > Get (Radius, Color, Area)
        cout << "Radius: " << circle.getRadius() << endl;
        cout << "Color: " << circle.getColor() << endl;
        cout << "\nArea: " << circle.getArea() << endl;

        // Return
        return 0;
    }
