#include <exception>
#include <iostream>
#include <stdexcept>

namespace pluzhnik
{
  int getMaxLen()
  {
    int val = 0;
    int temp_val = 0;
    int len_pos = 1;
    int max_len_pos = 1;

    if (!(std::cin >> val))
    {
      throw std::invalid_argument("Error: invalid input format");
    }

    if (val == 0)
    {
      return 0;
    }

    temp_val = val;

    while (true)
    {
      if (!(std::cin >> val))
      {
        throw std::invalid_argument("Error: invalid input format");
      }

      if (val == 0)
      {
        if (len_pos > max_len_pos)
        {
          max_len_pos = len_pos;
        }
        break;
      }

      if (val >= temp_val)
      {
        ++len_pos;
      }
      else if (len_pos > max_len_pos)
      {
        max_len_pos = len_pos;
        len_pos = 1;
      }
      else
      {
        len_pos = 1;
      }

      temp_val = val;
    }

    return max_len_pos;
  }
}

int main()
{
  try
  {
    const int max_len_pos = pluzhnik::getMaxLen();
    std::cout << max_len_pos << "\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

