/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Point --- NOTE (Lapys) -> Number-to-string conversion.
    #include <math.h> // Mathematics --- NOTE (Lapys) -> Number-to-string conversion.
    #include <stdlib.h> // Standard Library
    #include <stdio.h> // Standard Input-Output --- NOTE (Lapys) -> Standard library console input/ output.

    // [Platform-Dependent]
    #include <unistd.h> // UNIX Standard Library --- NOTE (Lapys) -> Linux platform console input/ output.
    #include <windows.h> // Windows --- NOTE (Lapys) -> Windows platform console input/ output.

    // [...]
    #include <conio.h> // Console Input-Output --- NOTE (Lapys) -> Non-standard console input/ output.

#include <iostream>

/* Definition > ... */
#define ANDROID_EXISTS (defined(__ANDROID__))
#define LINUX_EXISTS (defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__))
#define MACINTOSH_EXISTS (defined(__APPLE__ ) && defined(__MACH__))
#define WINDOWS_EXISTS (defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__))

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

    /* Console --- WARN (Lapys) -> Supports ASCII characters only (`char8_t`, `char16_t`, `char32_t` and `wchar_t` types are ignored). */
    class Console { friend int main(void); // UPDATE (Lapys) -> For testing only.
        // [...]
        private:
            // Definition
                // Buffer ...
                size_t bufferLength;
                char *bufferValue;

                // Error, Input, Output --- NOTE (Lapys) -> Alias: stream.
                FILE *errorFile, *inputFile, *outputFile;
                #if LINUX_EXISTS
                    int errorFileDescriptor, inputFileDescriptor, outputFileDescriptor;
                #endif
                #if WINDOWS_EXISTS
                    HANDLE errorBufferHandle, inputBufferHandle, outputBufferHandle;
                #endif

                // Stream
                enum {$BUFFER, $ERROR, $INPUT, $OUTPUT} stream;

            // Declaration > ...
            const FILE* getDefaultErrorFile(void) const noexcept;
            const FILE* getDefaultInputFile(void) const noexcept;
            const FILE* getDefaultOutputFile(void) const noexcept;
            inline const FILE* getFile(void) const noexcept;
            inline bool hasErrorFile(void) const noexcept;
            inline bool hasInputFile(void) const noexcept;
            inline bool hasOutputFile(void) const noexcept;
            inline bool isBuffered(void) const noexcept;
            inline bool isSpecial(void) const noexcept;
            void setError(FILE*) noexcept; void setError(const FILE*) noexcept; void setError(void) noexcept;
            void setInput(FILE*) noexcept; void setInput(const FILE*) noexcept; void setInput(void) noexcept;
            void setOutput(FILE*) noexcept; void setOutput(const FILE*) noexcept; void setOutput(void) noexcept;

            #if LINUX_EXISTS
                int getDefaultErrorFileDescriptor(void) const noexcept;
                int getDefaultInputFileDescriptor(void) const noexcept;
                int getDefaultOutputFileDescriptor(void) const noexcept;
                inline int getFileDescriptor(void) const noexcept;
                inline bool hasErrorFileDescriptor(void) const noexcept;
                inline bool hasInputFileDescriptor(void) const noexcept;
                inline bool hasOutputFileDescriptor(void) const noexcept;
                void setError(const int) noexcept;
                void setInput(const int) noexcept;
                void setOutput(const int) noexcept;
            #endif

            #if WINDOWS_EXISTS
                HANDLE createDefaultErrorBufferHandle(void) const noexcept;
                HANDLE createDefaultInputBufferHandle(void) const noexcept;
                HANDLE createDefaultOutputBufferHandle(void) const noexcept;
                HANDLE getDefaultErrorBufferHandle(void) const noexcept;
                HANDLE getDefaultInputBufferHandle(void) const noexcept;
                HANDLE getDefaultOutputBufferHandle(void) const noexcept;
                inline HANDLE getBufferHandle(void) const noexcept;
                inline bool hasErrorBufferHandle(void) const noexcept;
                inline bool hasInputBufferHandle(void) const noexcept;
                inline bool hasOutputBufferHandle(void) const noexcept;
                void setError(HANDLE) noexcept;
                void setInput(HANDLE) noexcept;
                void setOutput(HANDLE) noexcept;
            #endif

        // [...]
        protected:
            // Class > Console Stream
            struct ConsoleStream { friend Console;
                // [...]
                private:
                    // Definition > (Type, Value) --- MINIFY (Lapys)
                    struct state { public:
                        bool buffer_handle; bool file; bool file_descriptor;
                        constexpr inline state(const bool value = false) : buffer_handle{value}, file{value}, file_descriptor{value} {}
                    } type;

                    struct { public: FILE *file; // NOTE (Lapys) -> Unsupported members are typed as `void*` instead.
                        #if LINUX_EXISTS
                            int descriptor;
                        #else
                            void *descriptor;
                        #endif
                        #if WINDOWS_EXISTS
                            HANDLE handle;
                        #else
                            void *handle;
                        #endif
                    } value;

                // [...]
                public:
                    // [Constructor] --- MINIFY (Lapys)
                    inline ConsoleStream(FILE* file) : type{false}, value{} { this -> type.file = true; this -> value.file = file; }
                    inline ConsoleStream(const FILE* file) : type{false}, value{} { this -> type.file = true; this -> value.file = (FILE*) file; }
                    #if LINUX_EXISTS
                        inline ConsoleStream(const int fileDescriptor) : type{false}, value{} { this -> type.file_descriptor = true; this -> value.descriptor = fileDescriptor; }
                        inline ConsoleStream(FILE* file, const int fileDescriptor) : type{false}, value{} { this -> type.file = true; this -> type.file_descriptor = true; this -> value.descriptor = fileDescriptor; this -> value.file = file; }
                        inline ConsoleStream(const FILE* file, const int fileDescriptor) : type{false}, value{} { this -> type.file = true; this -> type.file_descriptor = true; this -> value.descriptor = fileDescriptor; this -> value.file = (FILE*) file; }
                    #endif
                    #if LINUX_EXISTS && WINDOWS_EXISTS
                        inline ConsoleStream(FILE* file, const int fileDescriptor, HANDLE bufferHandle) : type{false}, value{} { this -> type.buffer_handle = true; this -> type.file = true; this -> type.file_descriptor = true; this -> value.descriptor = fileDescriptor; this -> value.file = file; this -> value.handle = bufferHandle; }
                        inline ConsoleStream(const FILE* file, const int fileDescriptor, HANDLE bufferHandle) : type{false}, value{} { this -> type.buffer_handle = true; this -> type.file = true; this -> type.file_descriptor = true; this -> value.descriptor = fileDescriptor; this -> value.file = (FILE*) file; this -> value.handle = bufferHandle; }
                    #endif
                    #if WINDOWS_EXISTS
                        inline ConsoleStream(HANDLE bufferHandle) : type{false}, value{} { this -> type.buffer_handle = true; this -> value.handle = bufferHandle; }
                        inline ConsoleStream(FILE* file, HANDLE bufferHandle) : type{false}, value{} { this -> type.buffer_handle = true; this -> type.file = true; this -> value.file = file; this -> value.handle = bufferHandle; }
                        inline ConsoleStream(const FILE* file, HANDLE bufferHandle) : type{false}, value{} { this -> type.buffer_handle = true; this -> type.file = true; this -> value.file = (FILE*) file; this -> value.handle = bufferHandle; }
                    #endif
            };

            // Function --- NOTE (Lapys) -> Atomic routines.
                // Fetch
                #if WINDOWS_EXISTS
                    inline bool fetch(char* character) noexcept {
                        // Initialization > Console Input Buffer ...
                        DWORD consoleInputBufferEventsReadCount;
                        INPUT_RECORD consoleInputBufferInformation[1];

                        // Logic --- NOTE (Lapys) -> Synchronous.
                        if (::ReadConsoleInput(Console::getDefaultInputBufferHandle(), consoleInputBufferInformation, 1uL, &consoleInputBufferEventsReadCount)) {
                            // Logic
                            if (consoleInputBufferInformation -> EventType == KEY_EVENT) {
                                // Constant > Console Input Buffer Key Event Record
                                const KEY_EVENT_RECORD& consoleInputBufferKeyEventRecord = consoleInputBufferInformation -> Event.KeyEvent;

                                // Logic
                                if (consoleInputBufferKeyEventRecord.bKeyDown)
                                *character = consoleInputBufferKeyEventRecord.uChar.AsciiChar;
                            }

                            return true;
                        }

                        else
                            return false;
                    }

                #else
                    inline bool fetch(char* character) noexcept {
                        // Initialization > Evaluation
                        int evaluation;

                        // ...; Update > Evaluation --- NOTE (Lapys) -> Synchronous.
                        while (0 == ::_kbhit()) continue;
                        evaluation = ::_getch();

                        // Logic > ...
                        if (ERR == evaluation) { *character = evaluation; return true; }
                        else return false;
                    }

                #endif

                // Put
                #if LINUX_EXISTS
                    inline bool put(char string[], size_t length = 0u) noexcept { if (0u == length) while (*(string + length)) ++length; return ::write(Console::getFileDescriptor(), string, length) ^ -1; }
                    inline bool put(const char string[], size_t length = 0u) noexcept { if (0u == length) while (*(string + length)) ++length; return ::write(Console::getFileDescriptor(), string, length) ^ -1; }
                #elif WINDOWS_EXISTS
                    inline bool put(char string[], size_t = 0u) noexcept {
                        // Initialization > Console Buffer ...
                        static DWORD consoleBufferBytesWritten = 0;
                        HANDLE consoleBufferHandle = Console::getBufferHandle();
                        CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInformation {};

                        BOOL consoleBufferWriteProcedureEvaluation = true;

                        // Update > ...; Loop
                        ::GetConsoleScreenBufferInfo(consoleBufferHandle, &consoleScreenBufferInformation);
                        for (char *iterator = (char*) string; consoleBufferBytesWritten != 1L && consoleBufferWriteProcedureEvaluation; ++iterator) {
                            // Constant > Character
                            const char character = *iterator;

                            // Logic
                            if ('\0' == character || '\a' == character || '\b' == character || '\f' == character || '\n' == character || '\r' == character || '\t' == character || '\v' == character) {
                                // ...
                                consoleBufferWriteProcedureEvaluation = ::WriteConsoleOutputCharacter(
                                    consoleBufferHandle, string, (DWORD) (iterator - string),
                                    consoleScreenBufferInformation.dwCursorPosition,
                                    &consoleBufferBytesWritten
                                );

                                // Logic
                                if (consoleBufferWriteProcedureEvaluation) {
                                    // ... Update ...
                                    switch (character) {
                                        case '\a': ::MessageBeep(0xFFFFFFFF); break;
                                        case '\b': --consoleScreenBufferInformation.dwCursorPosition.X; break;
                                        case '\f': --consoleScreenBufferInformation.dwCursorPosition.X; ++consoleScreenBufferInformation.dwCursorPosition.Y; break;
                                        case '\n': consoleScreenBufferInformation.dwCursorPosition.X = 0; ++consoleScreenBufferInformation.dwCursorPosition.Y; break;
                                        case '\r': consoleScreenBufferInformation.dwCursorPosition.X = 0; break;
                                        case '\t': while (consoleScreenBufferInformation.dwCursorPosition.X % 4) ++consoleScreenBufferInformation.dwCursorPosition.X; break;
                                        case '\v': while (consoleScreenBufferInformation.dwCursorPosition.Y % 4) ++consoleScreenBufferInformation.dwCursorPosition.Y; break;
                                        default: consoleScreenBufferInformation.dwCursorPosition.X += consoleBufferBytesWritten;
                                    }
                                    consoleBufferWriteProcedureEvaluation = character;
                                    string = iterator + 1;
                                }
                            }
                        }

                        ::SetConsoleCursorPosition(consoleBufferHandle, consoleScreenBufferInformation.dwCursorPosition);

                        // Return
                        return consoleBufferWriteProcedureEvaluation;
                    }
                    inline bool put(const char string[], size_t length = 0u) noexcept { return Console::put((char*) string, length); }
                #else
                    inline bool put(char string[], const size_t = 0u) noexcept { return ::fprintf(Console::getFile(), "%s", string) > 0; }
                    inline bool put(const char string[], const size_t = 0u) noexcept { return ::fprintf(Console::getFile(), "%s", string) > 0; }
                #endif

            // Function
                // Print
                inline void print(const bool) const noexcept { std::cout << "[boolean]" << std::endl; }
                inline void print(const char) const noexcept { std::cout << "[character]" << std::endl; }
                inline void print(char[]) const noexcept { std::cout << "[string]" << std::endl; }
                inline void print(const char[]) const noexcept { std::cout << "[constant string]" << std::endl; }
                inline void print(const double) const noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const float) const noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const int) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const long) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const long double) const noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const long long) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const short) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned int) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned long) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned long long) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned short) const noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(void) const noexcept { std::cout << "[]" << std::endl; }
                template <size_t length> inline void print(char (*)[length]) const noexcept { std::cout << "[array pointer string]" << std::endl; }
                template <size_t length> inline void print(char (&)[length]) const noexcept { std::cout << "[array string]" << std::endl; }
                template <typename type> inline void print(type) const noexcept { std::cout << "[object]" << std::endl; }
                template <typename type> inline void print(type*) const noexcept { std::cout << "[pointer]" << std::endl; }
                template <typename type, typename... types> inline void print(type (*)(types...)) const noexcept { std::cout << "[function pointer (template)]" << std::endl; }
                template <typename type, typename... types> inline void print(type (*)(types..., ...)) const noexcept { std::cout << "[function pointer (template variadic)]" << std::endl; }
                template <typename type, typename... types> inline void print(type (&)(types...)) const noexcept { std::cout << "[function (template)]" << std::endl; }
                template <typename type, typename... types> inline void print(type (&)(types..., ...)) const noexcept { std::cout << "[function (template variadic)]" << std::endl; }
                template <size_t length, typename type> inline void print(type (*)[length]) const noexcept { std::cout << "[array pointer]" << std::endl; }
                template <size_t length, typename type> inline void print(type (&)[length]) const noexcept { std::cout << "[array]" << std::endl; }
                template <typename type, typename... types> inline void print(type, types...) const noexcept { std::cout << "[...]" << std::endl; }

        // [...]
        public:
            // Initialization > ... --- REDACT (Lapys)
            const struct ConsoleBuffer { private: const Console *console; public:
                constexpr inline ConsoleBuffer(const Console* console) : console{console} {}
                constexpr inline ConsoleBuffer(void) : console{NULL} {}

                inline operator char*(void) const noexcept { char *buffer = (char*) ::calloc(this -> console -> bufferLength + 1u, sizeof(char)); ::memcpy(buffer, this -> console -> bufferValue, this -> console -> bufferLength * sizeof(char)); return buffer; }
                inline operator const char*(void) const noexcept { char *buffer = (char*) ::calloc(this -> console -> bufferLength + 1u, sizeof(char)); ::memcpy(buffer, this -> console -> bufferValue, this -> console -> bufferLength * sizeof(char)); return (const char*) buffer; }
            } buffer;

            struct ConsoleFiles {
                private: const Console *console;
                protected: struct ConsoleFile { private: FILE* const* file; public:
                    constexpr inline ConsoleFile(FILE* const* consoleFile) : file{consoleFile} {}
                    constexpr inline ConsoleFile(void) : file{NULL} {}

                    inline operator FILE*(void) const noexcept { return *(this -> file); }
                    inline operator const FILE*(void) const noexcept { return *(this -> file); }
                };
                public: ConsoleFile error, input, output;

                constexpr inline ConsoleFiles(const Console* console) : console{console}, error{&(console -> errorFile)}, input{&(console -> inputFile)}, output{&(console -> outputFile)} {}
                constexpr inline ConsoleFiles(void) : console{NULL}, error{NULL}, input{NULL}, output{NULL} {}
            } files;

            // Descriptors
            #if LINUX_EXISTS
                struct ConsoleFileDescriptors {
                    private: const Console *console;
                    protected: struct ConsoleFileDescriptor { private: const int *fileDescriptor; public:
                        constexpr inline ConsoleFileDescriptor(const int* consoleFileDescriptor) : fileDescriptor{consoleFileDescriptor} {}
                        constexpr inline ConsoleFileDescriptor(void) : fileDescriptor{NULL} {}

                        inline operator int(void) const noexcept { return *(this -> fileDescriptor); }
                    };
                    public: ConsoleFileDescriptor error, input, output;

                    constexpr inline ConsoleFileDescriptors(const Console* console) : console{console}, error{&(console -> errorFileDescriptor)}, input{&(console -> inputFileDescriptor)}, output{&(console -> outputFileDescriptor)} {}
                    constexpr inline ConsoleFileDescriptors(void) : console{NULL}, error{NULL}, input{NULL}, output{NULL} {}
                } descriptors;
            #endif

            // Handles
            #if WINDOWS_EXISTS
                struct ConsoleBufferHandles {
                    private: const Console *console;
                    protected: struct ConsoleBufferHandle { private: const HANDLE *handle; public:
                        constexpr inline ConsoleBufferHandle(const HANDLE* consoleBufferHandle) : handle{consoleBufferHandle} {}
                        constexpr inline ConsoleBufferHandle(void) : handle{NULL} {}

                        inline operator HANDLE(void) const noexcept { return *(this -> handle); }
                    };
                    public: ConsoleBufferHandle error, input, output;

                    constexpr inline ConsoleBufferHandles(const Console* console) : console{console}, error{&(console -> errorBufferHandle)}, input{&(console -> inputBufferHandle)}, output{&(console -> outputBufferHandle)} {}
                    constexpr inline ConsoleBufferHandles(void) : console{NULL}, error{NULL}, input{NULL}, output{NULL} {}
                } handles;
            #endif

            // [Constructor]
            inline Console(void);
            inline Console(const ConsoleStream);
            inline Console(const ConsoleStream, const ConsoleStream);
            inline Console(const ConsoleStream, const ConsoleStream, const ConsoleStream);
    } console {};

/* Namespace */
    /* Mathematics */
    namespace Math {
        /* Definition > ... */
        /* Declaration > ... */
    }

/* Modification */
    /* Clock */
    /* Console */
        // ...
        #if LINUX_EXISTS && WINDOWS_EXISTS
            #define console__constructor_initializer_list : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}, \
                errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}, \
                errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}, \
                stream{$OUTPUT}, buffer{this}, files{this}, \
                descriptors{this}, \
                handles{this}
        #elif LINUX_EXISTS
            #define console__constructor_initializer_list : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}, \
                errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}, \
                stream{$OUTPUT}, buffer{this}, files{this}, \
                descriptors{this}
        #elif WINDOWS_EXISTS
            #define console__constructor_initializer_list : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}, \
                errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}, \
                stream{$OUTPUT}, buffer{this}, files{this}, \
                handles{this}
        #else
            #define console__constructor_initializer_list : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}, \
                stream{$OUTPUT}, buffer{this}, files{this}
        #endif

        // [Constructor] --- MINIFY (Lapys)
        inline Console::Console(void) console__constructor_initializer_list { Console::setError(); Console::setInput(); Console::setOutput(); }
        inline Console::Console(const ConsoleStream output) console__constructor_initializer_list {
            Console::setError();
            Console::setInput();

            if (output.type.file) { Console::setOutput((FILE*) output.value.file); if (false == Console::hasOutputFile()) Console::setOutput(Console::getDefaultOutputFile()); } else Console::setOutput(Console::getDefaultOutputFile());
            #if LINUX_EXISTS
            if (output.type.file_descriptor) { Console::setOutput(output.value.descriptor); if (false == Console::hasOutputFileDescriptor()) Console::setOutput(Console::getDefaultOutputFileDescriptor()); } else Console::setOutput(Console::getDefaultOutputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (output.type.buffer_handle) { Console::setOutput(output.value.handle); if (false == Console::hasOutputBufferHandle()) Console::setOutput(Console::getDefaultOutputBufferHandle()); } else Console::setOutput(Console::getDefaultOutputBufferHandle());
            #endif
        }
        inline Console::Console(const ConsoleStream output, const ConsoleStream input) console__constructor_initializer_list {
            Console::setError();

            if (input.type.file) { Console::setInput((FILE*) input.value.file); if (false == Console::hasInputFile()) Console::setInput(Console::getDefaultInputFile()); } else Console::setInput(Console::getDefaultInputFile());
            #if LINUX_EXISTS
            if (input.type.file_descriptor) { Console::setInput(input.value.descriptor); if (false == Console::hasInputFileDescriptor()) Console::setInput(Console::getDefaultInputFileDescriptor()); } else Console::setInput(Console::getDefaultInputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (input.type.buffer_handle) { Console::setInput(input.value.handle); if (false == Console::hasInputBufferHandle()) Console::setInput(Console::getDefaultInputBufferHandle()); } else Console::setInput(Console::getDefaultInputBufferHandle());
            #endif

            if (output.type.file) { Console::setOutput((FILE*) output.value.file); if (false == Console::hasOutputFile()) Console::setOutput(Console::getDefaultOutputFile()); } else Console::setOutput(Console::getDefaultOutputFile());
            #if LINUX_EXISTS
            if (output.type.file_descriptor) { Console::setOutput(output.value.descriptor); if (false == Console::hasOutputFileDescriptor()) Console::setOutput(Console::getDefaultOutputFileDescriptor()); } else Console::setOutput(Console::getDefaultOutputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (output.type.buffer_handle) { Console::setOutput(output.value.handle); if (false == Console::hasOutputBufferHandle()) Console::setOutput(Console::getDefaultOutputBufferHandle()); } else Console::setOutput(Console::getDefaultOutputBufferHandle());
            #endif
        }
        inline Console::Console(const ConsoleStream output, const ConsoleStream input, const ConsoleStream error) console__constructor_initializer_list {
            if (error.type.file) { Console::setError((FILE*) error.value.file); if (false == Console::hasErrorFile()) Console::setError(Console::getDefaultErrorFile()); } else Console::setError(Console::getDefaultErrorFile());
            #if LINUX_EXISTS
            if (error.type.file_descriptor) { Console::setError(error.value.descriptor); if (false == Console::hasErrorFileDescriptor()) Console::setError(Console::getDefaultErrorFileDescriptor()); } else Console::setError(Console::getDefaultErrorFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (error.type.buffer_handle) { Console::setError(error.value.handle); if (false == Console::hasErrorBufferHandle()) Console::setError(Console::getDefaultErrorBufferHandle()); } else Console::setError(Console::getDefaultErrorBufferHandle());
            #endif

            if (input.type.file) { Console::setInput((FILE*) input.value.file); if (false == Console::hasInputFile()) Console::setInput(Console::getDefaultInputFile()); } else Console::setInput(Console::getDefaultInputFile());
            #if LINUX_EXISTS
            if (input.type.file_descriptor) { Console::setInput(input.value.descriptor); if (false == Console::hasInputFileDescriptor()) Console::setInput(Console::getDefaultInputFileDescriptor()); } else Console::setInput(Console::getDefaultInputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (input.type.buffer_handle) { Console::setInput(input.value.handle); if (false == Console::hasInputBufferHandle()) Console::setInput(Console::getDefaultInputBufferHandle()); } else Console::setInput(Console::getDefaultInputBufferHandle());
            #endif

            if (output.type.file) { Console::setOutput((FILE*) output.value.file); if (false == Console::hasOutputFile()) Console::setOutput(Console::getDefaultOutputFile()); } else Console::setOutput(Console::getDefaultOutputFile());
            #if LINUX_EXISTS
            if (output.type.file_descriptor) { Console::setOutput(output.value.descriptor); if (false == Console::hasOutputFileDescriptor()) Console::setOutput(Console::getDefaultOutputFileDescriptor()); } else Console::setOutput(Console::getDefaultOutputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
            if (output.type.buffer_handle) { Console::setOutput(output.value.handle); if (false == Console::hasOutputBufferHandle()) Console::setOutput(Console::getDefaultOutputBufferHandle()); } else Console::setOutput(Console::getDefaultOutputBufferHandle());
            #endif
        }

        // Create Default ...
        #if WINDOWS_EXISTS
            HANDLE Console::createDefaultErrorBufferHandle(void) const noexcept { return Console::createDefaultOutputBufferHandle(); }
            HANDLE Console::createDefaultInputBufferHandle(void) const noexcept { return ::CreateFile("CONIN$", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); }
            HANDLE Console::createDefaultOutputBufferHandle(void) const noexcept { return ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); }
        #endif

        // Get Default ...
        const FILE* Console::getDefaultErrorFile(void) const noexcept { return stderr; }
        const FILE* Console::getDefaultInputFile(void) const noexcept { return stdin; }
        const FILE* Console::getDefaultOutputFile(void) const noexcept { return stdout; }
        #if LINUX_EXISTS
            int Console::getDefaultErrorFileDescriptor(void) const noexcept { return STDOUT_FILENO; }
            int Console::getDefaultInputFileDescriptor(void) const noexcept { return STDIN_FILENO; }
            int Console::getDefaultOutputFileDescriptor(void) const noexcept { return STDERR_FILENO; }
        #endif
        #if WINDOWS_EXISTS
            HANDLE Console::getDefaultErrorBufferHandle(void) const noexcept { static HANDLE consoleErrorBufferHandle = Console::createDefaultErrorBufferHandle(); return Console::isSpecial() ? consoleErrorBufferHandle : Console::createDefaultErrorBufferHandle(); }
            HANDLE Console::getDefaultInputBufferHandle(void) const noexcept { static HANDLE consoleInputBufferHandle = Console::createDefaultInputBufferHandle(); return Console::isSpecial() ? consoleInputBufferHandle : Console::createDefaultInputBufferHandle(); }
            HANDLE Console::getDefaultOutputBufferHandle(void) const noexcept { static HANDLE consoleOutputBufferHandle = Console::createDefaultOutputBufferHandle(); return Console::isSpecial() ? consoleOutputBufferHandle : Console::createDefaultOutputBufferHandle(); }
        #endif

        // Get ...
        inline const FILE* Console::getFile(void) const noexcept { switch (this -> stream) { case $BUFFER: return NULL; case $ERROR: return this -> errorFile; case $INPUT: return this -> inputFile; case $OUTPUT: return this -> outputFile; } return NULL; }
        #if LINUX_EXISTS
            inline int Console::getFileDescriptor(void) const noexcept { switch (this -> stream) { case $BUFFER: return -1; case $ERROR: return this -> errorFileDescriptor; case $INPUT: return this -> inputFileDescriptor; case $OUTPUT: return this -> outputFileDescriptor; } return -1; }
        #endif
        #if WINDOWS_EXISTS
            inline HANDLE Console::getBufferHandle(void) const noexcept { switch (this -> stream) { case $BUFFER: return INVALID_HANDLE_VALUE; case $ERROR: return this -> errorBufferHandle; case $INPUT: return this -> inputBufferHandle; case $OUTPUT: return this -> outputBufferHandle; } return INVALID_HANDLE_VALUE; }
        #endif

        // Has ...
        inline bool Console::hasErrorFile(void) const noexcept { return NULL != this -> errorFile; }
        inline bool Console::hasInputFile(void) const noexcept { return NULL != this -> inputFile; }
        inline bool Console::hasOutputFile(void) const noexcept { return NULL != this -> outputFile; }
        #if LINUX_EXISTS
            inline bool Console::hasErrorFileDescriptor(void) const noexcept { return this -> errorFileDescriptor ^ -1; }
            inline bool Console::hasInputFileDescriptor(void) const noexcept { return this -> inputFileDescriptor ^ -1; }
            inline bool Console::hasOutputFileDescriptor(void) const noexcept { return this -> outputFileDescriptor ^ -1; }
        #endif
        #if WINDOWS_EXISTS
            inline bool Console::hasErrorBufferHandle(void) const noexcept { return INVALID_HANDLE_VALUE != this -> errorBufferHandle && NULL != this -> errorBufferHandle; }
            inline bool Console::hasInputBufferHandle(void) const noexcept { return INVALID_HANDLE_VALUE != this -> inputBufferHandle && NULL != this -> inputBufferHandle; }
            inline bool Console::hasOutputBufferHandle(void) const noexcept { return INVALID_HANDLE_VALUE != this -> outputBufferHandle && NULL != this -> outputBufferHandle; }
        #endif

        // Is ...
        inline bool Console::isBuffered(void) const noexcept { return this -> stream == $BUFFER; }
        inline bool Console::isSpecial(void) const noexcept { return this == &console; }

        // Set ...
        void Console::setError(FILE* file) noexcept { this -> errorFile = file; }
        void Console::setError(const FILE* file) noexcept { this -> errorFile = (FILE*) file; }
        void Console::setError(void) noexcept {
            Console::setError(Console::getDefaultErrorFile());
            #if LINUX_EXISTS
                Console::setError(Console::getDefaultErrorFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
                Console::setError(Console::getDefaultErrorBufferHandle());
            #endif
        }
        #if LINUX_EXISTS
            void Console::setError(const int fileDescriptor) noexcept { this -> errorFileDescriptor = fileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            void Console::setError(HANDLE bufferHandle) noexcept { this -> errorBufferHandle = bufferHandle; }
        #endif

        void Console::setInput(FILE* file) noexcept { this -> inputFile = file; }
        void Console::setInput(const FILE* file) noexcept { this -> inputFile = (FILE*) file; }
        void Console::setInput(void) noexcept {
            Console::setInput(Console::getDefaultInputFile());
            #if LINUX_EXISTS
                Console::setInput(Console::getDefaultInputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
                Console::setInput(Console::getDefaultInputBufferHandle());
            #endif
        }
        #if LINUX_EXISTS
            void Console::setInput(const int fileDescriptor) noexcept { this -> inputFileDescriptor = fileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            void Console::setInput(HANDLE bufferHandle) noexcept { this -> inputBufferHandle = bufferHandle; }
        #endif

        void Console::setOutput(FILE* file) noexcept { this -> outputFile = file; }
        void Console::setOutput(const FILE* file) noexcept { this -> outputFile = (FILE*) file; }
        void Console::setOutput(void) noexcept {
            Console::setOutput(Console::getDefaultOutputFile());
            #if LINUX_EXISTS
                Console::setOutput(Console::getDefaultOutputFileDescriptor());
            #endif
            #if WINDOWS_EXISTS
                Console::setOutput(Console::getDefaultOutputBufferHandle());
            #endif
        }
        #if LINUX_EXISTS
            void Console::setOutput(const int fileDescriptor) noexcept { this -> outputFileDescriptor = fileDescriptor; }
        #endif
        #if WINDOWS_EXISTS
            void Console::setOutput(HANDLE bufferHandle) noexcept { this -> outputBufferHandle = bufferHandle; }
        #endif

        // ...
        #undef console__constructor_initializer_list

    /* Mathematics */

/* Definition > ... */
typedef Clock::Date Date;

/* Main */
int main(void) {
    const char string[14] {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};

    console.print(string);
    console.print("Hello, World!");

    // Return
    return EXIT_SUCCESS;
}
