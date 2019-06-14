/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    /* Money
            --- NOTE ---
                #Lapys: Which is really just fiat currency.
    */
    class Money {
        // [Private]
        private:
            // Initialization > (Kobo, Naira)
            int kobo = 0, naira = 0;

        // [Public]
        public:
            // [Constructor]
            Money(int naira = 0, int kobo = 0) {
                // Target > Set (Naira, Kobo)
                this -> setNaira(naira);
                this -> setKobo(kobo);
            }

            // [Operator] > [+]
            Money operator +(Money arg) {
                // Return
                return Money(this -> naira + arg.naira, this -> kobo + arg.kobo);
            }

            // Function
                // Get (Kobo, Naira)
                int getKobo() { return this -> kobo; }
                int getNaira() { return this -> naira; }

                // Print
                void print() { cout << this -> getNaira() << '.' << this -> getKobo() << " Naira"; }

                // Set (Kobo, Naira)
                void setKobo(int kobo) {
                    // Loop
                    while (kobo > 100 && kobo - 100 > 0) {
                        // Target > Set Naira
                        this -> setNaira(this -> getNaira() + 1);

                        // Update > Kobo
                        kobo -= 100;
                    }

                    // Modification > Target > Kobo
                    this -> kobo = kobo;
                }
                void setNaira(int naira) { this -> naira = naira; }
    };

/* Function */
    // Main
    int main() {
        // Initialization > M
        Money m(2, 99);

        // (...)
        (m + m + m).print();

        // Return
        return 0;
    }
