/* Import */
#include <iostream> // Input-Output Stream
#include <thread> // Thread

/* Function > ... --- NOTE (Lapys) -> User-defined. */
void print_threadA() { std::cout << "[THREAD A]" << std::flush; }
void print_threadB(char message[]) { std::cout << "[THREAD B]: \"" << message << '"' << std::flush; }

/* Main */
int main(void) {
    // Initialization > Thread ...
    std::thread threadA(::print_threadA);
    std::thread threadB(::print_threadB, "Hello, World!");

    // ...
    std::cout << "[INITIALIZING]" << std::endl;

    threadB.join();
    threadA.join();

    std::cout << "[TERMINATING]" << std::endl;

    // Return
    return 0;
}
