/* Definitions */
#undef UNICODE

/* Import */
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <windows.h>

/* Main */
int main(int, char* arguments[]) /* noexcept */ {
  char            directory[MAX_PATH + 3u];
  char const     *executableName = const_cast<char const*>(arguments[0]);
  char const     *sourceName     = __FILE__;
  WIN32_FIND_DATA findData;
  std::size_t     fileCount      = 0u;
  HANDLE          fileHandle;
  std::size_t     fileIndex      = 0u;
  char           *fileNames      = NULL;

  // ... ->> Format `executableName` and `sourceName`
  for (char const **const names[] = {&executableName, &sourceName}, **const *name = names; name != names + (sizeof(names) / sizeof(char const**)); ++name) {
    for (char const *iterator = **name; ; ++iterator)
    if ('\0' == *iterator) {
      while (iterator-- != **name)
      if ('\\' == *iterator || '/' == *iterator) {
        **name = ++iterator;
        break;
      }

      break;
    }

    if ('\0' == ***name)
    **name = arguments[0];
  }

  // ... ->> Determine `directory`
  *directory = '\0';

  if (NULL != arguments[1])
  for (char *iterator = arguments[1]; ; ++iterator) {
    directory[iterator - (arguments[1])] = *iterator;
    if ('\0' == *iterator || MAX_PATH == iterator - (arguments[1])) break;
  }

  if ('\0' == *directory) {
    directory[0] = '.';
    directory[1] = '\0';
  }

  for (char *iterator = directory; ; ++iterator) {
    // ->> Translate slashes to backslashes
    if ('/' == *iterator)
    *iterator = '\\';

    // ->> Iterate a folder (suffixed by the 3-character wildcard `"\\*"`)
    if ('\0' == *iterator) {
      iterator[0] = '\\';
      iterator[1] = '\\';
      iterator[2] = '*';
      iterator[3] = '\0';

      break;
    }
  }

  // ... ->> Iterate `directory` entries
  fileHandle = ::FindFirstFile(directory, &findData);

  if (INVALID_HANDLE_VALUE == fileHandle) {
    std::fprintf(stderr, "\r\n" "Unable to open directory \"%s\"", directory);
    return EXIT_SUCCESS;
  }

  else {
    std::fprintf(stdout, "Searching directory \"%s\"" "\r\n", directory);

    // ... ->> Iterate files only
    do if (false == (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      char const *const filters[] = {executableName, sourceName, arguments[0], __FILE__};
      bool              match     = false;

      // ... ->> Filter specific files
      for (char const *const *filter = filters; filter != filters + (sizeof(filters) / sizeof(char*)) && false == match; ++filter) {
        for (char const *fileName = const_cast<char const*>(findData.cFileName); '\0' != *fileName && false == match; ++fileName)
        for (char const *iteratorA = *filter, *iteratorB = fileName; ; ++iteratorA, ++iteratorB) {
          if ('\0' == *iteratorA) { match = true; break; }
          if (*iteratorA != *iteratorB || '\0' == *iteratorB) break;
        }
      }

      // ... ->> Perform action based on filter
      if (false == match) {
        void *allocation;
        std::size_t length = 0u;

        // ...
        for (char *iterator = findData.cFileName; '\0' != *iterator; ++iterator) ++length;
        allocation = std::realloc(fileNames, (fileIndex + length + 2u) * sizeof(char));

        if (NULL == allocation) {
          std::fputs("\r\n" "Unable to review all files for renaming", stderr);
          std::free(fileNames);

          fileNames = NULL;
          break;
        }

        fileCount += 1u;
        fileNames  = static_cast<char*>(allocation);

        for (char *iterator = findData.cFileName; '\0' != *iterator; ++iterator) fileNames[fileIndex++] = *iterator;
        fileNames[fileIndex++] = '\0';
      }
    } while (FALSE != ::FindNextFile(fileHandle, &findData));

    ::FindClose(fileHandle);

    // ...
    if (NULL == fileNames)
      std::fputs("Found no files to rename", stdout);

    else {
      char       *fileName;
      std::size_t fileNameLength = 0u;
      char        name[MAX_PATH - 1u];
      std::size_t nameLength     = 0u;

      // ...
      fileNames[fileIndex++] = '\0';
      fileIndex              = 0u;

      while (fileCount) {
        fileCount /= 10u;
        ++fileNameLength;
      }

      for (char *iterator = fileNames; '\0' != *iterator; ++iterator) {
        std::fputs("  " "Renaming \"", stdout);

        for (fileName = iterator; '\0' != *fileName; ++fileName)
        std::putchar(*fileName);

        // ...
        nameLength = fileNameLength;

        for (std::size_t index = ++fileIndex; nameLength; index /= 10u)
        name[--nameLength] = "0123456789"[index % 10u];

        // ...
        nameLength = fileNameLength;

        while (fileName-- != iterator)
        if ('.' == *fileName) {
          while ('\0' != *fileName)
          name[nameLength++] = *(fileName++);

          break;
        }

        // ...
        fileName           = iterator;
        name[nameLength++] = '\0';

        std::fprintf(stdout, "\" to \"%s\"..." "\r\n", name);

        // ...
        if (FALSE == ::MoveFile(fileName, name))
        std::fprintf(stderr, "  " "Unable to rename file \"%s\"" "\r\n", fileName);

        while ('\0' != *iterator)
        ++iterator;
      }

      std::free(fileNames);
    }
  }

  // ...
  return EXIT_SUCCESS;
}
