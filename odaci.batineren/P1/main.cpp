#include <cctype>
#include <iostream>
#include <limits>

namespace odaci
{
  int countMax(std::istream & in, int & result)
  {
    int value = 0;
    int max_value = 0;
    int count = 0;
    bool has_elements = false;
    bool count_overflow = false;
    while (in >> value)
    {
      const int next = in.eof() ? std::char_traits< char >::eof() : in.peek();
      if (next != std::char_traits< char >::eof() && !std::isspace(next))
      {
        return 1;
      }
      if (value == 0)
      {
        break;
      }
      if (!has_elements || value > max_value)
      {
        has_elements = true;
        max_value = value;
        count = 1;
        count_overflow = false;
      }
      else if (value == max_value)
      {
        if (count == std::numeric_limits< int >::max())
        {
          count_overflow = true;
        }
        else
        {
          ++count;
        }
      }
    }
    if (!in)
    {
      return 1;
    }
    if (!has_elements || count_overflow)
    {
      return 2;
    }
    result = count;
    return 0;
  }
}

int main()
{
  int result = 0;
  const int status = odaci::countMax(std::cin, result);
  if (status == 1)
  {
    std::cerr << "Error: not a sequence\n";
    return 1;
  }
  if (status == 2)
  {
    std::cerr << "Error: cannot compute maximum count\n";
    return 2;
  }
  std::cout << result << '\n';
  return 0;
}
