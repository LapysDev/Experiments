/* Import > ... */
/* [1] */
#include <cstdio> // C Standard Input-Output
#include <iostream> // Input-Output Stream
#include <stdexcept> // Standard Exception
#include <string> // String

/* [2] */
#include <cstdint> // C Standard Integer
#include <cstdio> // C Standard Input-Output
#include <deque> // Dequeue
#include <iostream> // Input-Output
#include <string> // String
#include <thread> // Thread
#include <windows.h> // Windows

/* [3] */
#include <atlstr.h> // ATL String
#include <windows.h> // Windows

/* Function > ... --- WARN (Lapys) -> This will only read the data in the standard output file, not the standard error file. */
/* [1] */ std::string execute(char const command[]) {
    // Initialization > (Buffer, Evaluation, Pipe)
    char buffer[128] {};
    std::string evaluation {};
    FILE *pipe = ::popen(command, "r"); // NOTE (Lapys) -> `_popen` for Windows.

    // Logic > ...
    if (pipe) {
        // Exception Handling > Update > Result ...
        try { while (NULL != ::fgets(buffer, sizeof(buffer), pipe)) result.append(buffer); }
        catch (...) { ::pclose(pipe); throw; }
    } else throw std::runtime_error("");

    // Deletion; Return
    ::pclose(pipe); // NOTE (Lapys) -> `_pclose` for Windows.
    return evaluation;
}

/* [2] --- REDACT (Lapys) -> Users may decide to utilize the `CREATE_NO_WINDOW` flag. */ int system_capture(std::string command, std::string directory, std::string& standardOutputList, std::string& standardErrorList, uint32_t& exitCode) {
    char commandBuffer[MAX_PATH] {};
    PROCESS_INFORMATION processInformation;
    SECURITY_ATTRIBUTES securityAttributes;
    STARTUPINFO startupInformation;

    HANDLE standardErrorReadHandle, standardErrorWriteHandle; std::thread standardErrorThread;
    HANDLE standardOutputReadHandle, standardOutputWriteHandle; std::thread standardOutputThread;

    int success;

    securityAttributes.bInheritHandle = true;
    securityAttributes.lpSecurityDescriptor = NULL;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);

    standardErrorReadHandle = INVALID_HANDLE_VALUE;
    standardErrorWriteHandle = INVALID_HANDLE_VALUE;
    standardOutputReadHandle = INVALID_HANDLE_VALUE;
    standardOutputWriteHandle = INVALID_HANDLE_VALUE;

    if (
        false == ::CreatePipe(&standardOutputReadHandle, &standardOutputWriteHandle, &securityAttributes, 0) ||
        false == ::SetHandleInformation(standardOutputReadHandle, HANDLE_FLAG_INHERIT, 0)
    ) return -1;

    if (
        false == ::CreatePipe(&standardOutputReadHandle, &standardOutputWriteHandle, &securityAttributes, 0) ||
        false == ::SetHandleInformation(standardOutputReadHandle, HANDLE_FLAG_INHERIT, 0)
    ) {
        if (INVALID_HANDLE_VALUE != standardOutputReadHandle) ::CloseHandle(standardOutputReadHandle);
        if (INVALID_HANDLE_VALUE != standardOutputWriteHandle) ::CloseHandle(standardOutputWriteHandle);

        return -2;
    }

    ::ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));
    ::ZeroMemory(&startupInformation, sizeof(STARTUPINFO));

    startupInformation.cb = sizeof(STARTUPINFO);
    startupInformation.hStdError = standardErrorWriteHandle;
    startupInformation.hStdInput = 0;
    startupInformation.hStdOutput = standardOutputWriteHandle;

    if (standardErrorReadHandle || standardOutputReadHandle)
    startupInformation.dwFlags |= STARTF_USESTDHANDLES;

    ::strncpy(commandBuffer, command.c_str(), MAX_PATH);
    *(commandBuffer + (MAX_PATH - 1)) = '\0';

    success = ::CreateProcess(NULL, commandBuffer, NULL, NULL, true, 0, NULL, directory.c_str(), &startupInformation, &processInformation);
    ::CloseHandle(standardErrorWriteHandle);
    ::CloseHandle(standardOutputWriteHandle);

    if (success) ::CloseHandle(processInformation.hThread);
    else {
        ::CloseHandle(processInformation.hProcess);
        ::CloseHandle(processInformation.hThread);
        ::CloseHandle(standardErrorReadHandle);
        ::CloseHandle(standardOutputReadHandle);
        return -4;
    }

    if (standardOutputReadHandle) {
        standardOutputThread = std::thread([&]() {
            char buffer[1000u] {};
            size_t const bufferSize = sizeof(buffer) / sizeof(char);
            DWORD size;

            while (true) {
                int success;

                size = 0;
                success = ::ReadFile(standardOutputReadHandle, buffer, (DWORD) bufferSize, &size, NULL);
                ::printf("[Standard Error Stream]: Exit Code: %d, Size: %d\n\r", success, (int) size);

                if (0 == size || false == success) break;
                std::string subevaluation {buffer, size};

                ::printf("[Standard Output Stream]: \"%s\"\n\r", subevaluation.c_str());
                standardOutputList.append(subevaluation);
            }

            ::printf("[Standard Output Stream]: [break]\n\r");
        });
    }

    if (standardErrorReadHandle) {
        standardErrorThread = std::thread([&]() {
            char buffer [1000u] {};
            size_t const bufferSize = sizeof(buffer) / sizeof(char);
            DWORD size;

            while (true) {
                int success;

                size = 0;
                success = ::ReadFile(standardErrorReadHandle, buffer, (DWORD) bufferSize, &size, NULL);
                ::printf("[Standard Error Stream]: Exit Code: %d, Size: %d\n\r", success, (int) size);

                if (0 == size || false == success) break;
                std::string subevaluation {buffer, size};

                ::printf("[Standard Error Stream]: \"%s\"", subevaluation.c_str());
                standardErrorList.append(subevaluation);
            }

            ::printf("[Standard Error Stream]: [break]\n\r");
        });
    }

    ::WaitForSingleObject(processInformation.hProcess, INFINITE);
    if (false == ::GetExitCodeProcess(processInformation.hProcess, (DWORD*) &exitCode)) exitCode = -1;
    ::CloseHandle(processInformation.hProcess);

    if (standardOutputThread.joinable()) standardOutputThread.join();
    if (standardErrorThread.joinable()) standardErrorThread.join();

    ::CloseHandle(standardErrorReadHandle);
    ::CloseHandle(standardOutputReadHandle);

    return 0;
}

/* [3] --- REDACT (Lapys) */ CStringA execute_command(wchar_t const command[]) {
    CStringA evaluation;
    HANDLE standardOutputReadPipe, standardOutputWritePipe;

    BOOL processEnded;
    BOOL success;

    PROCESS_INFORMATION processInformation {0};
    SECURITY_ATTRIBUTES securityAttributes {sizeof(SECURITY_ATTRIBUTES)};
    STARTUPINFOW startupInformation {sizeof(STARTUPINFOW)};

    securityAttributes.bInheritHandle = true; // NOTE (Lapys) -> Pipe handles are inherited by child process.
    securityAttributes.lpSecurityDescriptor = NULL;

    startupInformation.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    startupInformation.hStdError = standardOutputWritePipe;
    startupInformation.hStdOutput = standardOutputWritePipe;
    startupInformation.wShowWindow = SW_HIDE; // NOTE (Lapys) -> Prevents command window from flashing. --- WARN (Lapys) -> Requires `STARTF_USESHOWWINDOW` in `dwFlags` member.

    // Logic --- NOTE (Lapys) -> Create a pipe to get results from the child process` standard output.
    if (false == ::CreatePipe(&standardOutputReadPipe, &standardOutputWritePipe, &securityAttributes, 0))
    return evaluation;

    success = ::CreateProcessW(NULL, (LPWSTR) command, NULL, NULL, true, CREATE_NEW_CONSOLE, NULL, NULL, &startupInformation, &processInformation);;

    if (false == success) {
        ::CloseHandle(standardOutputReadPipe);
        ::CloseHandle(standardOutputWritePipe);

        return evaluation;
    }

    while (false == processEnded) {
        // Update > Process Ended --- NOTE (Lapys) -> Give a time slice of 50ms or so to prevent wasting 100% CPU.
        processEnded = WAIT_OBJECT_0 == ::WaitForSingleObject(processInformation.hProcess, 50);

        // Loop --- NOTE (Lapys) -> Regardless of the process ending, continue reading available data from the pipes.
        while (true) {
            char buffer[1024] {};
            DWORD bytesAvailable = 0, bytesRead = 0;

            if (false == ::PeekNamedPipe(standardOutputReadPipe, NULL, 0, NULL, &bytesAvailable, NULL)) break;
            if (false == bytesAvailable) break; // NOTE (Lapys) -> No available data.
            if (false == ::ReadFile(standardOutputReadPipe, buffer, ::min(sizeof(buffer) - 1u, bytesAvailable), &bytesRead, NULL) || false == bytesRead) break; // NOTE (Lapys) -> The child process may have ended.

            *(buffer + bytesRead) = '\0';
            evaluation += buffer;
        }
    }

    ::CloseHandlee(processInformation.hProcess);
    ::CloseHandlee(processInformation.hThread);
    ::CloseHandle(standardOutputReadPipe);
    ::CloseHandle(standardOutputWritePipe);

    return evaluation;
}
