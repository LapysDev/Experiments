/* ... --> wininet.lib | ws2_32.lib */
/* Import */
// : [C/ C++ Standard Library]
#include <cerrno>  // C Error Number
#include <cstddef> // C Standard Definition
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library
#include <new>     // New

#include <stdint.h> // Standard Integers

// : [POSIX]
#if ( \
  defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
  defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
  defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
  defined(_MSC_VER) ||\
  \
  defined(_WIN32) || defined(_WIN64) \
)
# include <cstring>      // C String
# include <sys/types.h>  // System > Types
# if defined(_WIN32) || defined(_WIN64)
#  include <BaseTsd.h>  // Base Types Definitions
#  include <winsock2.h> // Windows Sockets
# else
#  include <arpa/inet.h>  // ARPA > Internet
#  include <sys/socket.h> // System > Socket
# endif

// : [Windows]
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# undef UNICODE

# include <windows.h> // Windows
# include <wininet.h> // Windows Internet
#endif

/* Main */
int main(int const, char* const[]) /* noexcept */ {
  char       *haystack = NULL;
  std::size_t haystackLength = 0u;

  int exitCode = EXIT_SUCCESS;
  char const     host    [] = "en.wikipedia.org";
  char const     method  [] = "GET";
  uint16_t const port       = 80u;
  char const     protocol[] = "HTTP";
  char const     target  [] = "wiki/\"Hello,_World!\"_program";
  char const     version [] = "1.1";

  // ...
  #if ( \
    defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
    defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
    defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
    defined(_MSC_VER) ||\
    \
    defined(_WIN32) || defined(_WIN64) \
  )
    char       *message       = NULL;
    std::size_t messageLength = 0u;
    bool        ready;
    sockaddr_in server;
    int         socketFileDescriptor;

    // ...
    static_cast<void>(target);

    // ...
    #if defined(_WIN32) || defined(_WIN64)
      WSADATA windowsSocketsAPIData;

      if (0x0 == ::WSAStartup(MAKEWORD(2, 2), &windowsSocketsAPIData))
        ready = true;

      else {
        exitCode = EXIT_FAILURE;
        std::fprintf(stderr, "\r\n" "[Module Error (%u)]: Unable to initialize use of Windows Sockets subsystem DLL to establish request to read haystack from host \"%s\"", static_cast<unsigned>(::WSAGetLastError()), host);
      }
    #else
      ready = true;
    #endif

    // ...
    if (ready) {
      socketFileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0x0);

      if (socketFileDescriptor == -1) {
        exitCode = EXIT_FAILURE;
        std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to create socket to establish request to read haystack from host \"%s\":" "\r\n\t" "%s", errno, host, std::strerror(errno));
      }

      else {
        server.sin_port        = ::htons(port);
        server.sin_family      = AF_INET;
        server.sin_addr.s_addr = ::inet_addr(host);

        if (INADDR_NONE == server.sin_addr.s_addr) {
          hostent *const hostEntry = ::gethostbyname(host);

          if (NULL != hostEntry && AF_INET == hostEntry -> h_addrtype)
          server.sin_addr = *reinterpret_cast<in_addr*>(hostEntry -> h_addr);
        }

        // ...
        if (::connect(socketFileDescriptor, reinterpret_cast<sockaddr*>(&server), sizeof(sockaddr_in)) == -1) {
          exitCode = EXIT_FAILURE;
          std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to connect request to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
        }

        else {
          for (char const *iterator = method  ; '\0' != *iterator; ++iterator) ++messageLength;
          for (char const *iterator = protocol; '\0' != *iterator; ++iterator) ++messageLength;
          for (char const *iterator = version ; '\0' != *iterator; ++iterator) ++messageLength;

          messageLength += 9u;
          message = static_cast<char*>(::operator new(messageLength * sizeof(char), std::nothrow));

          // ...
          if (NULL == message) {
            exitCode = EXIT_FAILURE;
            std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to read haystack from %s server \"%s\"", protocol, host);
          }

          else {
            for (char const *iterator = method       ; '\0' != *iterator; ++iterator) *(message++) = *iterator;
            for (char const *iterator = " / "        ; '\0' != *iterator; ++iterator) *(message++) = *iterator;
            for (char const *iterator = protocol     ; '\0' != *iterator; ++iterator) *(message++) = *iterator;
            for (char const *iterator = "/"          ; '\0' != *iterator; ++iterator) *(message++) = *iterator;
            for (char const *iterator = version      ; '\0' != *iterator; ++iterator) *(message++) = *iterator;
            for (char const *iterator = "\r\n" "\r\n"; '\0' != *iterator; ++iterator) *(message++) = *iterator;

            *message = '\0';
            message -= messageLength;

            // ...
            if (::send(socketFileDescriptor, message, messageLength, 0x0) == -1) {
              exitCode = EXIT_FAILURE;
              std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to send request to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
            }

            else {
              haystackLength = 1024u;
              haystack = static_cast<char*>(std::calloc(haystackLength, sizeof(char)));
              std::strcpy(haystack, "Hello, World!");

              if (::recv(socketFileDescriptor, haystack, haystackLength, 0x0) == -1) {
                exitCode = EXIT_FAILURE;
                std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to read response to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
              }

              haystack[haystackLength - 1u] = '\0';
            }
          }
        }
      }

      // ...
      #if defined(_WIN32) || defined(_WIN64)
        if (socketFileDescriptor != -1) ::closesocket(socketFileDescriptor);
        ::WSACleanup();
      #else
        if (socketFileDescriptor != -1) ::close(socketFileDescriptor);
      #endif
    }

    // ...
    if (NULL != message)
    ::operator delete(message);
  #elif defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    HINTERNET connectionHandle;
    HINTERNET openHandle;
    HINTERNET resourceHandle;

    // ...
    static_cast<void>(port);
    static_cast<void>(version);

    // ...
    do {
      openHandle = ::InternetOpen(protocol, INTERNET_OPEN_TYPE_DIRECT, static_cast<LPCSTR>(NULL), static_cast<LPCSTR>(NULL), 0x0u);
      if (NULL == openHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to initialize the Windows Internet API to establish request to read haystack from host \"%s\"", static_cast<unsigned>(::GetLastError()), host); break; }

      connectionHandle = ::InternetConnect(openHandle, host, INTERNET_DEFAULT_HTTPS_PORT, static_cast<LPCSTR>(NULL), static_cast<LPCSTR>(NULL), INTERNET_SERVICE_HTTP, 0x0u, 0x1u);
      if (NULL == connectionHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to open %s session to read haystack from host \"%s\"", static_cast<unsigned>(::GetLastError()), protocol, host); break; }

      resourceHandle = ::HttpOpenRequest(connectionHandle, method, target, static_cast<LPCSTR>(NULL), "", static_cast<LPCSTR*>(NULL), INTERNET_FLAG_SECURE | INTERNET_FLAG_KEEP_CONNECTION, 0x1u);
      if (NULL == resourceHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to create request to read haystack from %s server \"%s\"", static_cast<unsigned>(::GetLastError()), protocol, host); break; }
    } while (false);

    // ...
    if (NULL == connectionHandle || NULL == openHandle || NULL == resourceHandle)
      exitCode = EXIT_FAILURE;

    else {
      if (false == ::HttpSendRequest(resourceHandle, NULL, 0, NULL, 0)) {
        exitCode = EXIT_FAILURE;
        std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to send request to read haystack from HTTP server \"%s\"", static_cast<unsigned>(::GetLastError()), host);
      }

      else {
        bool completed = true;
        char *data = NULL;
        std::size_t dataLength = 0u;

        // ...
        while (true) {
          void *allocation;
          DWORD length;

          // ...
          if (FALSE == ::InternetQueryDataAvailable(resourceHandle, &length, 0x0u, 0x0u)) break;
          else if (0u == length) break;
          else if (dataLength < length) {
            allocation = std::realloc(data, length * sizeof(char));
            if (NULL == allocation) { completed = false; std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory for queried haystack from HTTP server \"%s\"", host); break; }

            data = static_cast<char*>(allocation);
          } dataLength = length;

          if (FALSE == ::InternetReadFile(resourceHandle, data, length, &length)) break;
          else if (0u == length) break;
          else if (dataLength < length) {
            allocation = std::realloc(data, length * sizeof(char));
            if (NULL == allocation) { completed = false; std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to read haystack from HTTP server \"%s\"", host); break; }

            data = static_cast<char*>(allocation);
          } dataLength = length;

          // ...
          haystackLength += dataLength;
          allocation = std::realloc(haystack, haystackLength * sizeof(char));
          if (NULL == allocation) { completed = false; std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to parse haystack from HTTP server \"%s\"", host); break; }
          haystack = static_cast<char*>(allocation);

          // ...
          haystack += haystackLength;
            for (char *iterator = data + dataLength; data != iterator; )
            *--haystack = *--iterator;
          haystack -= haystackLength - dataLength;
        }

        if (false == completed) {
          std::free(data);
          std::free(haystack);

          exitCode = EXIT_FAILURE;
          haystack = NULL;
        }
      }
    }

    // ...
    if (NULL != resourceHandle)   ::InternetCloseHandle(resourceHandle);
    if (NULL != connectionHandle) ::InternetCloseHandle(connectionHandle);
    if (NULL != openHandle)       ::InternetCloseHandle(openHandle);
  #endif

  // ...
  if (NULL != haystack) {
    std::fprintf(stdout, "%15s", "Haystack: ```" "\r\n");
    std::fwrite(haystack, sizeof(char), haystackLength, stdout);
    std::fprintf(stdout, "%5s", "\r\n" "```");

    std::free(haystack);
  }

  // ...
  return exitCode;
}
