/* Import */
#include <pthread.h> // POSIX Thread
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <unistd.h> // UNIX Standard Library

/* Function > ... --- NOTE (Lapys) -> User-defined function. */
void* print_thread(void* argument) {
    // ...
    ::printf("[THREADING (%p)]\n", argument);

    // Return
    return NULL;
}

/* Main */
int main(int argumentCount, char* argumentVector[]) {
    // Initialization > Thread
    pthread_t thread;

    // ...
    ::write(STDOUT_FILENO, "[THREAD : BEFORE]\n", 18u);

    // [...] --- NOTE (Lapys) -> Both functions return the state of the thread.
    ::pthread_create(
        &thread, NULL /* --- NOTE (Lapys) -> Attributes (static). */,
        print_thread, NULL /* --- NOTE (Lapys) -> Argument. */
    );
    ::pthread_join(thread, NULL /* --- NOTE (Lapys) -> Value. */); // NOTE (Lapys) -> - Wait for thread to terminate before continuing.

    ::write(STDOUT_FILENO, "[THREAD : AFTER]", 16u);

    ::pthread_exit(thread);

    // Return
    return 0;
}
