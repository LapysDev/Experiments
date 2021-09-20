/* Import */
// : [C/ C++ Standard Library]
#include <cerrno>  // C Error Number
#include <cstddef> // C Standard Definition
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library
#include <cstring> // C String

#include <stdint.h> // Standard Integers

// : [POSIX]
#if (\
  defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
  defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
  defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
  defined(_MSC_VER) \
)
# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string.h>

// : [Windows]
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# undef UNICODE

# include <windows.h> // Windows
# include <wininet.h> // Windows Internet
#endif

/* ... */
#include <cstring>
void error(const char *msg) {
  std::perror(msg);
  std::printf("\r\n" "[ERROR]: %u", errno);
  std::exit(0);
}

/* Main */
int main(int const, char* const[]) /* noexcept */ {
  char       *haystack = NULL;
  std::size_t haystackLength = 0u;

  int exitCode = EXIT_SUCCESS;
  char const host    [] = "en.wikipedia.org";
  char const method  [] = "GET";
  char const protocol[] = "HTTP";
  char const target  [] = "wiki/\"Hello,_World!\"_program";

  // ...
  #if (\
    defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || \
    defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__) || \
    defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__) || \
    defined(_MSC_VER) \
  )
    const char * request = "GET /index.html HTTP/1.1\nAccept: */*\n\n";
    size_t length = strlen(request);
    printf("request:\n\n%s", request);

    //  get the destination address
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo * address;
    getaddrinfo("castifyreceiver.com", "http", &hints, &address);

    //  create a socket
    int sfd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
    int result = connect(sfd, address->ai_addr, address->ai_addrlen);
    if (result != 0) {
        printf("connection failed: %i\n", result);
        freeaddrinfo(address);
        close(sfd);
        return 0;
    } else {
        printf("connected\n");
    }

    //  write to socket
    ssize_t written = write(sfd, request, length);
    printf("wrote %lu of %lu expected\n", written, length);

    //  read from socket and cleanup
    char response[4096];
    ssize_t readed = read(sfd, response, 4096);
    printf("read %lu of 4096 possible\n", readed);
    close(sfd);
    freeaddrinfo(address);

    //  display response message
    response[readed] = '\0';
    printf("response:\n\n%s\n", response);
  #elif defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    HINTERNET connectionHandle;
    HINTERNET openHandle;
    HINTERNET resourceHandle;

    // ...
    do {
      openHandle = ::InternetOpen(protocol, INTERNET_OPEN_TYPE_DIRECT, static_cast<LPCSTR>(NULL), static_cast<LPCSTR>(NULL), 0x0u);
      if (NULL == openHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to initialize Windows Internet to establish request to \"%s\"", static_cast<unsigned>(::GetLastError()), host); break; }

      connectionHandle = ::InternetConnect(openHandle, host, INTERNET_DEFAULT_HTTPS_PORT, static_cast<LPCSTR>(NULL), static_cast<LPCSTR>(NULL), INTERNET_SERVICE_HTTP, 0x0u, 0x1u);
      if (NULL == connectionHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to open %s session for host \"%s\"", static_cast<unsigned>(::GetLastError()), protocol, host); break; }

      resourceHandle = ::HttpOpenRequest(connectionHandle, method, target, static_cast<LPCSTR>(NULL), "", static_cast<LPCSTR*>(NULL), INTERNET_FLAG_SECURE | INTERNET_FLAG_KEEP_CONNECTION, 0x1u);
      if (NULL == resourceHandle) { std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to create request to HTTP server \"%s\"", static_cast<unsigned>(::GetLastError()), host); break; }
    } while (false);

    // ...
    if (NULL == connectionHandle || NULL == openHandle || NULL == resourceHandle)
      exitCode = EXIT_FAILURE;

    else {
      if (false == ::HttpSendRequest(resourceHandle, NULL, 0, NULL, 0)) {
        exitCode = EXIT_FAILURE;
        std::fprintf(stderr, "\r\n" "[I/O Error (%u)]: Unable to send request to HTTP server \"%s\"", static_cast<unsigned>(::GetLastError()), host);
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

    // std::free(haystack);
  }

  // ...
  return exitCode;
}
