#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Get length of string.
unsigned length(const char string[]) { unsigned stringLength = 0; while (string[stringLength] != '\0') stringLength += 1; return stringLength; }

// Convert character to string.
char* characterToString(char character) {
    char* string = (char*) malloc(2);
    string[0] = character;
    string[1] = '\0';
    return string;
}

// Compare two strings.
bool compare(const char stringA[], const char stringB[]) { return !strcmp(stringA, stringB); }

// Print newline
void printn() { printf("%s", "\n"); fflush(stdout); }

// Concatenate two strings.
char* concat(const char stringA[], const char stringB[]) {unsigned stringLength = length(stringA) + length(stringB); char* string = (char*) malloc(stringLength + 1); string[stringLength] = '\0'; strcpy(string, stringA); strcat(string, stringB); return string; }

char* convertToString(unsigned arg) {
    char* string = (char*) malloc(255);
    sprintf(string, "%u", arg);
    string[255] = '\0';
    return string;
}

// Convert digit to character.
char digitToCharacter(unsigned digit) { switch (digit) { case 0: return '0'; case 1: return '1'; case 2: return '2'; case 3: return '3'; case 4: return '4'; case 5: return '5'; case 6: return '6'; case 7: return '7'; case 8: return '8'; case 9: return '9'; default: return '\0'; } }

class Account {
    private:
        char* address = NULL, *name = NULL;
        double balance = 0;
        signed ID = 0;
        char PIN[4] {'0', '0', '0', '0'};

    public:
        explicit Account() {}
        explicit Account(const char name[], char* PIN, double balance = 0) { this -> deposit(balance); this -> setName(name); this -> setPIN(PIN); }
        Account(const Account& account) { this -> setBalance(account.checkBalance()); }

        ~Account() { (NULL == this -> address) || (this -> address = NULL); std::free(this -> address); (NULL == this -> name) || (this -> name = NULL); std::free(this -> name); }

        const double checkBalance() const { return this -> balance; }
        char* getAddress() { return this -> address; }
        signed getID() { return this -> ID; }
        char* getName() { return this -> name; }
        char* getPIN() { return this -> PIN; }
        char* getReadablePIN() { return concat(concat("[", concat(concat(concat(characterToString(this -> PIN[0]), characterToString(this -> PIN[1])), characterToString(this -> PIN[2])), characterToString(this -> PIN[3]))), "]"); }

        friend signed generateRandomAccountID(Account& account) { return rand() % 100000 + 1; }
        friend char* generateRandomAccountPIN(Account& account) { static char PIN[4] {digitToCharacter(rand() % 10 + 1), digitToCharacter(rand() % 10 + 1), digitToCharacter(rand() % 10 + 1), digitToCharacter(rand() % 10 + 1)}; return PIN; }

        void setBalance(double balance) { this -> balance = balance; }
        void setID(signed ID) { this -> ID = ID; }
        void setName(const char name[]) { this -> name = (char*) name; }
        void setPIN(char* PIN) { this -> setPIN(PIN[0], PIN[1], PIN[2], PIN[3]); }
        void setPIN(char pinNumberA, char pinNumberB, char pinNumberC, char pinNumberD) { *(this -> PIN) = pinNumberA; *(this -> PIN + 1) = pinNumberB; *(this -> PIN + 2) = pinNumberC; *(this -> PIN + 3) = pinNumberD; }

        double deposit(double amount) { return (this -> balance += amount); }
        double transfer(Account& account, double amount) { account.deposit(amount); this -> withdraw(amount); return this -> balance; }
        double withdraw(double amount) { return (this -> balance = this -> balance - amount < 0 ? 0 : this -> balance - amount); }

        char* toString() { return concat("[", concat(concat(concat(this -> getName(), " : "), convertToString(this -> getID())), "]")); }
};

class ATMSession {
    private:
        Account account;

        void displayDepositMenu() {
            double depositAmount = 0;

            this -> clearView();
            this -> displayTitle("Deposit");

            printn(); printf("Balance: %f\n", (this -> account).checkBalance());
            printn(); printf("Deposit Amount: "); scanf("%lf", &depositAmount);

            this -> displayDepositSuccessfulMenu(depositAmount);
        }

        void displayDepositSuccessfulMenu(double depositAmount) {
            const char* OPTIONS[1] {"Return"};

            this -> clearView();
            this -> displayTitle("Deposit Successful");

            printn();
            printf("You have successfully deposited %f into your account.\n", depositAmount);

            (this -> account).deposit(depositAmount);

            printn(); printf("Balance: %f\n", (this -> account).checkBalance());

            char* choice = this -> displayInquiredOptions(OPTIONS, 1);

            if (compare(choice, "Return")) this -> displayIntroductionMenu();
        }

        void displayIntroductionMenu() {
            char* accountName = (this -> account).getName();
            const char* OPTIONS[5] {"Inquiry", "Deposit", "Transfer", "Withdraw", "Cancel Session"};
            char TITLE[9 + strlen(accountName) + 1];

            strcpy(TITLE, "Welcome, ");
            strcat(TITLE, accountName);

            char* choice = this -> displayViewWithInquiredOptions(TITLE, OPTIONS, 5);

            if (compare(choice, "Cancel Session")) this -> endSession();
            else if (compare(choice, "Deposit")) this -> displayDepositMenu();
            else if (compare(choice, "Inquiry")) this -> displayInquiryMenu();
            else if (compare(choice, "Transfer")) this -> displayTransferMenu();
            else if (compare(choice, "Withdraw")) this -> displayWithdrawMenu();
        }

        void displayInquiryMenu() {
            const char* OPTIONS[1] {"Return"};

            this -> clearView();
            this -> displayTitle("Inquiry");
            printn(); printf("Balance: %f\n", (this -> account).checkBalance());
            char* choice = this -> displayInquiredOptions(OPTIONS, 1);

            if (compare(choice, "Return")) this -> displayIntroductionMenu();
        }

        void displayTransferMenu() {
            double transferAmount = 0;
            char* recipientAccountName = (char*) malloc(255);
            unsigned recipientID = 0;

            this -> clearView();
            this -> displayTitle("Transfer");

            printn();
            printf("Balance: %f\n", (this -> account).checkBalance());

            printn();
            printf("Recipient's Name: "); scanf("%s", &recipientAccountName);
            printf("Recipient's Account Number: "); scanf("%u", &recipientID);

            printn();
            printf("Transfer Amount: "); scanf("%lf", &transferAmount);

            Account recipient(recipientAccountName, generateRandomAccountPIN(recipient));
            recipient.setID(recipientID);

            this -> displayTransferSuccessfulMenu(recipient, transferAmount);
        }

        void displayTransferSuccessfulMenu(Account& recipient, double transferAmount) {
            const char* OPTIONS[1] {"Return"};

            this -> clearView();
            this -> displayTitle("Transfer Successful");

            printn();
            printf("You have successfully transferred %f to the account %s.\n", transferAmount, recipient.toString());

            (this -> account).transfer(recipient, transferAmount);

            printn(); printf("Balance: %f\n", (this -> account).checkBalance());

            char* choice = this -> displayInquiredOptions(OPTIONS, 1);

            if (compare(choice, "Return")) this -> displayIntroductionMenu();
        }

        void displayWithdrawMenu() {
            const char* OPTIONS[10] {
                "1000", "2000", "3000", "5000", "10000", "20000", "30000", "40000",
                "Other", "Return"
            };

            this -> clearView();
            this -> displayTitle("Withdraw");

            printn(); printf("Balance: %f\n", (this -> account).checkBalance());

            char* choice = this -> displayInquiredOptions(OPTIONS, 10);

            if (compare(choice, "1000")) this -> displayWithdrawalSuccessfulMenu(1000);
            else if (compare(choice, "2000")) this -> displayWithdrawalSuccessfulMenu(2000);
            else if (compare(choice, "3000")) this -> displayWithdrawalSuccessfulMenu(3000);
            else if (compare(choice, "5000")) this -> displayWithdrawalSuccessfulMenu(5000);
            else if (compare(choice, "10000")) this -> displayWithdrawalSuccessfulMenu(10000);
            else if (compare(choice, "20000")) this -> displayWithdrawalSuccessfulMenu(20000);
            else if (compare(choice, "30000")) this -> displayWithdrawalSuccessfulMenu(30000);
            else if (compare(choice, "40000")) this -> displayWithdrawalSuccessfulMenu(40000);
            else if (compare(choice, "Other")) this -> displayWithdrawalAmountMenu();
            else if (compare(choice, "Return")) this -> displayIntroductionMenu();
        }

        void displayWithdrawalAmountMenu() {
            bool specifiedInvalidWithdrawalAmount = false;
            double withdrawalAmount = 0;

            this -> clearView();
            this -> displayTitle("Key in Withdrawal Amount");

            printn();

            while (
                withdrawalAmount != (unsigned) withdrawalAmount ||
                (withdrawalAmount ? (unsigned) withdrawalAmount % 500 : true) ||
                withdrawalAmount > 40000
            ) {
                specifiedInvalidWithdrawalAmount ?
                    printf("Withdrawal Amount (in multiples of 500): ") :
                    printf("Withdrawal Amount: ");
                scanf("%lf", &withdrawalAmount);
                specifiedInvalidWithdrawalAmount = true;
            }

            this -> displayWithdrawalSuccessfulMenu(withdrawalAmount);
        }
        void displayWithdrawalSuccessfulMenu(double withdrawalAmount) {
            const char* OPTIONS[1] {"Return"};

            this -> clearView();
            this -> displayTitle("Withdrawal Successful");

            printn();
            printf("You have successfully withdrawn %f from your account.\n", withdrawalAmount);

            (this -> account).withdraw(withdrawalAmount);

            printn(); printf("Balance: %f\n", (this -> account).checkBalance());

            char* choice = this -> displayInquiredOptions(OPTIONS, 1);

            if (compare(choice, "Return")) this -> displayIntroductionMenu();
        }

        void clearView() { system("cls"); }
        char* displayInquiredOptions(const char* OPTIONS[], unsigned OPTIONS_LENGTH) {
            this -> displayOptions(OPTIONS, OPTIONS_LENGTH);
            return (char*) this -> inquireOptions(OPTIONS, OPTIONS_LENGTH);
        }
        void displayOptions(const char* OPTIONS[], unsigned OPTIONS_LENGTH) {
            printn();

            if (OPTIONS_LENGTH) {
                unsigned iterator = OPTIONS_LENGTH;
                while (iterator) {
                    unsigned index = OPTIONS_LENGTH - (iterator -= 1) - 1;
                    const char* option = OPTIONS[index];
                    printf("    .%u) %s\n", index + 1, option);
                }
            }
        }
        void displayTitle(const char* TITLE) { printf("===== %s =====\n", TITLE); }
        char* displayViewWithInquiredOptions(const char* TITLE, const char* OPTIONS[], unsigned OPTIONS_LENGTH) {
            this -> clearView();
            this -> displayTitle(TITLE);
            return this -> displayInquiredOptions(OPTIONS, OPTIONS_LENGTH);
        }
        void endSession() {
            this -> clearView();
            this -> displayTitle("GOODBYE");
            printf("Thank you for using our services, %s.\n", (this -> account).getName());
            printf("%s", "Please come back next time.\n");
        }
        const char* inquireOptions(const char* OPTIONS[], unsigned OPTIONS_LENGTH) {
            if (OPTIONS_LENGTH) {
                unsigned choiceIndex = 0; bool selectedInvalidOption = false;
                printn();

                while (!choiceIndex || choiceIndex > OPTIONS_LENGTH) {
                    selectedInvalidOption ?
                        printf("Please key in a number between 1-%u to select an option: ", OPTIONS_LENGTH) :
                        printf("Please select an option: ");
                    scanf("%u", &choiceIndex);
                    selectedInvalidOption = true;
                }

                return OPTIONS[choiceIndex - 1];
            }

            return NULL;
        }

    public:
        ATMSession(Account& account) {
            this -> account = account;
            this -> displayIntroductionMenu();
        }
};

int main(int argc, char* argv[]) {
    Account account("Tony Stark", generateRandomAccountPIN(account), 1e6);

    new ATMSession(account);

    return 0;
}
