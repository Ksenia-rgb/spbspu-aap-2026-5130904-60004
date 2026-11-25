#include <iostream>
#include <cstddef>
#include <cctype>
#include <new>

namespace sierra
{
  char* readLine(std::istream& in, size_t& size);
  char* toLowerLatin(const char* src, char* dst) noexcept;
}

char* sierra::readLine(std::istream& in, size_t& size)
{
  size_t capacity = 1;
  char* str = new char[capacity];
  size = 0;
  char c = '\0';
  while (in.get(c) && c != '\n')
  {
    if (size + 1 == capacity)
    {
      char* bigger = nullptr;
      try
      {
        bigger = new char[capacity * 2];
      }
      catch (const std::bad_alloc&)
      {
        delete[] str;
        throw;
      }
      for (size_t i = 0; i < size; ++i)
      {
        bigger[i] = str[i];
      }
      delete[] str;
      str = bigger;
      capacity *= 2;
    }
    str[size] = c;
    ++size;
  }
  str[size] = '\0';
  return str;
}

char* sierra::toLowerLatin(const char* src, char* dst) noexcept
{
  size_t i = 0;
  for (; src[i] != '\0'; ++i)
  {
    const unsigned char c = static_cast< unsigned char >(src[i]);
    if (std::isupper(c))
    {
      dst[i] = static_cast< char >(std::tolower(c));
    }
    else
    {
      dst[i] = src[i];
    }
  }
  dst[i] = '\0';
  return dst;
}

int main()
{
  size_t size = 0;
  char* input = nullptr;
  try
  {
    input = sierra::readLine(std::cin, size);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  char* result = nullptr;
  try
  {
    result = new char[size + 1];
  }
  catch (const std::bad_alloc&)
  {
    delete[] input;
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  sierra::toLowerLatin(input, result);
  std::cout << result << '\n';
  delete[] input;
  delete[] result;
  return 0;
}