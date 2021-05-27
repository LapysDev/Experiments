public class EmployeeOffice {
    private static class Employee {
        String name;
        int id;
        String department;
        String profession;

        Employee(String name, int id, String department, String profession) {
            this.department = department;
            this.name = name;
            this.id = id;
            this.profession = profession;
        }
    };

    public static void main(String[] arguments) {
        Employee[] employees = {
            new Employee("Susan Meyers", 47899, "Accounting", "Vice President"),
            new Employee("Mark Jones", 39119, "IT", "Programmer"),
            new Employee("Joy Rogers", 81774, "Marketing", "Engineer")
        };

        for (Employee employee : employees)
        System.out.println("[Employee (" + employee.id + ")]: " +
            "\"" + employee.name + "\" {" +

            "department: \"" + employee.department + "\", " +
            "profession: \"" + employee.profession + "\"" +
        "}");
    }
};
