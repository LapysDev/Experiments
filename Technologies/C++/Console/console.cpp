/* Import */
    // [C Standard Library]
    #include <float.h> // Floating-Point --- NOTE (Lapys) -> Number-to-string conversion.
    #include <math.h> // Mathematics
    #include <stdlib.h> // Standard Library
    #include <stdio.h> // Standard Input-Output

    // [Platform-Dependent]
    #include <windows.h> // Windows

    // [...]
    #include <conio.h> // Console Input-Output

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

    /* Console --- WARN (Lapys) -> Supports ASCII characters only. */
    class Console { friend int main(void); // UPDATE (Lapys)
        // [...]
        private:
            // Definition > (Buffer ..., (Error, Input, Output) ..., Stream)
            size_t bufferLength;
            char *bufferValue;

            FILE *errorFile, *inputFile, *outputFile;
            #if LINUX_EXISTS
                int errorFileDescriptor, inputFileDescriptor, outputFileDescriptor;
            #endif
            #if WINDOWS_EXISTS
                HANDLE errorBufferHandle, inputBufferHandle, outputBufferHandle;
            #endif

            enum ConsoleStream {$BUFFER, $ERROR, $INPUT, $OUTPUT} stream;

            // Function
                // Allocate
                void allocate(void) noexcept {
                    // Logic
                    if (NULL == this -> bufferValue)
                        // Modification > Target > Buffer
                        this -> bufferValue = (char*) ::malloc(32u * sizeof(char));

                    else {
                        // Initialization > Buffer Size
                        size_t bufferSize = 32u;

                        // : Loop > Update > Buffer Size
                        // : Modification > Target > Buffer
                        while (this -> bufferLength > bufferSize) bufferSize <<= 1u;
                        this -> bufferValue = (char*) ::realloc(this -> bufferValue, bufferSize * sizeof(char));
                    }
                }

                // Fetch
                void fetch(...) noexcept; // NOTE (Lapys) -> Atomic scanning.

                // Print --- NOTE (Lapys) -> Print an output.
                inline void print(const bool) noexcept { std::cout << "[boolean]" << std::endl; }
                inline void print(const char) noexcept { std::cout << "[character]" << std::endl; }
                inline void print(char[]) noexcept { std::cout << "[character string]" << std::endl; }
                inline void print(const char[]) noexcept { std::cout << "[character string]" << std::endl; }
                inline void print(const double) noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const float) noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const int) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const long) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const long double) noexcept { std::cout << "[rational]" << std::endl; }
                inline void print(const short) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned int) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned long) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned long long) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(const unsigned short) noexcept { std::cout << "[integral]" << std::endl; }
                inline void print(void) const noexcept { std::cout << "[]" << std::endl; }
                template <size_t length> inline void print(char (*)[length]) noexcept { std::cout << "[character string array pointer]" << std::endl; }
                template <size_t length> inline void print(const char (*)[length]) noexcept { std::cout << "[character string array pointer]" << std::endl; }
                template <size_t length> inline void print(char (&)[length]) noexcept { std::cout << "[character string array]" << std::endl; }
                template <size_t length> inline void print(const char (&)[length]) noexcept { std::cout << "[character string array]" << std::endl; }
                template <typename type> inline void print(type) noexcept { std::cout << "[object]" << std::endl; }
                template <typename type> inline void print(type*) noexcept { std::cout << "[pointer]" << std::endl; }
                template <size_t length, typename type> inline void print(type (*)[length]) noexcept { std::cout << "[array pointer]" << std::endl; }
                template <size_t length, typename type> inline void print(type (&)[length]) noexcept { std::cout << "[array]" << std::endl; }
                template <typename type, typename... types> inline void print(type (*)(types...)) noexcept { std::cout << "[function pointer]" << std::endl; }
                template <typename type, typename... types> inline void print(type (&)(types...)) noexcept { std::cout << "[function]" << std::endl; }
                template <typename type, typename... types> inline void print(type (*)(types..., ...)) noexcept { std::cout << "[function pointer]" << std::endl; }
                template <typename type, typename... types> inline void print(type (&)(types..., ...)) noexcept { std::cout << "[function]" << std::endl; }
                template <typename type, typename... types> inline void print(type, types...) noexcept { std::cout << "[...]" << std::endl; }
                template <size_t length, typename type, typename... types> inline void print(type (*)[length], types...) noexcept { std::cout << "[...]" << std::endl; }
                template <size_t length, typename type, typename... types> inline void print(type (&)[length], types...) noexcept { std::cout << "[...]" << std::endl; }
                template <typename message_type, typename... message_types, typename... types> inline void print(message_type (*)(message_types...), types...) noexcept { std::cout << "[...]" << std::endl; }
                template <typename message_type, typename... message_types, typename... types> inline void print(message_type (&)(message_types...), types...) noexcept { std::cout << "[...]" << std::endl; }
                template <typename message_type, typename... message_types, typename... types> inline void print(message_type (*)(message_types..., ...), types...) noexcept { std::cout << "[...]" << std::endl; }
                template <typename message_type, typename... message_types, typename... types> inline void print(message_type (&)(message_types..., ...), types...) noexcept { std::cout << "[...]" << std::endl; }

                // Print Line
                inline void println(void) noexcept { std::endl(std::cout); }
                template <typename... types> void println(types... messages) noexcept { Console::print(messages...); }

                // Print Pretty
                void printp(...) noexcept;

                // Print Pretty Line
                void printpln(...) noexcept;

                // Put --- NOTE (Lapys) -> Atomic printing.
                inline bool put(const char character) noexcept { ::putchar(character); return true; }
                #if LINUX_EXISTS
                    inline bool put(const char character, const int fileDescriptor) noexcept { int fileWriteProcedureEvaluation = ::write(fileDescriptor, &character, 1u); return fileWriteProcedureEvaluation ^ -1; }
                #endif
                #if WINDOWS_EXISTS
                    inline bool put(const char character, HANDLE consoleBufferHandle, COORD* coordinates) noexcept {
                        // Initialization > Console Buffer Bytes Written
                        static DWORD consoleBufferBytesWritten;

                        // Logic > ...
                        switch (character) {
                            case '\a': break;
                            case '\b': --(coordinates -> X); break;
                            case '\f': break;
                            case '\n': ++(coordinates -> Y); break;
                            case '\r': coordinates -> X = 0; break;
                            case '\t': while (coordinates -> X % 4) ++(coordinates -> X); break;
                            case '\v': while (coordinates -> Y % 4) ++(coordinates -> Y); break;
                            default: {
                                // Initialization > Console Buffer Write Procedure Evaluation
                                // : Logic > Return
                                BOOL consoleBufferWriteProcedureEvaluation = ::WriteConsoleOutputCharacter(consoleBufferHandle, &character, 1uL, *coordinates, &consoleBufferBytesWritten);

                                if (1 != consoleBufferBytesWritten || false == consoleBufferWriteProcedureEvaluation) return false;
                                else ++(coordinates -> X);
                            } break;
                        }

                        // ...; Return
                        ::SetConsoleCursorPosition(consoleBufferHandle, *coordinates);
                        return true;
                    }
                #endif

                // Scan
                void scan(...) noexcept;

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

                // Is Buffered
                inline bool isBuffered(void) const noexcept { return Console::mode == Console::BUFFERED; }

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
                inline void setError(FILE*) noexcept; inline void setError(const FILE*) noexcept;
                inline void setInput(FILE*) noexcept; inline void setInput(const FILE*) noexcept;
                inline void setOutput(FILE*) noexcept; inline void setOutput(const FILE*) noexcept;
                #if LINUX_EXISTS
                    inline void setError(const int) noexcept;
                    inline void setInput(const int) noexcept;
                    inline void setOutput(const int) noexcept;
                #endif
                #if WINDOWS_EXISTS
                    inline void setError(HANDLE) noexcept;
                    inline void setInput(HANDLE) noexcept;
                    inline void setOutput(HANDLE) noexcept;
                #endif

                // Set Stream
                inline void setStream(const ConsoleStream STREAM) noexcept { this -> stream = STREAM; }

        // [...]
        public:
            // [Constructor]
            Console(void) : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , stream{}, count{}, files{this}, mode{Console::modes::UNBUFFERED}, timestamp{} { Console::setDefaultError(); Console::setDefaultInput(); Console::setDefaultOutput(); }
            template <typename outputType> explicit Console(outputType output) : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , stream{}, count{}, files{this}, mode{Console::modes::UNBUFFERED}, timestamp{} { Console::setDefaultError(); Console::setDefaultInput(); Console::setOutput(output); }
            template <typename inputType, typename outputType> explicit Console(outputType output, inputType input) : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , stream{}, count{}, files{this}, mode{Console::modes::UNBUFFERED}, timestamp{} { Console::setDefaultError(); Console::setInput(input); Console::setOutput(output); }
            template <typename errorType, typename inputType, typename outputType> explicit Console(outputType output, inputType input, errorType error) : bufferLength{0u}, bufferValue{NULL}, errorFile{NULL}, inputFile{NULL}, outputFile{NULL}
                #if LINUX_EXISTS
                    , errorFileDescriptor{-1}, inputFileDescriptor{-1}, outputFileDescriptor{-1}
                #endif
                #if WINDOWS_EXISTS
                    , errorBufferHandle{INVALID_HANDLE_VALUE}, inputBufferHandle{INVALID_HANDLE_VALUE}, outputBufferHandle{INVALID_HANDLE_VALUE}
                #endif
            , stream{}, count{}, files{this}, mode{Console::modes::UNBUFFERED}, timestamp{} { Console::setError(error); Console::setInput(input); Console::setOutput(output); }

            inline Console(Console&);
            inline Console(Console&&);
            inline Console(const Console&);
            inline Console(const Console&&);

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

            // Initialization
                // Count --- MINIFY (Lapys) --- REDACT (Lapys)
                struct console_counter { private: size_t value; public:
                    constexpr inline console_counter(void) : value{0u} {}
                    inline operator size_t(void) noexcept { return this -> value++; }
                } count;

                // Files --- MINIFY (Lapys)
                struct console_files { private: const Console *console; public:
                    // [Constructor]
                    constexpr inline console_files(const Console* console) : console{(Console*) console}, error{this}, input{this}, output{this} {}
                    constexpr inline console_files(void) : console{NULL}, error{this}, input{this}, output{this} {}

                    // Initialization > (Error, Input, Output)  --- REDACT (Lapys)
                    struct console_error { private: const console_files *files; public:
                        constexpr inline console_error(const console_files* consoleFiles) : files{(console_files*) consoleFiles} {}
                        constexpr inline console_error(void) : files{NULL} {}

                        inline operator FILE*(void) const noexcept { return this -> files -> console -> errorFile; }
                        inline operator const FILE*(void) const noexcept { return this -> files -> console -> errorFile; }
                    } error;
                    struct console_input { private: const console_files *files; public:
                        constexpr inline console_input(const console_files* consoleFiles) : files{(console_files*) consoleFiles} {}
                        constexpr inline console_input(void) : files{NULL} {}

                        inline operator FILE*(void) const noexcept { return this -> files -> console -> inputFile; }
                        inline operator const FILE*(void) const noexcept { return this -> files -> console -> inputFile; }
                    } input;
                    struct console_output { private: const console_files *files; public:
                        constexpr inline console_output(const console_files* consoleFiles) : files{(console_files*) consoleFiles} {}
                        constexpr inline console_output(void) : files{NULL} {}

                        inline operator FILE*(void) const noexcept { return this -> files -> console -> outputFile; }
                        inline operator const FILE*(void) const noexcept { return this -> files -> console -> outputFile; }
                    } output;
                } files;

                // Mode
                enum modes {BUFFERED, UNBUFFERED} mode;

                // Timestamp
                struct console_timestamp {} timestamp;

            // Function
            void buffer(void) noexcept { Console::setStream(Console::$OUTPUT); Console::println(this -> bufferValue); Console::clear(); } // NOTE (Lapys) -> Print the buffered data and clear it.
            inline void clear(void) noexcept { ::free(this -> bufferValue); this -> bufferLength = 0u; this -> bufferValue = NULL; }
            void end(void) noexcept; // NOTE (Lapys) -> General-purpose method with multiple semantic meanings e.g.: ending a console group e.t.c.
            template <typename... types> void error(types... messages) noexcept { Console::setStream(Console::isBuffered() ? Console::$BUFFER : Console::$ERROR); Console::println(messages...); } // NOTE (Lapys) -> Print an error.
            inline void flush(void) noexcept { ::fflush(this -> errorFile); ::fflush(this -> inputFile); ::fflush(this -> outputFile); } // NOTE (Lapys) -> Flush the error, input & output file.
            void group(...) noexcept;
            template <typename... types> void log(types... messages) noexcept { Console::setStream(Console::isBuffered() ? Console::$BUFFER : Console::$OUTPUT); Console::println(messages...); }
            template <typename... types> friend inline void print(types...) noexcept;
            void prompt(...) noexcept; // NOTE (Lapys) -> Scan an input.
            template <typename... types> friend inline void scan(types...) noexcept;

            // [Operator] > [=]
            inline Console& operator =(Console&) const noexcept;
            inline Console& operator =(Console&&) const noexcept;
            inline Console& operator =(const Console&) const noexcept;
            inline Console& operator =(const Console&&) const noexcept;
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

        // Print
        template <typename... types> inline void print(types... messages) noexcept { console.print(messages...); }

        // Scan
        template <typename... types> inline void scan(types... messages) noexcept { console.scan(messages...); }

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
    const char string[14] {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    console.print(string);
    // console.log("Hello, World!");

    // Return
    return EXIT_SUCCESS;
}
