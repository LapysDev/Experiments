/* Library */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Volume
        // {Cube}
        int volume(const int length) { return length * length * length; }

        // {Cuboid}
        long volume(const long length, const int breadth, const int height) { return length * breadth * height; }

        // {Cylinder}
        double volume(const double radius, const int height) { return (22.00 / 7.00) * radius * radius * static_cast<double>(height); }

    /* Main */
    int main(int argc, char* argv[]) {
        // {Title} Standard Library > C Output
        std::cout << "Program to use overloaded functions in C++:\n" << std::endl;

        // Standard Library > C Output
        std::cout << "Volume of a Cube of Length 5: " << volume(5) << std::endl;
        std::cout << "Volume of a Cuboid of Breadth 3, Height 6, Length 5: " << volume(5, 3, 6) << std::endl;
        std::cout << "Volume of a Cylinder of Height 6, Radius 4.5: " << volume(4.5, 5) << std::endl;

        // Return
        return 0;
    }
