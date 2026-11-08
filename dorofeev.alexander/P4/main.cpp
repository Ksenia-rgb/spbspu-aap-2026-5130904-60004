#include <iostream>
#include <cstring>
#include <new>

namespace dorofeev {
  const size_t startCapacity = 100;

  char* readline(std::istream& in)
  {
    size_t capacity = startCapacity;
    size_t size = 0;
    char* buf = new (std::nothrow) char[capacity];
    if (buf == nullptr) {
      return nullptr;
    }
    char c = 0;
    while (in.get(c) && c != '\n') {
      if (size + 1 >= capacity) {
        char* newBuf = new (std::nothrow) char[capacity * 2];

        if (newBuf == nullptr) {
          delete[] buf;
          return nullptr;
        }

        for (size_t i = 0; i < size; ++i) {
          newBuf[i] = buf[i];
        }

        delete[] buf;

        buf = newBuf;
        capacity *= 2;
      }
      buf[size] = c;
      ++size;
    }
    buf[size] = '\0';
    return buf;
  }

  char* repSym(char* buf, const char* s)
  {
    size_t size = 0;
    buf[0] = '\0';
    for (size_t i = 0; s[i] != '\0'; ++i) {
      if (std::strchr(s + i + 1, s[i]) != nullptr && std::strchr(buf, s[i]) == nullptr) {
        buf[size] = s[i];
        ++size;
        buf[size] = '\0';
      }
    }
    return buf;
  }
}

int main()
{
  char* s = dorofeev::readline(std::cin);

  if (s == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  size_t len = std::strlen(s);

  char* result = new (std::nothrow) char[len + 1];

  if (result == nullptr) {
    std::cerr << "Error: not enough memory\n";
    delete[] s;
    return 1;
  }

  dorofeev::repSym(result, s);

  std::cout << result << '\n';

  delete[] result;
  delete[] s;

  return 0;
}
