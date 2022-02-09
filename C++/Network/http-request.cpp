/* ... --> wininet.lib | ws2_32.lib */
/* Import */
// : [C/ C++ Standard Library]
#include <cstring>
#include <cerrno>  // C Error Number
#include <climits> // C Limits
#include <cstddef> // C Standard Definition
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library

#include <stdint.h> // Standard Integers

// : [Windows]
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# undef UNICODE

# include <windows.h> // Windows
# include <wininet.h> // Windows Internet

// : [POSIX]
#elif ( \
  defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
  defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
  defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
  defined(_MSC_VER) ||\
  \
  defined(_WIN32) || defined(_WIN64) \
)
# include <cstring>     // C String
# include <sys/types.h> // System > Types
# include <unistd.h>    // UNIX Standard

# if defined(_WIN32) || defined(_WIN64)
#  include <BaseTsd.h>  // Base Types Definitions
#  include <winsock2.h> // Windows Sockets
# else
#  include <arpa/inet.h>  // ARPA > Internet
#  include <netdb.h>      // Net "Database"
#  include <sys/socket.h> // System > Socket
# endif
#endif

/* Main */
int main(int const, char* const[]) /* noexcept */ {
  char       *haystack = NULL;
  std::size_t haystackLength = 0u;
  char       *needle = const_cast<char*>("Example Domain");
  std::size_t needleLength = 14u;

  int exitCode = EXIT_SUCCESS;
  char const     host    [] = "www.example.com";
  char const     method  [] = "GET";
  uint16_t const port       = 80u;
  char const     protocol[] = "HTTP";
  char const     target  [] = "index.html";
  char const     version [] = "1.1";

  // ...
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
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

    else if (false == ::HttpSendRequest(resourceHandle, static_cast<LPCSTR>(NULL), 0u, static_cast<LPVOID>(NULL), 0u)) {
      std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to send request to read haystack from HTTP server \"%s\"", static_cast<unsigned>(::GetLastError()), host);
      exitCode = EXIT_FAILURE;
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

          if (NULL != allocation) { data = static_cast<char*>(allocation); dataLength = length; }
          else { std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory for queried haystack from HTTP server \"%s\"", host); completed = false; break; }
        }

        if (FALSE == ::InternetReadFile(resourceHandle, data, length, &length)) break;
        else if (0u == length) break;
        else if (dataLength < length) {
          allocation = std::realloc(data, length * sizeof(char));

          if (NULL != allocation) { data = static_cast<char*>(allocation); dataLength = length; }
          else { std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to read haystack from HTTP server \"%s\"", host); completed = false; break; }
        }

        // ...
        haystackLength += dataLength;
        allocation = std::realloc(haystack, (haystackLength + 1u) * sizeof(char));

        if (NULL != allocation) haystack = static_cast<char*>(allocation);
        else { std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to parse haystack from HTTP server \"%s\"", host); completed = false; break; }

        // ...
        haystack += haystackLength;
        *haystack = '\0';
          for (char *iterator = data + dataLength; data != iterator; )
          *--haystack = *--iterator;
        haystack -= haystackLength - dataLength;
      }

      // ...
      if (false == completed) {
        std::free(data);
        std::free(haystack);

        exitCode = EXIT_FAILURE;
        haystack = NULL;
      }
    }

    // ...
    if (NULL != resourceHandle)   ::InternetCloseHandle(resourceHandle);
    if (NULL != connectionHandle) ::InternetCloseHandle(connectionHandle);
    if (NULL != openHandle)       ::InternetCloseHandle(openHandle);

  #elif ( \
    defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
    defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
    defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
    defined(_MSC_VER) ||\
    \
    defined(_WIN32) || defined(_WIN64) \
  )
    #if defined(_WIN32) || defined(_WIN64)
      WSADATA windowsSocketsData;

      if (0x0 != ::WSAStartup(MAKEWORD(2, 2), &windowsSocketsData)) {
        std::fprintf(stderr, "\r\n" "[Module Error (%u)]: Unable to initialize use of Windows Sockets subsystem DLL to establish request to read haystack from host \"%s\"", static_cast<unsigned>(::WSAGetLastError()), host);
        exitCode = EXIT_FAILURE;
      } else
    #endif
    {
      char *message = NULL;
      std::size_t messageLength = 0u;
      sockaddr_in server;
      int const socketFileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0x0);

      // ...
      if (socketFileDescriptor == -1) {
        std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to create socket to establish request to read haystack from host \"%s\":" "\r\n\t" "%s", errno, host, std::strerror(errno));
        exitCode = EXIT_FAILURE;
      }

      else {
        server.sin_addr.s_addr = ::inet_addr(host);
        server.sin_family      = AF_INET;
        server.sin_port        = ::htons(port);

        // ...
        if (INADDR_NONE == server.sin_addr.s_addr) {
          hostent *const hostEntry = ::gethostbyname(host);

          if (NULL != hostEntry && AF_INET == hostEntry -> h_addrtype)
          server.sin_addr = *reinterpret_cast<in_addr*>(hostEntry -> h_addr);
        }

        // ...
        if (::connect(socketFileDescriptor, reinterpret_cast<sockaddr*>(&server), sizeof(sockaddr_in)) == -1) {
          std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to connect request to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
          exitCode = EXIT_FAILURE;
        }

        else {
          messageLength = 17u + std::strlen(host) + std::strlen(method) + std::strlen(protocol) + std::strlen(target) + std::strlen(version);
          message = static_cast<char*>(std::calloc(messageLength + 1u, sizeof(char)));

          // ... ->> Build up HTTP request message
          if (NULL == message) {
            std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to read haystack from %s server \"%s\"", protocol, host);
            exitCode = EXIT_FAILURE;
          }

          else {
            std::strcat(message, method);
            std::strcat(message, " /");
            std::strcat(message, target);
            std::strcat(message, " ");
            std::strcat(message, protocol);
            std::strcat(message, "/");
            std::strcat(message, version);
            std::strcat(message, "\r\n");
            std::strcat(message, "Host: ");
            std::strcat(message, host);
            std::strcat(message, "\r\n");

            std::strcat(message, "\r\n");
            message[messageLength] = '\0';

            // ...
            if (::send(socketFileDescriptor, message, messageLength, 0x0) == -1) {
              exitCode = EXIT_FAILURE;
              std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to send request to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
            }

            else {
              void *allocation;
              ssize_t bytesRecieved = 0;
              ssize_t bytesTotal = 0;
              char *data;
              std::size_t dataLength = 0u;

              // ... ->> Parse the HTTP response
              std::free(message);
              while (true) {
                haystackLength += 1024u;
                allocation = std::realloc(haystack, (haystackLength + 1u) * sizeof(char));

                if (NULL == allocation) {
                  std::free(haystack);
                  std::fprintf(stderr, "\r\n" "[Memory Error]: Unable to allocate memory to parse haystack from %s server \"%s\"", protocol, host);

                  haystack = NULL;
                  break;
                }

                // ...
                haystack = static_cast<char*>(allocation);
                haystack[haystackLength] = '\0';

                bytesRecieved = ::recv(socketFileDescriptor, haystack + bytesTotal, 1024u, 0x0);
                bytesTotal += bytesRecieved;
                haystack[bytesTotal] = '\0';

                if (0 == bytesRecieved) break;
                else if (bytesRecieved == -1) {
                  std::fprintf(stderr, "\r\n" "[I/O Error (%i)]: Unable to read response to read haystack from %s server \"%s\":" "\r\n\t" "%s", errno, protocol, host, std::strerror(errno));
                  exitCode = EXIT_FAILURE;

                  break;
                }

                // ...
                if (0u == dataLength) {
                  data = std::strstr(haystack, "\r\n" "Content-Length: ");

                  if (NULL != data) {
                    data += 18; // --> std::strlen("\r\n" "Content-Length: ")

                    for (char *iterator = data; '\0' != *iterator; ++iterator)
                    if ('0' != *iterator && '1' != *iterator && '2' != *iterator && '3' != *iterator && '4' != *iterator && '5' != *iterator && '6' != *iterator && '7' != *iterator && '8' != *iterator && '9' != *iterator) {
                      while (data != iterator) {
                        dataLength *= 10u;
                        switch (*(data++)) {
                          case '1': dataLength += 1u; break;
                          case '2': dataLength += 2u; break;
                          case '3': dataLength += 3u; break;
                          case '4': dataLength += 4u; break;
                          case '5': dataLength += 5u; break;
                          case '6': dataLength += 6u; break;
                          case '7': dataLength += 7u; break;
                          case '8': dataLength += 8u; break;
                          case '9': dataLength += 9u; break;
                        }
                      } break;
                    }
                  }
                }
              }

              // ... ->> Get the HTTP response content-body
              if (NULL != haystack) {
                data = std::strstr(haystack, "\r\n" "\r\n");

                if (NULL != data) {
                  data += 4u; // --> std::strlen("\r\n" "\r\n")
                  if (0u == dataLength) dataLength = haystackLength - (data - haystack);

                  // ...
                  haystack[dataLength] = '\0';
                  haystackLength = dataLength;

                  while (dataLength--) *(haystack++) = *(data++);
                  haystack -= haystackLength;
                  allocation = std::realloc(haystack, (haystackLength + 1u) * sizeof(char));
                  if (NULL != allocation) haystack = static_cast<char*>(allocation);
                }
              }
            }
          }
        }

        // ...
        #if defined(_WIN32) || defined(_WIN64)
          ::closesocket(socketFileDescriptor);
        #else
          ::close(socketFileDescriptor);
        #endif
      }

      // ...
      #if defined(_WIN32) || defined(_WIN64)
        ::WSACleanup();
      #endif
    }
  #endif

  // ...
  if (NULL != haystack) {
    bool found = false;

    for (char *iterator = haystack; false == found && '\0' != *iterator; ++iterator)
    for (char *subiterator = needle; *iterator == *needle; ++subiterator) {
      if ('\0' == *subiterator) { found = true; break; }
      if (*subiterator != iterator[subiterator - needle]) break;
    }

    // ...
    std::puts(found ? "Needle found in Haystack" : "Needle not found in Haystack");

    std::fprintf(stdout, "%9s", "Needle: \"");
    std::fwrite(needle, sizeof(char), needleLength, stdout);
    std::fprintf(stdout, "%3s", "\"" "\r\n");

    std::fprintf(stdout, "%15s", "Haystack: ```" "\r\n");
    std::fwrite(haystack, sizeof(char), haystackLength, stdout);
    std::fprintf(stdout, "%5s", "\r\n" "```");

    // ...
    std::free(haystack);
  }

  // ...
  return exitCode;
}
