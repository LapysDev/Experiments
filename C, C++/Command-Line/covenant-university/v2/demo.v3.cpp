/* Library Files */
    // Input-Output Stream
    #include <iostream>

    // Time Header
    #include <time.h>

/* Global Data */
    // Date
    class Date {
        // [Public]
        public:
            // Day, Month, Year
            int day, month, year;

            // [Constructor]
            Date() {};
            Date(int month, int day, int year) {
                // Modification > Target > (Day, Month, Year)
                this -> day = day;
                this -> month = month;
                this -> year = year;
            };

            // Set Day
            void setDay(int day) { this -> day = day; };

            // Set Month
            void setMonth(int month) { this -> month = month; };

            // Set Year
            void setYear(int year) { this -> year = year; };
    };

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > ((Local) Time, (Birth, Current) Date, Month, Day, Year)
        time_t Time = time(NULL);
        struct tm *LocalTime = localtime(&Time);
        Date birthDate, currentDate(LocalTime -> tm_mon + 1, LocalTime -> tm_mday, LocalTime -> tm_year + 1900);
        int month, day, year;

        // Standard > C (Input, Output)
        std::cout << "Program to calculate number of days & leap years passed since birth\n\n" << std::endl;
        std::cout << "Input your birth month: ";
        std::cin >> month;
        std::cout << std::endl;
        std::cout << "Input your birth year: ";
        std::cin >> year;
        std::cout << std::endl;
        std::cout << "Input your birth day: ";
        std::cin >> day;

        // Birth Date > (Month, Day, Year)
        birthDate.setMonth(month);
        birthDate.setDay(day);
        birthDate.setYear(year);

        // Standard > C (Input, Output)
        std::cout << std::endl;
        std::cout << "\nIt has been " << (((currentDate.year * 365) + (currentDate.month * 30) + currentDate.day) - ((birthDate.year * 365) + (birthDate.month * 30) + birthDate.day)) << " days since your birth and" << std::endl;
        std::cout << "    " << ((currentDate.year - birthDate.year) / 4) << " leap years since as well.";

        // Return
        return 0;
    }
