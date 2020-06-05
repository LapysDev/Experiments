/* Library */
    // Input-Output Stream
    #include <iostream>

/* Global Data */
    // Account, Person
    class Account;
    class Person;

    // Account
    class Account {
        // [Private]
        private:
            // Initialization > (Balance, Owner, Name, Passkey)
            long double balance = 0;
            Person* owner;
            char passkey[4];
            std::string name = "";

        // [Public]
        public:
            // [Constructor]
            template <typename data>
            Account(Person& owner, data balance = 0.00) {
                // Set (Balance, Owner)
                setBalance(balance);
                setOwner(owner);
            }

            // Function
                // Deposit
                template <typename data>
                long double deposit(data amount) {
                    // Modification > Target > Balance
                    this -> balance = getBalance() + static_cast<long double>(amount);

                    // Return
                    return getBalance();
                }

                // Get Balance
                long double getBalance() {
                    // Return
                    return this -> balance;
                }

                // Get Name
                std::string getName() {
                    // Return
                    return this -> name;
                }

                // Get Owner
                Person& getOwner() {
                    // Return
                    return *(this -> owner);
                }

                // Get Passkey
                std::string getPasskey() {
                    // Initialization > (Passkey, Stream)
                    char* passkey = this -> passkey;
                    std::string stream = "";

                    // Update > Stream
                    stream += *passkey;
                    stream += *(passkey + 1);
                    stream += *(passkey + 2);
                    stream += *(passkey + 3);

                    // Return
                    return stream;
                }

                // Is In Debt
                bool isInDebt() {
                    // Initialization > Balance
                    long double balance = getBalance();

                    // Return
                    return balance < 0;
                }

                // Set Balance
                template <typename data>
                long double setBalance(data balance) {
                    // Modification > Target > Balance
                    this -> balance = getBalance() + static_cast<long double>(balance);

                    // Return
                    return getBalance();
                }

                // Set Name
                std::string setName(std::string name) {
                    // Modification > Target > Name
                    this -> name = name;

                    // Return
                    return getName();
                }

                // Set Owner
                Person& setOwner(Person& person) {
                    // Modification > Target > Person
                    this -> owner = &person;

                    // Return
                    return getOwner();
                }

                // Set Passkey
                std::string setPasskey(int key1, int key2, int key3, int key4) {
                    // Initialization > Pass Key
                    char* passkey = this -> passkey;

                    // Update > Pass Key
                    *passkey = key1;
                    *(passkey + 1) = key2;
                    *(passkey + 2) = key3;
                    *(passkey + 3) = key4;

                    // Return
                    return getPasskey();
                }

                // Transfer Amount
                template <typename data>
                long double transferAmount(Account& account, data amount) {
                    // Account > Deposit
                    account.deposit(amount);

                    // Withdraw
                    withdraw(amount);

                    // Return
                    return getBalance();
                }

                // Withdraw
                template <typename data>
                long double withdraw(data amount) {
                    // Modification > Target > Balance
                    this -> balance = getBalance() - static_cast<long double>(amount);

                    // Return
                    return getBalance();
                }
    };

    // Person
    class Person {
        // [Private]
        private:
            // Initialization > (Age, Name)
            long double age = 0;
            std::string name = "";

        // [Public]
        public:
            // [Constructor]
            Person(std::string name = "", long double age = 0) {
                // Modification > Target > (Age, Name)
                this -> age = age;
                this -> name = name;
            }

            // Function
                // Get Age
                long double getAge() {
                    // Return
                    return this -> age;
                }

                // Get Name
                std::string getName() {
                    // Return
                    return this -> name;
                }

                // Set Age
                long double setAge(long double age) {
                    // Modification > Target > Age
                    this -> age = age;

                    // Return
                    return getAge();
                }

                // Set Name
                std::string setName(std::string name) {
                    // Modification > Target > Name
                    this -> name = name;

                    // Return
                    return getName();
                }
    };

/* Function */
    /* Main*/
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to work with a user-programmed C++ class" << std::endl << std::endl;

        // Initialization > (Lapys, Jyrsper) (Account)
        Person lapys = Person("Lapys", 22);
            Account lapysAccount = Account(lapys, 10000);
        Person jyrsper = Person("Jyrsper", 22);
            Account jyrsperAccount = Account(jyrsper, 100000);

        // Standard > C Output
        std::cout << "Lapys   > Name: " << lapys.getName() << std::endl;
        std::cout << "Jyrsper > Name: " << jyrsper.getName() << std::endl;

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "Lapys` Account    > Balance: " << lapysAccount.getBalance() << std::endl;
        std::cout << "Jyrsper`s Account > Balance: " << jyrsperAccount.getBalance() << std::endl;

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "--- Jyrsper transfers " << (jyrsperAccount.getBalance() / 2) << " to Lapys ---" << std::endl;

        // Jyrsper Account > Transfer Amount > Lapys Account
        jyrsperAccount.transferAmount(lapysAccount, jyrsperAccount.getBalance() / 2);

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "Lapys` Account    > Balance: " << lapysAccount.getBalance() << std::endl;
        std::cout << "Jyrsper`s Account > Balance: " << jyrsperAccount.getBalance() << std::endl;

        // Return
        return 0;
    }
