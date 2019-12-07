/* Import */
#include <iostream> // Input-Output Stream
#include <string> // String

#include <tchar.h> // Typed Characters
#include <windows.h> // Windows
#include <wininet.h> // Windows Internet

/* Directive > ... */
#pragma comment(lib, "wininet.lib")

/* Main */
int main(void) {
    // ...
    std::cout << "[INITIALIZATION]" << std::endl;

    // Initialization > ...
    HINTERNET hConnectHandle;
    HINTERNET hOpenHandle;
    HINTERNET hResourceHandle;

    // Update > ...; Logic > Return
    hOpenHandle = ::InternetOpen("HTTPS", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hOpenHandle == NULL) { return false; }

    hConnectHandle = ::InternetConnect(hOpenHandle, "www.w3.org", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
    if (hConnectHandle == NULL) { ::InternetCloseHandle(hOpenHandle); return false; }

    hResourceHandle = ::HttpOpenRequest(hConnectHandle, "GET", "TR/PNG/iso_8859-1.txt", NULL, "", NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_KEEP_CONNECTION, 1);
    if (hResourceHandle == NULL) { ::InternetCloseHandle(hOpenHandle); ::InternetCloseHandle(hConnectHandle); return false; }

    // Initialization > Buffer
    std::string buf;

    // Logic
    if (::HttpSendRequest(hResourceHandle, NULL, 0, NULL, 0))
        // Loop
        while (true) {
            // Initialization > ...
            std::string part;
            DWORD size;

            // Logic ...; ...
            if (!::InternetQueryDataAvailable(hResourceHandle, &size, 0, 0)) break;
            if (size == 0) break;
            part.resize(size);

            if (!::InternetReadFile(hResourceHandle, &part[0], part.size(), &size)) break;
            if (size == 0) break;
            part.resize(size);

            // Update > Buffer
            buf.append(part);
        }

    else
        // Error
        std::cout << "[ERROR]: " << ::GetLastError() << std::endl;

    // Logic --- NOTE (Lapys) -> Get data back.
    if (!buf.empty()) std::cout << "[DATA]: \"" << buf << '"' << std::endl;

    // ...
    ::InternetCloseHandle(hResourceHandle);
    ::InternetCloseHandle(hConnectHandle);
    ::InternetCloseHandle(hOpenHandle);

    // ...
    std::cout << "[TERMINATION]" << std::flush;

    // Return
    return 0;
}
