/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <time.h> // Time
#include <unistd.h> // UNIX Standard Library

/* Function */
    // ... --- NOTE (Lapys) -> User-defined function.
    void print_interval(void) { ::write(STDOUT_FILENO, "[INTERVAL]\n\r", 12u); }
    void print_timeout(void) { ::write(STDOUT_FILENO, "[TIMEOUT]\n\r", 9u); }

    /* Set (Interval, Timeout) */
    void setTimeout(void (&handler)(), unsigned long delay) {
        // [Main] Logic
        #if _POSIX_C_SOURCE
            // Initialization > Time Specification
            struct timespec timeSpecification;

            // Modification > Time Specification > Time Value (Nano) Seconds
            timeSpecification.tv_sec = time_t(delay / 1000uL);
            timeSpecification.tv_nsec = (delay % 1000uL) * 1000000uL;

            // ... --- NOTE (Lapys) -> Natively pause the program with the data specified.
            ::nanosleep(&timeSpecification, NULL);
        #elif _WINDOWS_H_
            // Initialization > (Current, Recent) Time
            clock_t currentTime, recentTime;

            // Update > (Current Time, Delay)
            currentTime = recentTime = ::clock();
            delay *= (CLOCKS_PER_SEC / 1000uL);

            // Loop > Update > Current Time --- NOTE (Lapys) -> Keep pausing the program.
            while((currentTime - recentTime) < delay) currentTime = ::clock();
        #endif
    } void setInterval(void (&handler)(), unsigned long interval) { for (;;) { ::setTimeout(handler, interval); } }

/* Main */
int main(int argumentCount, char* argumentVector[]) {
    // ...
    ::setTimeout(print_timeout, 1000uL);
    ::setInterval(print_interval, 1000uL);

    // Return
    return 0;
}
