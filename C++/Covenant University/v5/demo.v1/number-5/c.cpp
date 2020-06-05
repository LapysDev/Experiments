/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    // Item
    class Item {
        private:
            long double unitPrice = 0;
            unsigned int tally = 0;
            string itemName;

        public:
            Item(string itemName = "", long double unitPrice = 0, unsigned int tally = 1) {
                this -> itemName = itemName;
                this -> tally = tally;
                this -> unitPrice = unitPrice;
            }

            void decreaseStock(int stock) { decreaseStock((unsigned int)stock); }
            void decreaseStock(unsigned int stock) {
                (int) this -> tally - stock < 0 ?
                    throw "Error, cannot decrease stock by that amount" :
                    this -> tally -= stock;
            }

            long double getAssetValue() { return (long double) tally * unitPrice; }

            void increaseStock(int stock) { increaseStock((unsigned int) stock); }
            void increaseStock(unsigned int stock) { this -> tally += stock; }
    };

/* Function */
    // Main
    int main() {
        // Initialization > (Item Name, Object)
        string itemName = "Tesla Model S";
        Item obj = Item(itemName, 4.5e7, 1);

        // Object > (Increase, Decrease) Stock
        obj.increaseStock(10);
        obj.decreaseStock(5);

        // C Output
        cout << "Current price for " <<  itemName << ": " << obj.getAssetValue();

        // Return
        return 0;
    }
