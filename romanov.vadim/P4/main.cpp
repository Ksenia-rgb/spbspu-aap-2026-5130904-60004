#include <cctype>
#include <cstring>
#include <iostream>
namespace romanov
{
  char* readDynamicString();
  void removeLatin(char*);
}
int main()
{
  std::cout << "Write a line" << '\n';
  char* n = romanov::readDynamicString();
  romanov::removeLatin(n);
  std::cout << "The new line is " << n << '\n';
  delete[] n;
  return 0;
}
char* romanov::readDynamicString()
{
  int capacity = 10;
  int length = 0;
  char* buffer = new char[capacity];
  char ch;
  while (std::cin.get(ch) && ch != '\n')
  {
    if (length + 1 >= capacity)
    {
      capacity *= 2;
      char* newBuffer = new char[capacity];
      std::copy(buffer, buffer + length, newBuffer);
      delete[] buffer;
      buffer = newBuffer;
    }
    buffer[length] = ch;
    length++;
  }
  buffer[length] = '\0';
  return buffer;
}
void romanov::removeLatin(char * n)
{
  int write_index = 0;
  int read_index = 0;
  while(n[read_index] != '\0')
  {
    char ch = n[read_index];
    if (!std::isalpha(ch))
    {
      n[write_index] = n[read_index];
      write_index++;
    }
    read_index++;
  }
  n[write_index] = '\0';
}
