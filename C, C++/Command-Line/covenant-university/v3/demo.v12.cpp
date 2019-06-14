/* Library */
    // Input-Output Stream
    #include <iostream>

    // Lapys Header
    #include "lapys (2018 - Q4).h"

/* Global Data */
    // Vector
    class Vector {
        private:
            String type = "2D";

        public:
            Number x, y;

            Vector() {}
            Vector(Number x) { setValues(x); }
            Vector(Number x, Number y) { setValues(x, y); }
            Vector(Number x, Number y, String type) {
                setValues(x, y);
                (type == "2D" || type == "3D") && (this -> type = type);
            }

            String printValues() {
                String values = "X: ";
                values += this -> x;
                values += ", Y: ";
                values += this -> y;

                print(values);
                return values;
            }
            void resetValues() { this -> x = 0; this -> y = 0; }
            void setValues(Number x) { this -> x = x; }
            void setValues(Number x, Number y) { this -> x = x; this -> y = y; }
    };

/* Function */
    /* Main */
    int main(int argc, char* argv[]) {
        // {Title} Print Line
        printl("Program to use overloaded functions in C++:\n");

        Vector vector;

        vector.setValues(2);
        vector.printValues();

        printl();
        vector.resetValues();

        vector.setValues(2, 3);
        vector.printValues();

        // Return
        return 0;
    }
