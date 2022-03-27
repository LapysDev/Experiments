#include <cstddef>
#include <cstdio>
#include <cstdlib>

/* Main */
int main(int, char* arguments[]) /* noexcept */ {
  long             length;
  std::FILE *const file     = std::fopen(*++arguments, "rb");
  bool             error    = NULL == file;
  char            *content  = NULL;
  std::size_t      capacity = 0u;
  char             buffer[1024];

  // ...
  while (false == error) {
    if (0x0 != std::fseek(file, 0L, SEEK_SET)) { error = true; break; }
    length = std::ftell(file);
    if (length == -1L) { error = true; break; }

    if (0x0 != std::fseek(file, 0L, SEEK_END)) { error = true; break; }
    length = std::ftell(file) - length;
    if (length == -1L) { error = true; break; }

    if (0x0 != std::fseek(file, 0L, SEEK_SET)) { error = true; break; }

    // ...
    content = static_cast<char*>(std::malloc((length + 1) * sizeof(char)));
    if (NULL == content) { error = true; break; }
    if (std::fread(content, sizeof(char), length, file) < length) { error = true; break; }
    content[length] = '\0';

    // ...
    break;
  }

  if (error) {
    std::fprintf(stderr, "%21s%s%3s", "Unable to read file \"", *arguments, "\"" "\r\n");
    std::free(content);

    return EXIT_FAILURE;
  }

  // ...
  std::setbuf(stdout, buffer);

  for (char *character = content; length--; ++character) {
    if (capacity >= (sizeof(buffer) / sizeof(char)) - 10u)
    if (EOF == std::fflush(stdout)) {
      std::setbuf(stdout, NULL);
      std::fputs("Unable to view file contents", stderr);

      return EXIT_FAILURE;
    }

    switch (*character) {
      case '0' : capacity += 1u * (EOF != std::fputc('0',     stdout)); break;
      case '1' : capacity += 1u * (EOF != std::fputc('1',     stdout)); break;
      case '2' : capacity += 1u * (EOF != std::fputc('2',     stdout)); break;
      case '3' : capacity += 1u * (EOF != std::fputc('3',     stdout)); break;
      case '4' : capacity += 1u * (EOF != std::fputc('4',     stdout)); break;
      case '5' : capacity += 1u * (EOF != std::fputc('5',     stdout)); break;
      case '6' : capacity += 1u * (EOF != std::fputc('6',     stdout)); break;
      case '7' : capacity += 1u * (EOF != std::fputc('7',     stdout)); break;
      case '8' : capacity += 1u * (EOF != std::fputc('8',     stdout)); break;
      case '9' : capacity += 1u * (EOF != std::fputc('9',     stdout)); break;
      case 'A' : capacity += 1u * (EOF != std::fputc('A',     stdout)); break;
      case 'B' : capacity += 1u * (EOF != std::fputc('B',     stdout)); break;
      case 'C' : capacity += 1u * (EOF != std::fputc('C',     stdout)); break;
      case 'D' : capacity += 1u * (EOF != std::fputc('D',     stdout)); break;
      case 'E' : capacity += 1u * (EOF != std::fputc('E',     stdout)); break;
      case 'F' : capacity += 1u * (EOF != std::fputc('F',     stdout)); break;
      case 'G' : capacity += 1u * (EOF != std::fputc('G',     stdout)); break;
      case 'H' : capacity += 1u * (EOF != std::fputc('H',     stdout)); break;
      case 'I' : capacity += 1u * (EOF != std::fputc('I',     stdout)); break;
      case 'J' : capacity += 1u * (EOF != std::fputc('J',     stdout)); break;
      case 'K' : capacity += 1u * (EOF != std::fputc('K',     stdout)); break;
      case 'L' : capacity += 1u * (EOF != std::fputc('L',     stdout)); break;
      case 'M' : capacity += 1u * (EOF != std::fputc('M',     stdout)); break;
      case 'N' : capacity += 1u * (EOF != std::fputc('N',     stdout)); break;
      case 'O' : capacity += 1u * (EOF != std::fputc('O',     stdout)); break;
      case 'P' : capacity += 1u * (EOF != std::fputc('P',     stdout)); break;
      case 'Q' : capacity += 1u * (EOF != std::fputc('Q',     stdout)); break;
      case 'R' : capacity += 1u * (EOF != std::fputc('R',     stdout)); break;
      case 'S' : capacity += 1u * (EOF != std::fputc('S',     stdout)); break;
      case 'T' : capacity += 1u * (EOF != std::fputc('T',     stdout)); break;
      case 'U' : capacity += 1u * (EOF != std::fputc('U',     stdout)); break;
      case 'V' : capacity += 1u * (EOF != std::fputc('V',     stdout)); break;
      case 'W' : capacity += 1u * (EOF != std::fputc('W',     stdout)); break;
      case 'X' : capacity += 1u * (EOF != std::fputc('X',     stdout)); break;
      case 'Y' : capacity += 1u * (EOF != std::fputc('Y',     stdout)); break;
      case 'Z' : capacity += 1u * (EOF != std::fputc('Z',     stdout)); break;
      case 'a' : capacity += 1u * (EOF != std::fputc('a',     stdout)); break;
      case 'b' : capacity += 1u * (EOF != std::fputc('b',     stdout)); break;
      case 'c' : capacity += 1u * (EOF != std::fputc('c',     stdout)); break;
      case 'd' : capacity += 1u * (EOF != std::fputc('d',     stdout)); break;
      case 'e' : capacity += 1u * (EOF != std::fputc('e',     stdout)); break;
      case 'f' : capacity += 1u * (EOF != std::fputc('f',     stdout)); break;
      case 'g' : capacity += 1u * (EOF != std::fputc('g',     stdout)); break;
      case 'h' : capacity += 1u * (EOF != std::fputc('h',     stdout)); break;
      case 'i' : capacity += 1u * (EOF != std::fputc('i',     stdout)); break;
      case 'j' : capacity += 1u * (EOF != std::fputc('j',     stdout)); break;
      case 'k' : capacity += 1u * (EOF != std::fputc('k',     stdout)); break;
      case 'l' : capacity += 1u * (EOF != std::fputc('l',     stdout)); break;
      case 'm' : capacity += 1u * (EOF != std::fputc('m',     stdout)); break;
      case 'n' : capacity += 1u * (EOF != std::fputc('n',     stdout)); break;
      case 'o' : capacity += 1u * (EOF != std::fputc('o',     stdout)); break;
      case 'p' : capacity += 1u * (EOF != std::fputc('p',     stdout)); break;
      case 'q' : capacity += 1u * (EOF != std::fputc('q',     stdout)); break;
      case 'r' : capacity += 1u * (EOF != std::fputc('r',     stdout)); break;
      case 's' : capacity += 1u * (EOF != std::fputc('s',     stdout)); break;
      case 't' : capacity += 1u * (EOF != std::fputc('t',     stdout)); break;
      case 'u' : capacity += 1u * (EOF != std::fputc('u',     stdout)); break;
      case 'v' : capacity += 1u * (EOF != std::fputc('v',     stdout)); break;
      case 'w' : capacity += 1u * (EOF != std::fputc('w',     stdout)); break;
      case 'x' : capacity += 1u * (EOF != std::fputc('x',     stdout)); break;
      case 'y' : capacity += 1u * (EOF != std::fputc('y',     stdout)); break;
      case 'z' : capacity += 1u * (EOF != std::fputc('z',     stdout)); break;
      case '!' : capacity += 1u * (EOF != std::fputc('!',     stdout)); break;
      case '"' : capacity += 1u * (EOF != std::fputc('"',     stdout)); break;
      case '#' : capacity += 1u * (EOF != std::fputc('#',     stdout)); break;
      case '$' : capacity += 1u * (EOF != std::fputc('$',     stdout)); break;
      case '%' : capacity += 1u * (EOF != std::fputc('%',     stdout)); break;
      case '&' : capacity += 1u * (EOF != std::fputc('&',     stdout)); break;
      case '\'': capacity += 1u * (EOF != std::fputc('\'',    stdout)); break;
      case '(' : capacity += 1u * (EOF != std::fputc('(',     stdout)); break;
      case ')' : capacity += 1u * (EOF != std::fputc(')',     stdout)); break;
      case '*' : capacity += 1u * (EOF != std::fputc('*',     stdout)); break;
      case '+' : capacity += 1u * (EOF != std::fputc('+',     stdout)); break;
      case ',' : capacity += 1u * (EOF != std::fputc(',',     stdout)); break;
      case '-' : capacity += 1u * (EOF != std::fputc('-',     stdout)); break;
      case '.' : capacity += 1u * (EOF != std::fputc('.',     stdout)); break;
      case '/' : capacity += 1u * (EOF != std::fputc('/',     stdout)); break;
      case ':' : capacity += 1u * (EOF != std::fputc(':',     stdout)); break;
      case ';' : capacity += 1u * (EOF != std::fputc(';',     stdout)); break;
      case '<' : capacity += 1u * (EOF != std::fputc('<',     stdout)); break;
      case '=' : capacity += 1u * (EOF != std::fputc('=',     stdout)); break;
      case '>' : capacity += 1u * (EOF != std::fputc('>',     stdout)); break;
      case '?' : capacity += 1u * (EOF != std::fputc('?',     stdout)); break;
      case '@' : capacity += 1u * (EOF != std::fputc('@',     stdout)); break;
      case '[' : capacity += 1u * (EOF != std::fputc('[',     stdout)); break;
      case '\\': capacity += 1u * (EOF != std::fputc('\\',    stdout)); break;
      case ']' : capacity += 1u * (EOF != std::fputc(']',     stdout)); break;
      case '^' : capacity += 1u * (EOF != std::fputc('^',     stdout)); break;
      case '_' : capacity += 1u * (EOF != std::fputc('_',     stdout)); break;
      case '`' : capacity += 1u * (EOF != std::fputc('`',     stdout)); break;
      case '{' : capacity += 1u * (EOF != std::fputc('{',     stdout)); break;
      case '|' : capacity += 1u * (EOF != std::fputc('|',     stdout)); break;
      case '}' : capacity += 1u * (EOF != std::fputc('}',     stdout)); break;
      case '~' : capacity += 1u * (EOF != std::fputc('~',     stdout)); break;
      case '\a': capacity += 4u * (EOF != std::fputs("<\\a>", stdout)); break;
      case '\b': capacity += 4u * (EOF != std::fputs("<\\b>", stdout)); break;
      case '\f': capacity += 4u * (EOF != std::fputs("<\\f>", stdout)); break;
      case '\n': capacity += 1u * (EOF != std::fputc('\n',    stdout)); break;
      case '\t': capacity += 1u * (EOF != std::fputc('\t',    stdout)); break;
      case '\v': capacity += 4u * (EOF != std::fputs("<\\v>", stdout)); break;
      default: capacity += 2u; std::fprintf(stdout, "%3s%hX%c", "<0x", static_cast<unsigned char>(*character), '>'); break;
    }
  }

  std::fflush(stdout);

  // ...
  std::fclose(file);
  std::free(content);

  return EXIT_SUCCESS;
}
