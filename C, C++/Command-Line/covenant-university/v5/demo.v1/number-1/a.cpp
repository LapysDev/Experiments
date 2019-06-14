/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    // Employee
    class Employee {
        // [Private]
        private:
            // Initialization > (ID, Monthly Salary, Name)
            unsigned int id = 0;
            long double monthlySalary = 0;
            string name;

        // [Public]
        public:
            // [Constructor]
            Employee() {}

            // Function
                // Get ID
                unsigned int getId() { return this -> id; }

                // Get Monthly Salary
                long double getMonthlySalary() { return this -> monthlySalary; }

                // Get Name
                string getName() { return this -> name; }

                // Print
                void print() {
                    // C Output
                    cout <<
                        "Name: " << this -> name << endl <<
                        "ID: " << this -> id << endl <<
                        "Monthly Salary: " << this -> monthlySalary << endl;
                }

                // Set ID
                void setId(unsigned int id) { this -> id = id; }

                // Set Monthly Salary
                void setMonthlySalary(long double monthlySalary) { this -> monthlySalary = monthlySalary; }

                // Set Name
                void setName(string name) { this -> name = name; }
    };

/* Function */
    // Main
    int main() {
        // Initialization > Employee (1, 2)
        Employee employee1, employee2;

        // Employee (1, 2) > Set Monthly Salary
        employee1.setMonthlySalary(13265);
        employee2.setMonthlySalary(12750);

        // C Output
        cout <<
            "Employee 1 Yearly Salary: " << employee1.getMonthlySalary() * 12 << endl <<
            "Employee 2 Yearly Salary: " << employee2.getMonthlySalary() * 12 << endl;

        // C Output
        cout << endl;

        // Employee (1, 2) > Set Monthly Salary
        employee1.setMonthlySalary(employee1.getMonthlySalary() * 1.1);
        employee2.setMonthlySalary(employee2.getMonthlySalary() * 1.1);

        // C Output
        cout <<
            "Employee 1 Yearly Salary: " << employee1.getMonthlySalary() * 12 << endl <<
            "Employee 2 Yearly Salary: " << employee2.getMonthlySalary() * 12 << endl;

        // Return
        return 0;
    }
