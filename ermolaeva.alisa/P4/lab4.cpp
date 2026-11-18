#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>

namespace ermolaeva {

std::size_t countDiffLat(const char *str) {
  constexpr int alphabet_size = 26;
  char seen[alphabet_size] = {};
  std::size_t count = 0;

  for (; *str != '\0'; ++str) {
    const unsigned char c = static_cast<unsigned char>(*str);
    if (std::isalpha(c)) {
      const int idx = std::tolower(c) - 'a';
      if (idx >= 0 && idx < alphabet_size && !seen[idx]) {
        seen[idx] = 1;
        ++count;
      }
    }
  }
  return count;
}

char *readLine(std::istream &in) {
  constexpr std::size_t initial_capacity = 16;
  std::size_t capacity = initial_capacity;
  std::size_t size = 0;
  char *buf = new (std::nothrow) char[capacity];
  if (buf == nullptr) {
    return nullptr;
  }

  char c = '\0';
  while (in.get(c) && c != '\n') {
    if (size + 1 >= capacity) {
      if (capacity > std::numeric_limits<std::size_t>::max() / 2) {
        delete[] buf;
        return nullptr;
      }
      const std::size_t new_capacity = capacity * 2;
      char *const bigger = new (std::nothrow) char[new_capacity];
      if (bigger == nullptr) {
        delete[] buf;
        return nullptr;
      }
      std::memcpy(bigger, buf, size);
      delete[] buf;
      buf = bigger;
      capacity = new_capacity;
    }
    buf[size++] = c;
  }
  buf[size] = '\0';
  return buf;
}

} // namespace ermolaeva

int main() {
  char *const line = ermolaeva::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Error: not enough memory to read the string\n";
    return 1;
  }
  if (line[0] == '\0' && std::cin.eof()) {
    std::cerr << "Error: empty input\n";
    delete[] line;
    return 1;
  }

  std::cout << ermolaeva::countDiffLat(line) << '\n';
  delete[] line;
  return 0;
}
