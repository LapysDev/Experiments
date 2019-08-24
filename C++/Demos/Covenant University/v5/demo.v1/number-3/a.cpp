/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    // Demo
    class Demo {
        // [Private]
        private:
            // Initialization > (X, Y)
            int X = 0, Y = 0;

        // [Public]
        public:
            // [Constructor]
            Demo() {};
            Demo(int a, int b) { X = a; Y = b; };

            // Function > Display
            void display() { cout << "X: " << X << ", " << "Y: " << Y << endl; }
    };

/* Function */
    // Main
    int main() {
        // Initialization > Demo (A, B)
        Demo demoA = Demo(), demoB = Demo(2, 3);

        // Demo (A, B) > Display
        demoA.display();
        demoB.display();

        // Return
        return 0;
    }
