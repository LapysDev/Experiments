#include <iostream>

class Person {
    private:
        const std::string name = "Person";
        const unsigned int age = 0u;

    public:
        inline Person(std::string name, unsigned int age) : age(age), name(name.length() ? name : "Person") {}

        friend std::ostream& operator <<(std::ostream& outputStream, const Person& person) { outputStream << person.toString(); return outputStream; }
        operator =(const Person& person) { ::Person(person.name, person.age); }

        inline const std::string getName() const { return this -> name; }
        inline const unsigned int getAge() const { return this -> age; }

        const std::string toString() const { std::string string; string.append("{name: \""); string.append(this -> name); string.append("\", age: "); string.append(std::to_string(this -> age)); string.append("}"); return string; }
};

int main(int argc, char* argv[]) {
    const unsigned int age = 22u;
    const char *name = "Lapys";
    Person person = Person(name, age);

    void *list = std::malloc(sizeof(const char*) + sizeof(unsigned int) + sizeof(Person));

    *((const char**) list) = name;
    *(((unsigned int*) list) + 1) = age;
    *(((Person*) list) + 2) = person;

    std::cout << "Casting List[`void*`] to `const char*` (or `const void*` on logic errors):" << '\n';
        std::cout << "    [0] Age: " << *((const char**) list) << '\n';
        std::cout << "    [1] Name: " << *(((const void**) list) + 1) << '\n';
        std::cout << "    [2] Person: " << *(((const void**) list) + 2) << '\n';
    std::cout << std::endl;

    std::cout << "Casting List[`void*`] to `unsigned int`:" << '\n';
        std::cout << "    [0] Age: " << *((unsigned int*) list) << '\n';
        std::cout << "    [1] Name: " << *(((unsigned int*) list) + 1) << '\n';
        std::cout << "    [2] Person: " << *(((unsigned int*) list) + 2) << '\n';
    std::cout << std::endl;

    std::cout << "Casting List[`void*`] to `Person`:" << '\n';
        std::cout << "    [0] Age: " << *((Person*) list) << '\n';
        std::cout << "    [1] Name: " << *(((Person*) list) + 1) << '\n';
        std::cout << "    [2] Person: " << *(((Person*) list) + 2) << '\n'; // WARN --- NOTE (Lapys) -> At this point, the data within the `void*` pointer is "broken".
    std::cout << std::endl;

    std::free(list);

    return 0;
}
