/* rc /nologo /folocalhost.res localhost.rc && cl /nologo /utf-8 /EHsc /O2 /DUNICODE /D_UNICODE localhost.cpp localhost.res /Fe:localhost.exe /link /SUBSYSTEM:WINDOWS ws2_32.lib shell32.lib user32.lib kernel32.lib && del /q localhost.obj localhost.res */
/* clang++ -std=c++98 -O2 -Wall -Wextra -pthread localhost.cpp -o localhost */
/* localhost [--shutdown] --root "C:/LapysDev" --port 8000 */
#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <windows.h>
  #include <shellapi.h>
  #include <sys/stat.h>
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/select.h>
  #include <sys/stat.h>
  #include <sys/un.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <dirent.h>
  #include <pthread.h>
  #include <signal.h>
  #include <errno.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _WIN32
  typedef SOCKET socket_handle;
  typedef ::std::wstring file_path;
  typedef ULONGLONG file_size;
  static socket_handle const INVALID_SOCKET_HANDLE = INVALID_SOCKET;
#else
  typedef int socket_handle;
  typedef ::std::string file_path;
  typedef off_t file_size;
  static socket_handle const INVALID_SOCKET_HANDLE = -1;
#endif

static unsigned short const DEFAULT_PORT = 8000;
static unsigned int const MAX_REQUEST_BYTES = 16384;
static long const MAX_WORKERS = 128;
static file_path rootDirectory;
static unsigned short port = DEFAULT_PORT;
static socket_handle listeners[2] = { INVALID_SOCKET_HANDLE, INVALID_SOCKET_HANDLE };

#ifdef _WIN32
  static wchar_t const* const MUTEX_NAME = L"Local\\LapysDev.Localhost.Instance";
  static wchar_t const* const EVENT_NAME = L"Local\\LapysDev.Localhost.Shutdown";
  static HANDLE instanceMutex = NULL;
  static HANDLE shutdownEvent = NULL;
  static volatile LONG activeWorkers = 0;
#else
  static socket_handle controlSocket = INVALID_SOCKET_HANDLE;
  static ::std::string controlPath;
  static volatile sig_atomic_t stopping = 0;
  static pthread_mutex_t workerMutex = PTHREAD_MUTEX_INITIALIZER;
  static long activeWorkers = 0;
#endif

static void log_message(char const* message) {
#ifdef _WIN32
  ::OutputDebugStringA(message);
  ::OutputDebugStringA("\n");
  HANDLE stream = ::GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD written = 0;
  if (stream != NULL && stream != INVALID_HANDLE_VALUE) {
    ::WriteFile(stream, message, static_cast<DWORD>(::std::strlen(message)), &written, NULL);
    ::WriteFile(stream, "\r\n", 2, &written, NULL);
  }
#else
  ::std::fprintf(stderr, "%s\n", message);
#endif
}

static void close_socket(socket_handle socket) {
  if (socket == INVALID_SOCKET_HANDLE) return;
#ifdef _WIN32
  ::closesocket(socket);
#else
  ::close(socket);
#endif
}

static bool send_all(socket_handle socket, char const* data, ::std::size_t length) {
  while (length) {
    int count = static_cast<int>(length > 32768 ? 32768 : length);
#ifdef _WIN32
    int sent = ::send(socket, data, count, 0);
#else
    int flags = 0;
    #ifdef MSG_NOSIGNAL
      flags = MSG_NOSIGNAL;
    #endif
    int sent = ::send(socket, data, count, flags);
#endif
    if (sent <= 0) {
#ifndef _WIN32
      if (sent < 0 && errno == EINTR) continue;
#endif
      return false;
    }
    data += sent;
    length -= static_cast< ::std::size_t>(sent);
  }
  return true;
}

static ::std::string number_string(unsigned long value) {
  char buffer[64];
  ::std::sprintf(buffer, "%lu", value);
  return buffer;
}

static ::std::string lowercase(::std::string text) {
  for (::std::size_t index = 0; index < text.size(); ++index)
    text[index] = static_cast<char>(::std::tolower(static_cast<unsigned char>(text[index])));
  return text;
}

#ifdef _WIN32
static ::std::string utf8(file_path const& text) {
  if (text.empty()) return "";
  int length = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), static_cast<int>(text.size()), NULL, 0, NULL, NULL);
  if (length <= 0) return "";
  ::std::string output(static_cast< ::std::size_t>(length), '\0');
  ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), static_cast<int>(text.size()), &output[0], length, NULL, NULL);
  return output;
}

static bool from_utf8(::std::string const& input, file_path& output) {
  output.clear();
  if (input.empty()) return true;
  int length = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, input.data(), static_cast<int>(input.size()), NULL, 0);
  if (length <= 0) return false;
  output.resize(static_cast< ::std::size_t>(length));
  return ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, input.data(), static_cast<int>(input.size()), &output[0], length) == length;
}

static ::std::string native_path(file_path const& path) { return utf8(path); }
#else
static ::std::string native_path(file_path const& path) { return path; }
#endif

static ::std::string html_escape(::std::string const& input) {
  ::std::string output;
  for (::std::size_t index = 0; index < input.size(); ++index) {
    switch (input[index]) {
      case '&': output += "&amp;"; break;
      case '<': output += "&lt;"; break;
      case '>': output += "&gt;"; break;
      case '"': output += "&quot;"; break;
      case '\'': output += "&#x27;"; break;
      default: output += input[index]; break;
    }
  }
  return output;
}

static bool url_safe(unsigned char value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
    (value >= '0' && value <= '9') || value == '-' || value == '_' || value == '.' || value == '~';
}

static ::std::string url_encode(::std::string const& input) {
  char const hex[] = "0123456789ABCDEF";
  ::std::string output;
  for (::std::size_t index = 0; index < input.size(); ++index) {
    unsigned char value = static_cast<unsigned char>(input[index]);
    if (url_safe(value)) output += static_cast<char>(value);
    else {
      output += '%';
      output += hex[value >> 4];
      output += hex[value & 15];
    }
  }
  return output;
}

static int hex_digit(char value) {
  if (value >= '0' && value <= '9') return value - '0';
  if (value >= 'a' && value <= 'f') return value - 'a' + 10;
  if (value >= 'A' && value <= 'F') return value - 'A' + 10;
  return -1;
}

static bool url_decode(::std::string const& input, ::std::string& output) {
  output.clear();
  for (::std::size_t index = 0; index < input.size(); ++index) {
    unsigned char value = static_cast<unsigned char>(input[index]);
    if (value == '%') {
      if (index + 2 >= input.size()) return false;
      int upper = hex_digit(input[index + 1]);
      int lower = hex_digit(input[index + 2]);
      if (upper < 0 || lower < 0) return false;
      value = static_cast<unsigned char>((upper << 4) | lower);
      index += 2;
    }
    if (!value || value == '\\') return false; // Reject NUL and platform-ambiguous separators.
    output += static_cast<char>(value);
  }
  return true;
}

static file_path append_path(file_path const& parent, file_path const& name) {
#ifdef _WIN32
  wchar_t separator = L'\\';
#else
  char separator = '/';
#endif
  if (parent.empty()) return name;
  if (parent[parent.size() - 1] == separator) return parent + name;
  return parent + separator + name;
}

static bool resolve_path(::std::string const& url, file_path& output, ::std::string& canonical) {
  // Decode BEFORE splitting: encoded slashes and traversal also get normalized.
  ::std::string decoded;
  if (url.empty() || url[0] != '/' || !url_decode(url, decoded)) return false;
  ::std::vector< ::std::string> components;
  ::std::size_t position = 0;
  while (position < decoded.size()) {
    ::std::size_t end = decoded.find('/', position);
    if (end == ::std::string::npos) end = decoded.size();
    ::std::string segment = decoded.substr(position, end - position);
    if (segment == "..") {
      if (!components.empty()) components.pop_back();
    } else if (!segment.empty() && segment != ".") components.push_back(segment);
    position = end + 1;
  }
  output = rootDirectory;
  canonical = "/";
  for (::std::size_t index = 0; index < components.size(); ++index) {
#ifdef _WIN32
    file_path name;
    if (!from_utf8(components[index], name) || name.find(L':') != file_path::npos) return false;
    // Win32 strips trailing dots/spaces from path components. Disallow aliases.
    if (name.empty() || name[name.size() - 1] == L'.' || name[name.size() - 1] == L' ') return false;
#else
    file_path name = components[index];
#endif
    output = append_path(output, name);
    canonical += url_encode(components[index]);
    if (index + 1 != components.size()) canonical += '/';
  }
  if (!decoded.empty() && decoded[decoded.size() - 1] == '/' && canonical[canonical.size() - 1] != '/') canonical += '/';
  return true;
}

static bool is_directory(file_path const& path) {
#ifdef _WIN32
  DWORD attributes = ::GetFileAttributesW(path.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
  struct stat attributes = {};
  return ::stat(path.c_str(), &attributes) == 0 && S_ISDIR(attributes.st_mode);
#endif
}

static bool is_regular_file(file_path const& path, file_size& size) {
#ifdef _WIN32
  WIN32_FILE_ATTRIBUTE_DATA attributes = {};
  if (!::GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &attributes) ||
      (attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return false;
  size = (static_cast<file_size>(attributes.nFileSizeHigh) << 32) | attributes.nFileSizeLow;
  return true;
#else
  struct stat attributes = {};
  if (::stat(path.c_str(), &attributes) != 0 || !S_ISREG(attributes.st_mode)) return false;
  size = static_cast<file_size>(attributes.st_size);
  return true;
#endif
}

static ::FILE* open_file(file_path const& path) {
#ifdef _WIN32
  return ::_wfopen(path.c_str(), L"rb");
#else
  return ::std::fopen(path.c_str(), "rb");
#endif
}

struct directory_entry {
  ::std::string name;
  bool directory;
};

static bool entry_less(directory_entry const& first, directory_entry const& second) {
  return lowercase(first.name) < lowercase(second.name);
}

static bool list_directory(file_path const& path, ::std::vector<directory_entry>& entries) {
#ifdef _WIN32
  WIN32_FIND_DATAW item = {};
  file_path wildcard = append_path(path, L"*");
  HANDLE search = ::FindFirstFileW(wildcard.c_str(), &item);
  if (search == INVALID_HANDLE_VALUE) return false;
  do {
    if (::wcscmp(item.cFileName, L".") == 0 || ::wcscmp(item.cFileName, L"..") == 0) continue;
    directory_entry entry = { utf8(item.cFileName), (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 };
    entries.push_back(entry);
  } while (::FindNextFileW(search, &item));
  ::FindClose(search);
#else
  DIR* directory = ::opendir(path.c_str());
  if (!directory) return false;
  struct dirent* item = NULL;
  while ((item = ::readdir(directory)) != NULL) {
    if (::std::strcmp(item->d_name, ".") == 0 || ::std::strcmp(item->d_name, "..") == 0) continue;
    file_path child = append_path(path, item->d_name);
    directory_entry entry = { item->d_name, is_directory(child) };
    entries.push_back(entry);
  }
  ::closedir(directory);
#endif
  ::std::sort(entries.begin(), entries.end(), entry_less);
  return true;
}

static ::std::string mime_type(file_path const& path) {
  ::std::string name = lowercase(native_path(path));
  ::std::size_t dot = name.find_last_of('.');
  ::std::string extension = dot == ::std::string::npos ? "" : name.substr(dot);
  if (extension == ".avif") return "image/avif";
  if (extension == ".bmp") return "image/bmp";
  if (extension == ".css") return "text/css";
  if (extension == ".csv") return "text/csv";
  if (extension == ".gif") return "image/gif";
  if (extension == ".htm" || extension == ".html") return "text/html";
  if (extension == ".ico") return "image/x-icon";
  if (extension == ".jpeg" || extension == ".jpg") return "image/jpeg";
  if (extension == ".js" || extension == ".mjs") return "text/javascript";
  if (extension == ".json" || extension == ".map") return "application/json";
  if (extension == ".mp3") return "audio/mpeg";
  if (extension == ".mp4") return "video/mp4";
  if (extension == ".otf") return "font/otf";
  if (extension == ".pdf") return "application/pdf";
  if (extension == ".png") return "image/png";
  if (extension == ".svg") return "image/svg+xml";
  if (extension == ".txt" || extension == ".log" || extension == ".py" || extension == ".cpp" || extension == ".h") return "text/plain";
  if (extension == ".wasm") return "application/wasm";
  if (extension == ".webp") return "image/webp";
  if (extension == ".woff") return "font/woff";
  if (extension == ".woff2") return "font/woff2";
  if (extension == ".xml") return "application/xml";
  if (extension == ".zip") return "application/zip";
  return "application/octet-stream";
}

static ::std::string http_date() {
  char buffer[64] = {};
  ::std::time_t now = ::std::time(NULL);
  ::std::tm utc = {};
#ifdef _WIN32
  __time64_t timestamp = static_cast<__time64_t>(now);
  if (::_gmtime64_s(&utc, &timestamp) == 0)
    ::std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &utc);
#else
  if (::gmtime_r(&now, &utc))
    ::std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &utc);
#endif
  return buffer;
}

static ::std::string unsigned64_string(file_size value) {
  if (!value) return "0";
  ::std::string output;
  while (value) {
    output.insert(output.begin(), static_cast<char>('0' + value % 10));
    value /= 10;
  }
  return output;
}

static bool response_headers(socket_handle socket, int status, char const* label,
                             ::std::string const& type, file_size size,
                             ::std::string const& extra = "") {
  ::std::string header = "HTTP/1.0 " + number_string(static_cast<unsigned long>(status)) + " " + label + "\r\n";
  header += "Server: Localhost\r\n";
  header += "Date: " + http_date() + "\r\n";
  header += "Content-Type: " + type + "\r\n";
  header += "Content-Length: " + unsigned64_string(size) + "\r\n";
  header += "X-Content-Type-Options: nosniff\r\n";
  header += "Connection: close\r\n";
  header += extra;
  header += "\r\n";
  return send_all(socket, header.data(), header.size());
}

static void send_document(socket_handle socket, int status, char const* label, ::std::string const& document, bool head,
                          ::std::string const& extra = "") {
  if (response_headers(socket, status, label, "text/html; charset=utf-8", document.size(), extra) && !head)
    send_all(socket, document.data(), document.size());
}

static void send_error(socket_handle socket, int status, char const* label, bool head) {
  ::std::string document = "<!doctype html><html><head><meta charset=\"utf-8\"><title>";
  document += number_string(static_cast<unsigned long>(status)) + " " + label;
  document += "</title></head><body><h1>" + number_string(static_cast<unsigned long>(status)) + " " + label + "</h1></body></html>\n";
  send_document(socket, status, label, document, head);
}

static void set_client_timeout(socket_handle socket) {
#ifdef _WIN32
  DWORD timeout = 10000;
  ::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char const*>(&timeout), sizeof(timeout));
  ::setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char const*>(&timeout), sizeof(timeout));
#else
  timeval timeout = { 10, 0 };
  ::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  ::setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  #ifdef SO_NOSIGPIPE
    int enabled = 1;
    ::setsockopt(socket, SOL_SOCKET, SO_NOSIGPIPE, &enabled, sizeof(enabled));
  #endif
#endif
}

static void handle_request(socket_handle client) {
  set_client_timeout(client);
  ::std::string request;
  char buffer[4096];
  while (request.size() < MAX_REQUEST_BYTES && request.find("\r\n\r\n") == ::std::string::npos &&
         request.find("\n\n") == ::std::string::npos) {
    int count = ::recv(client, buffer, static_cast<int>(sizeof(buffer)), 0);
    if (count <= 0) return;
    request.append(buffer, static_cast< ::std::size_t>(count));
  }
  if (request.find("\r\n\r\n") == ::std::string::npos && request.find("\n\n") == ::std::string::npos) {
    send_error(client, 431, "Request Header Fields Too Large", false);
    return;
  }
  ::std::size_t lineEnd = request.find('\n');
  if (lineEnd == ::std::string::npos || lineEnd > 8192) { send_error(client, 414, "URI Too Long", false); return; }
  ::std::string line = request.substr(0, lineEnd);
  if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1);
  ::std::size_t firstSpace = line.find(' ');
  ::std::size_t secondSpace = firstSpace == ::std::string::npos ? ::std::string::npos : line.find(' ', firstSpace + 1);
  if (firstSpace == ::std::string::npos || secondSpace == ::std::string::npos || line.find(' ', secondSpace + 1) != ::std::string::npos) {
    send_error(client, 400, "Bad Request", false);
    return;
  }
  ::std::string method = line.substr(0, firstSpace);
  bool head = method == "HEAD";
  if (method != "GET" && !head) { send_error(client, 501, "Not Implemented", false); return; }
  ::std::string target = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
  for (::std::size_t index = 0; index < target.size(); ++index)
    if (static_cast<unsigned char>(target[index]) < 0x20 || target[index] == 0x7f) {
      send_error(client, 400, "Bad Request", head);
      return;
    }
  if (target.empty() || target[0] != '/') { send_error(client, 400, "Bad Request", head); return; }
  ::std::size_t delimiter = target.find_first_of("?#");
  ::std::string uriPath = target.substr(0, delimiter);
  ::std::string suffix = delimiter == ::std::string::npos ? "" : target.substr(delimiter);
  file_path path;
  ::std::string canonical;
  if (!resolve_path(uriPath, path, canonical)) { send_error(client, 400, "Bad Request", head); return; }

  if (is_directory(path)) {
    if (uriPath[uriPath.size() - 1] != '/') {
      ::std::string location = canonical;
      if (location[location.size() - 1] != '/') location += '/';
      location += suffix;
      ::std::string html = "<!doctype html><html><body><a href=\"" + html_escape(location) + "\">Moved Permanently</a></body></html>\n";
      send_document(client, 301, "Moved Permanently", html, head, "Location: " + location + "\r\n");
      return;
    }
#ifdef _WIN32
    file_path indexPaths[] = { append_path(path, L"index.html"), append_path(path, L"index.htm") };
#else
    file_path indexPaths[] = { append_path(path, "index.html"), append_path(path, "index.htm") };
#endif
    for (int index = 0; index < 2; ++index) {
      file_size bytes = 0;
      if (is_regular_file(indexPaths[index], bytes)) {
        path = indexPaths[index];
        break;
      }
    }
    if (is_directory(path)) {
      ::std::vector<directory_entry> entries;
      if (!list_directory(path, entries)) { send_error(client, 403, "Forbidden", head); return; }
      ::std::string html = "<!doctype html><html><head><meta charset=\"utf-8\"><title>Directory listing for ";
      html += html_escape(uriPath) + "</title></head><body><h1>Directory listing for " + html_escape(uriPath);
      html += "</h1><hr><ul>\n";
      for (::std::size_t index = 0; index < entries.size(); ++index) {
        ::std::string filename = entries[index].name + (entries[index].directory ? "/" : "");
        ::std::string link = url_encode(entries[index].name) + (entries[index].directory ? "/" : "");
        html += "<li><a href=\"" + html_escape(link) + "\">" + html_escape(filename) + "</a></li>\n";
      }
      html += "</ul><hr></body></html>\n";
      send_document(client, 200, "OK", html, head);
      return;
    }
  }

  file_size size = 0;
  if (!is_regular_file(path, size)) { send_error(client, 404, "File Not Found", head); return; }
  ::FILE* stream = open_file(path);
  if (!stream) { send_error(client, 403, "Forbidden", head); return; }
  if (response_headers(client, 200, "OK", mime_type(path), size) && !head) {
    while (!::std::feof(stream)) {
      ::std::size_t count = ::std::fread(buffer, 1, sizeof(buffer), stream);
      if (!count || !send_all(client, buffer, count)) break;
    }
  }
  ::std::fclose(stream);
}

static bool worker_begin() {
#ifdef _WIN32
  LONG current = 0;
  do {
    current = ::InterlockedCompareExchange(&activeWorkers, 0, 0);
    if (current >= MAX_WORKERS) return false;
  } while (::InterlockedCompareExchange(&activeWorkers, current + 1, current) != current);
  return true;
#else
  ::pthread_mutex_lock(&workerMutex);
  bool accepted = activeWorkers < MAX_WORKERS;
  if (accepted) ++activeWorkers;
  ::pthread_mutex_unlock(&workerMutex);
  return accepted;
#endif
}

static void worker_end() {
#ifdef _WIN32
  ::InterlockedDecrement(&activeWorkers);
#else
  ::pthread_mutex_lock(&workerMutex);
  --activeWorkers;
  ::pthread_mutex_unlock(&workerMutex);
#endif
}

#ifdef _WIN32
static DWORD WINAPI client_thread(void* parameter) {
  socket_handle client = static_cast<socket_handle>(reinterpret_cast<UINT_PTR>(parameter));
  handle_request(client);
  close_socket(client);
  worker_end();
  return 0;
}
#else
static void* client_thread(void* parameter) {
  socket_handle client = *static_cast<socket_handle*>(parameter);
  delete static_cast<socket_handle*>(parameter);
  handle_request(client);
  close_socket(client);
  worker_end();
  return NULL;
}
#endif

static void start_client(socket_handle client) {
  if (!worker_begin()) {
    close_socket(client);
    return;
  }
#ifdef _WIN32
  HANDLE thread = ::CreateThread(NULL, 0, client_thread, reinterpret_cast<void*>(static_cast<UINT_PTR>(client)), 0, NULL);
  if (thread) ::CloseHandle(thread);
  else { close_socket(client); worker_end(); }
#else
  pthread_t thread;
  socket_handle* parameter = new socket_handle(client);
  if (::pthread_create(&thread, NULL, client_thread, parameter) == 0) ::pthread_detach(thread);
  else { delete parameter; close_socket(client); worker_end(); }
#endif
}

static socket_handle open_listener(bool ipv6) {
  socket_handle server = ::socket(ipv6 ? AF_INET6 : AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server == INVALID_SOCKET_HANDLE) return INVALID_SOCKET_HANDLE;
#ifdef _WIN32
  // Windows: an exclusive listener prevents socket hijacking by another process.
  BOOL exclusive = TRUE;
  ::setsockopt(server, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char const*>(&exclusive), sizeof(exclusive));
#else
  int reuse = 1;
  ::setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
#endif
  if (ipv6) {
    int ipv6Only = 1;
#ifdef _WIN32
    ::setsockopt(server, IPPROTO_IPV6, IPV6_V6ONLY, reinterpret_cast<char const*>(&ipv6Only), sizeof(ipv6Only));
#else
    ::setsockopt(server, IPPROTO_IPV6, IPV6_V6ONLY, &ipv6Only, sizeof(ipv6Only));
#endif
    sockaddr_in6 address = {};
    address.sin6_family = AF_INET6;
    address.sin6_port = ::htons(port);
    address.sin6_addr = in6addr_any;
    if (::bind(server, reinterpret_cast<sockaddr const*>(&address), sizeof(address)) != 0 ||
        ::listen(server, 64) != 0) { close_socket(server); return INVALID_SOCKET_HANDLE; }
  } else {
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = ::htons(port);
    address.sin_addr.s_addr = ::htonl(INADDR_ANY);
    if (::bind(server, reinterpret_cast<sockaddr const*>(&address), sizeof(address)) != 0 ||
        ::listen(server, 64) != 0) { close_socket(server); return INVALID_SOCKET_HANDLE; }
  }
  return server;
}

#ifdef _WIN32
static int request_shutdown() {
  HANDLE event = ::OpenEventW(EVENT_MODIFY_STATE, FALSE, EVENT_NAME);
  if (!event) { log_message("Localhost is not running."); return 1; }
  BOOL success = ::SetEvent(event);
  ::CloseHandle(event);
  if (success) log_message("Localhost shutdown requested.");
  return success ? 0 : 1;
}

static bool start_control() {
  instanceMutex = ::CreateMutexW(NULL, FALSE, MUTEX_NAME);
  if (!instanceMutex) return false;
  if (::GetLastError() == ERROR_ALREADY_EXISTS) {
    log_message("Localhost is already running.");
    ::CloseHandle(instanceMutex);
    instanceMutex = NULL;
    return false;
  }
  shutdownEvent = ::CreateEventW(NULL, TRUE, FALSE, EVENT_NAME);
  if (!shutdownEvent) {
    ::CloseHandle(instanceMutex);
    instanceMutex = NULL;
    return false;
  }
  return true;
}

static void close_control() {
  if (shutdownEvent) ::CloseHandle(shutdownEvent);
  if (instanceMutex) ::CloseHandle(instanceMutex);
  shutdownEvent = instanceMutex = NULL;
}
#else
static void signal_stop(int) { stopping = 1; }

static ::std::string control_name() {
  char suffix[64];
  ::std::sprintf(suffix, "lapysdev-localhost-%lu.sock", static_cast<unsigned long>(::getuid()));
  char const* runtimeDirectory = ::std::getenv("XDG_RUNTIME_DIR");
  ::std::string prefix = "/tmp";
  if (runtimeDirectory && *runtimeDirectory) {
    struct stat directory = {};
    if (::stat(runtimeDirectory, &directory) == 0 && S_ISDIR(directory.st_mode) &&
        ::access(runtimeDirectory, W_OK | X_OK) == 0) prefix = runtimeDirectory;
  }
  if (prefix[prefix.size() - 1] != '/') prefix += '/';
  return prefix + suffix;
}

static bool make_control_address(sockaddr_un& address) {
  ::std::memset(&address, 0, sizeof(address));
  controlPath = control_name();
  if (controlPath.size() >= sizeof(address.sun_path)) return false;
  address.sun_family = AF_UNIX;
  ::std::memcpy(address.sun_path, controlPath.c_str(), controlPath.size() + 1);
  return true;
}

static int request_shutdown() {
  sockaddr_un address = {};
  if (!make_control_address(address)) return 1;
  socket_handle client = ::socket(AF_UNIX, SOCK_STREAM, 0);
  if (client == INVALID_SOCKET_HANDLE) return 1;
  bool success = ::connect(client, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0 &&
                 send_all(client, "S", 1);
  if (success) {
    timeval controlTimeout = { 0, 1000000 };
    ::setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &controlTimeout, sizeof(controlTimeout));
    char confirmation = '\0';
    success = ::recv(client, &confirmation, 1, 0) == 1 && confirmation == 'K';
  }
  close_socket(client);
  log_message(success ? "Localhost shutdown requested." : "Localhost is not running.");
  return success ? 0 : 1;
}

static bool start_control() {
  sockaddr_un address = {};
  if (!make_control_address(address)) return false;
  controlSocket = ::socket(AF_UNIX, SOCK_STREAM, 0);
  if (controlSocket == INVALID_SOCKET_HANDLE) return false;
  mode_t oldMask = ::umask(0077);
  int bound = ::bind(controlSocket, reinterpret_cast<sockaddr*>(&address), sizeof(address));
  if (bound < 0 && errno == EADDRINUSE) {
    socket_handle probe = ::socket(AF_UNIX, SOCK_STREAM, 0);
    bool running = probe != INVALID_SOCKET_HANDLE &&
      ::connect(probe, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0;
    close_socket(probe);
    if (running) log_message("Localhost is already running.");
    else {
      struct stat entry = {};
      if (::lstat(controlPath.c_str(), &entry) == 0 && S_ISSOCK(entry.st_mode) && entry.st_uid == ::geteuid()) {
        ::unlink(controlPath.c_str());
        bound = ::bind(controlSocket, reinterpret_cast<sockaddr*>(&address), sizeof(address));
      }
    }
  }
  ::umask(oldMask);
  if (bound < 0 || ::listen(controlSocket, 4) != 0) {
    close_socket(controlSocket);
    controlSocket = INVALID_SOCKET_HANDLE;
    return false;
  }
  return true;
}

static void close_control() {
  close_socket(controlSocket);
  controlSocket = INVALID_SOCKET_HANDLE;
  if (!controlPath.empty()) ::unlink(controlPath.c_str());
}
#endif

static void cleanup() {
  for (int index = 0; index < 2; ++index) {
    close_socket(listeners[index]);
    listeners[index] = INVALID_SOCKET_HANDLE;
  }
  close_control();
#ifdef _WIN32
  ::WSACleanup();
#endif
}

static int run_server() {
  if (!is_directory(rootDirectory)) {
    log_message("Error: --root does not name an existing directory.");
    return 1;
  }
#ifdef _WIN32
  WSADATA winsock = {};
  if (::WSAStartup(MAKEWORD(2, 2), &winsock) != 0) {
    log_message("Error: Winsock startup failed.");
    return 1;
  }
#endif
  if (!start_control()) {
    log_message("Error: unable to acquire the single-instance control endpoint.");
#ifdef _WIN32
    ::WSACleanup();
#endif
    return 1;
  }
  listeners[0] = open_listener(false);
  listeners[1] = open_listener(true);
  if (listeners[0] == INVALID_SOCKET_HANDLE || listeners[1] == INVALID_SOCKET_HANDLE) {
    log_message("Error: failed to bind both IPv4 and IPv6 (check the port and IPv6 availability).");
    cleanup();
    return 1;
  }
  log_message(("Serving: " + native_path(rootDirectory)).c_str());
  log_message(("IPv4: http://127.0.0.1:" + number_string(port)).c_str());
  log_message(("IPv6: http://[::1]:" + number_string(port)).c_str());
#ifndef _WIN32
  struct sigaction action = {};
  action.sa_handler = signal_stop;
  ::sigemptyset(&action.sa_mask);
  ::sigaction(SIGINT, &action, NULL);
  ::sigaction(SIGTERM, &action, NULL);
  ::signal(SIGPIPE, SIG_IGN);
#endif
  for (;;) {
#ifdef _WIN32
    if (::WaitForSingleObject(shutdownEvent, 0) == WAIT_OBJECT_0) break;
#else
    if (stopping) break;
#endif
    fd_set incoming;
    FD_ZERO(&incoming);
    FD_SET(listeners[0], &incoming);
    FD_SET(listeners[1], &incoming);
#ifndef _WIN32
    FD_SET(controlSocket, &incoming);
#endif
    timeval timeout = { 0, 200000 };
#ifdef _WIN32
    int selected = ::select(0, &incoming, NULL, NULL, &timeout);
#else
    int largest = listeners[0] > listeners[1] ? listeners[0] : listeners[1];
    if (controlSocket > largest) largest = controlSocket;
    int selected = ::select(largest + 1, &incoming, NULL, NULL, &timeout);
#endif
    if (selected <= 0) continue;
#ifndef _WIN32
    if (FD_ISSET(controlSocket, &incoming)) {
      socket_handle client = ::accept(controlSocket, NULL, NULL);
      if (client != INVALID_SOCKET_HANDLE) {
        timeval controlTimeout = { 0, 250000 };
        ::setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &controlTimeout, sizeof(controlTimeout));
        char command = '\0';
        if (::recv(client, &command, 1, 0) == 1 && command == 'S') {
          send_all(client, "K", 1);
          stopping = 1;
        }
        close_socket(client);
      }
    }
    if (stopping) break;
#endif
    for (int index = 0; index < 2; ++index) {
      if (FD_ISSET(listeners[index], &incoming)) {
        socket_handle client = ::accept(listeners[index], NULL, NULL);
        if (client != INVALID_SOCKET_HANDLE) start_client(client);
      }
    }
  }
  cleanup();
  log_message("Localhost stopped.");
  return 0;
}

static bool parse_port(::std::string const& text, unsigned short& result) {
  if (text.empty()) return false;
  unsigned long value = 0;
  for (::std::size_t index = 0; index < text.size(); ++index) {
    if (text[index] < '0' || text[index] > '9') return false;
    value = value * 10 + static_cast<unsigned long>(text[index] - '0');
    if (value > 65535) return false;
  }
  if (!value) return false;
  result = static_cast<unsigned short>(value);
  return true;
}

static int parse_options(int count, file_path const* values, bool& shutdown, bool& help) {
  shutdown = false;
  help = false;
#ifdef _WIN32
  rootDirectory = L"C:\\LapysDev";
#else
  rootDirectory = "C:\\LapysDev";
#endif
  for (int index = 1; index < count; ++index) {
    ::std::string option = lowercase(native_path(values[index]));
    if (option == "--shutdown") {
      if (count != 2) return 2;
      shutdown = true;
      return 0;
    }
    if (option == "--help" || option == "-h") {
      if (count != 2) return 2;
      help = true;
      return 0;
    }
    if (option == "--root" && index + 1 < count) rootDirectory = values[++index];
    else if (option == "--port" && index + 1 < count) {
      if (!parse_port(native_path(values[++index]), port)) return 2;
    } else return 2;
  }
  return 0;
}

/* Main */
static int entry_point(int count, file_path const* values) {
  bool shutdown = false;
  bool help = false;
  int result = parse_options(count, values, shutdown, help);
  if (result || help) {
    log_message("Usage: localhost [--root DIRECTORY] [--port 1..65535] | -shutdown | --help");
    return result;
  }
  if (shutdown) return request_shutdown();
  return run_server();
}

#ifdef _WIN32
  static int windows_entry_point(int count, wchar_t** arguments) {
    ::std::vector<file_path> values;
    for (int index = 0; index < count; ++index) values.push_back(arguments[index]);
    return entry_point(count, &values[0]);
  }

  #ifdef LOCALHOST_CONSOLE
    int wmain(int count, wchar_t** arguments) { return windows_entry_point(count, arguments); }
  #else
    int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
      int count = 0;
      LPWSTR* arguments = ::CommandLineToArgvW(::GetCommandLineW(), &count);
      if (!arguments || count < 1) return 2;
      int result = windows_entry_point(count, arguments);
      ::LocalFree(arguments);
      return result;
    }
  #endif
#else
  int main(int count, char** arguments) {
    ::std::vector<file_path> values;
    for (int index = 0; index < count; ++index) values.push_back(arguments[index]);
    return entry_point(count, &values[0]);
  }
#endif
