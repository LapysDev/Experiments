/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Point --- NOTE (Lapys) -> Number-to-string conversion.
    #include <math.h> // Mathematics
    #include <stdlib.h> // Standard Library
    #include <stdio.h> // Standard Input-Output
    #include <wchar.h> // Wide Character --- NOTE (Lapys) -> `wchar_t` primitive character type.

    // [C++ Standard Library]
    #include <type_traits> // Type Traits --- WARN (Lapys) -> Only works with C++ 2011, ISO/IEC 14882:2011.

    // [Platform-Dependent]
    #include <conio.h> // Console Input-Output
    #include <fcntl.h> // Functional Control
    #include <unistd.h> // UNIX Standard Library

    #include <windows.h> // Windows

    // [...]
    #include <stdio.h>
    #include <iostream>

/* Definition > ... */
#define ANDROID_EXISTS defined(__ANDROID__)
#define LINUX_EXISTS defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__)
#define MACINTOSH_EXISTS defined(__APPLE__ ) && defined(__MACH__)
#define WINDOWS_EXISTS defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)

/* Global */
    /* Clock */
    const class Clock {
        // [...]
        private:

        // [...]
        public:
            /* Class > Date */
            class Date {};

            // Declaration > ...
            void getDay(...) noexcept; // NOTE (Lapys) -> Relative to the start of the year.
            Date getDate(...) noexcept;
            void getHour(...) noexcept; // NOTE (Lapys) -> Relative to the start of the day.
            void getMinute(...) noexcept; // NOTE (Lapys) -> Relative to the start of the day.
            void getMonth(...) noexcept; // NOTE (Lapys) -> Relative to the start of the year.
            void getSecond(...) noexcept; // NOTE (Lapys) -> Relative to the start of the day.
            void getYear(...) noexcept;
    } clock;

    /* Console */
    class Console {
        // [...]
        private:
            // Definition > (Error, Input, Output) ...
            FILE *errorFile, *inputFile, *outputFile;
            #if LINUX_EXISTS
                int errorFileDescriptor, inputFileDescriptor, outputFileDescriptor;
            #endif
            #if WINDOWS_EXISTS
                HANDLE errorBufferHandle, inputBufferHandle, outputBufferHandle;
            #endif

            // Declaration > ...
            void fetch(...) noexcept; // NOTE (Lapys) -> Atomic scanning.
            void put(...) noexcept; // NOTE (Lapys) -> Atomic printing.

            // Function*
                // Get Default (Error, Input, Output) File
                inline const FILE* getDefaultErrorFile(void) noexcept { return stderr; }
                inline const FILE* getDefaultInputFile(void) noexcept { return stdin; }
                inline const FILE* getDefaultOutputFile(void) noexcept { return stdout; }

                // Get Default (Error, Input, Output) File Descriptor
                #if LINUX_EXISTS
                    inline int getDefaultErrorFileDescriptor(void) noexcept { return STDERR_FILENO; }
                    inline int getDefaultInputFileDescriptor(void) noexcept { return STDIN_FILENO; }
                    inline int getDefaultOutputFileDescriptor(void) noexcept { return STDOUT_FILENO; }
                #endif

                // Get Default (Error, Input, Output) Buffer Handle
                #if WINDOWS_EXISTS
                    inline HANDLE getDefaultErrorBufferHandle(void) noexcept; // *NOTE (Lapys) -> Requires the `console` object to be defined.
                    inline HANDLE getDefaultInputBufferHandle(void) noexcept;
                    inline HANDLE getDefaultOutputBufferHandle(void) noexcept;

                    // NOTE (Lapys) -> Helpers for the `getDefault...BufferHandle` methods.
                    inline HANDLE requestDefaultErrorBufferHandle(void) noexcept { return Console::requestDefaultOutputBufferHandle(); }
                    inline HANDLE requestDefaultInputBufferHandle(void) noexcept { return ::CreateFile("CONIN$", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); }
                    inline HANDLE requestDefaultOutputBufferHandle(void) noexcept { return ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); }
                #endif

                // Has Default (Error, Input, Output) File
                inline bool hasDefaultErrorFile(void) noexcept { return this -> errorFile == Console::getDefaultErrorFile(); }
                inline bool hasDefaultInputFile(void) noexcept { return this -> inputFile == Console::getDefaultInputFile(); }
                inline bool hasDefaultOutputFile(void) noexcept { return this -> outputFile == Console::getDefaultOutputFile(); }

                // Has (Error, Input, Output) File
                inline bool hasErrorFile(void) noexcept { return NULL != this -> errorFile; }
                inline bool hasInputFile(void) noexcept { return NULL != this -> inputFile; }
                inline bool hasOutputFile(void) noexcept { return NULL != this -> outputFile; }

                // Has (Default) (Error, Input, Output) File Descriptor
                #if LINUX_EXISTS
                    inline bool hasDefaultErrorFileDescriptor(void) noexcept { return this -> errorFileDescriptor == Console::getDefaultErrorFileDescriptor(); }
                    inline bool hasDefaultInputFileDescriptor(void) noexcept { return this -> inputFileDescriptor == Console::getDefaultInputFileDescriptor(); }
                    inline bool hasDefaultOutputFileDescriptor(void) noexcept { return this -> outputFileDescriptor == Console::getDefaultOutputFileDescriptor(); }

                    inline bool hasErrorFileDescriptor(void) noexcept { return this -> errorFileDescriptor ^ -1; }
                    inline bool hasInputFileDescriptor(void) noexcept { return this -> inputFileDescriptor ^ -1; }
                    inline bool hasOutputFileDescriptor(void) noexcept { return this -> outputFileDescriptor ^ -1; }
                #endif

                // Has (Default) (Error, Input, Output) Buffer Handle
                #if WINDOWS_EXISTS
                    inline bool hasDefaultErrorBufferHandle(void) noexcept; // *NOTE (Lapys) -> Requires the `console` object to be defined.
                    inline bool hasDefaultInputBufferHandle(void) noexcept;
                    inline bool hasDefaultOutputBufferHandle(void) noexcept;

                    inline bool hasErrorBufferHandle(void) noexcept { return INVALID_HANDLE_VALUE != this -> errorBufferHandle && NULL != this -> errorBufferHandle; }
                    inline bool hasInputBufferHandle(void) noexcept { return INVALID_HANDLE_VALUE != this -> inputBufferHandle && NULL != this -> inputBufferHandle; }
                    inline bool hasOutputBufferHandle(void) noexcept { return INVALID_HANDLE_VALUE != this -> outputBufferHandle && NULL != this -> outputBufferHandle; }
                #endif

                // Is Console --- *NOTE (Lapys) -> Requires the `console` object to be defined.
                inline bool isConsole(void) noexcept;

                // Set Default (Error, Input, Output)
                inline void setDefaultError(void) noexcept {
                    this -> errorFile = (FILE*) Console::getDefaultErrorFile();
                    #if LINUX_EXISTS
                        this -> errorFileDescriptor = Console::getDefaultErrorFileDescriptor();
                    #endif
                    #if WINDOWS_EXISTS
                        this -> errorBufferHandle = Console::getDefaultErrorBufferHandle();
                    #endif
                }
                inline void setDefaultInput(void) noexcept {
                    this -> inputFile = (FILE*) Console::getDefaultInputFile();
                    #if LINUX_EXISTS
                        this -> inputFileDescriptor = Console::getDefaultInputFileDescriptor();
                    #endif
                    #if WINDOWS_EXISTS
                        this -> inputBufferHandle = Console::getDefaultInputBufferHandle();
                    #endif
                }
                inline void setDefaultOutput(void) noexcept {
                    this -> outputFile = (FILE*) Console::getDefaultOutputFile();
                    #if LINUX_EXISTS
                        this -> outputFileDescriptor = Console::getDefaultOutputFileDescriptor();
                    #endif
                    #if WINDOWS_EXISTS
                        this -> outputBufferHandle = Console::getDefaultOutputBufferHandle();
                    #endif
                }

                // Set (Error, Input, Output) --- CONSIDERATION (Lapys) -> These functions are invoked before definition on the instantiation of the `console` object.
                inline void setError(FILE*) noexcept;
                inline void setError(const FILE*) noexcept;
                #if LINUX_EXISTS
                    inline void setError(const int) noexcept;
                #endif
                #if WINDOWS_EXISTS
                    inline void setError(HANDLE) noexcept;
                #endif

                inline void setInput(FILE*) noexcept;
                inline void setInput(const FILE*) noexcept;
                #if LINUX_EXISTS
                    inline void setInput(const int) noexcept;
                #endif
                #if WINDOWS_EXISTS
                    inline void setInput(HANDLE) noexcept;
                #endif

                inline void setOutput(FILE*) noexcept;
                inline void setOutput(const FILE*) noexcept;
                #if LINUX_EXISTS
                    inline void setOutput(const int) noexcept;
                #endif
                #if WINDOWS_EXISTS
                    inline void setOutput(HANDLE) noexcept;
                #endif

        // [...]
        public:
            // [Constructor]
            Console(void) : errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , count{}, mode{}, timestamp{} { Console::setDefaultError(); Console::setDefaultInput(); Console::setDefaultOutput(); }
            template <typename outputType> explicit Console(outputType output) : errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , count{}, mode{}, timestamp{} { Console::setDefaultError(); Console::setDefaultInput(); Console::setOutput(output); }
            template <typename inputType, typename outputType> explicit Console(outputType output, inputType input) : errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , count{}, mode{}, timestamp{} { Console::setDefaultError(); Console::setInput(input); Console::setOutput(output); }
            template <typename errorType, typename inputType, typename outputType> explicit Console(outputType output, inputType input, errorType error) : errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , count{}, mode{}, timestamp{} { Console::setError(error); Console::setInput(input); Console::setOutput(output); }

            // [Destructor]
            inline ~Console(void) {
                // Logic > Deletion
                #if WINDOWS_EXISTS
                    ::CloseHandle(this -> errorBufferHandle);
                    ::CloseHandle(this -> inputBufferHandle);
                    ::CloseHandle(this -> outputBufferHandle);

                #else
                    if (Console::hasErrorFile()) ::fclose(this -> errorFile);
                    if (Console::hasInputFile()) ::fclose(this -> inputFile);
                    if (Console::hasOutputFile()) ::fclose(this -> outputFile);
                #endif
            }

            // Declaration > ...
            void batch(...) noexcept;
            void clear(...) noexcept;
            void end(...) noexcept;
            void error(...) noexcept;
            void flush(...) noexcept;
            void group(...) noexcept;
            void log(...) noexcept;
            void prompt(...) noexcept;

            // Initialization > ...
            struct console_counter {} count;
            struct console_mode {} mode;
            struct console_timestamp {} timestamp;
    } console;

/* Namespace */
    /* Mathematics */
    namespace Math {
        /* Definition > ... */
        /* Declaration > ... */
    }

/* Modification */
    /* Clock */
    /* Console */
        // Get Default ... Buffer Handle
        #if WINDOWS_EXISTS
            inline HANDLE Console::getDefaultErrorBufferHandle(void) noexcept { static HANDLE errorBufferHandle = Console::requestDefaultErrorBufferHandle(); if (!Console::isConsole()) errorBufferHandle = Console::requestDefaultErrorBufferHandle(); return errorBufferHandle; }
            inline HANDLE Console::getDefaultInputBufferHandle(void) noexcept { static HANDLE inputBufferHandle = Console::requestDefaultInputBufferHandle(); if (!Console::isConsole()) inputBufferHandle = Console::requestDefaultInputBufferHandle(); return inputBufferHandle; }
            inline HANDLE Console::getDefaultOutputBufferHandle(void) noexcept { static HANDLE outputBufferHandle = Console::requestDefaultOutputBufferHandle(); if (!Console::isConsole()) outputBufferHandle = Console::requestDefaultOutputBufferHandle(); return outputBufferHandle; }
        #endif

        // Has Default ... Buffer Handle
        #if WINDOWS_EXISTS
            inline bool Console::hasDefaultErrorBufferHandle(void) noexcept { return this -> errorBufferHandle == console.errorBufferHandle; }
            inline bool Console::hasDefaultInputBufferHandle(void) noexcept { return this -> inputBufferHandle == console.inputBufferHandle; }
            inline bool Console::hasDefaultOutputBufferHandle(void) noexcept { return this -> outputBufferHandle == console.outputBufferHandle; }
        #endif

        // Is Console
        inline bool Console::isConsole(void) noexcept { return this == &console; }

        // Set ...
        inline void Console::setError(FILE* errorFile) noexcept { this -> errorFile = errorFile; }
        inline void Console::setError(const FILE* errorFile) noexcept { this -> errorFile = (FILE*) errorFile; }
        #if LINUX_EXISTS
            inline void Console::setError(const int errorFileDescriptor) noexcept { this -> errorFileDescriptor = errorFileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            inline void Console::setError(HANDLE errorBufferHandle) noexcept { this -> errorBufferHandle = errorBufferHandle; }
        #endif

        inline void Console::setInput(FILE* inputFile) noexcept { this -> inputFile = inputFile; }
        inline void Console::setInput(const FILE* inputFile) noexcept { this -> inputFile = (FILE*) inputFile; }
        #if LINUX_EXISTS
            inline void Console::setInput(const int inputFileDescriptor) noexcept { this -> inputFileDescriptor = inputFileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            inline void Console::setInput(HANDLE inputBufferHandle) noexcept { this -> inputBufferHandle = inputBufferHandle; }
        #endif

        inline void Console::setOutput(FILE* outputFile) noexcept { this -> outputFile = outputFile; }
        inline void Console::setOutput(const FILE* outputFile) noexcept { this -> outputFile = (FILE*) outputFile; }
        #if LINUX_EXISTS
            inline void Console::setOutput(const int outputFileDescriptor) noexcept { this -> outputFileDescriptor = outputFileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            inline void Console::setOutput(HANDLE outputBufferHandle) noexcept { this -> outputBufferHandle = outputBufferHandle; }
        #endif

    /* Mathematics */

/* Definition > ... */
typedef Clock::Date Date;

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
