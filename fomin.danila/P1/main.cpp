<<<<<<< HEAD
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
=======
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
>>>>>>> 6f0d363 (cherry-picking)
namespace fomin
{
  int func();
}
int main()
{
  try
  {
    const int max_len_over_zero = fomin::func();
    std::cout << max_len_over_zero << "\n";
<<<<<<< HEAD
  }
  catch (const std::exception &e)
=======
    return 0;
  }
  catch (std::exception& e)
>>>>>>> 6f0d363 (cherry-picking)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
namespace fomin
{
  int func()
  {
    long int num = 0;
    int len = 0;
    int max_len = 0;
<<<<<<< HEAD
    while (std::cin >> num)
    {
      if (std::cin.peek() == '.' || std::cin.peek() == ',')
      {
        throw std::runtime_error("Not an integer");
      }
      if (num == 0)
      {
        if (max_len < len)
        {
          max_len = len;
        }
        return max_len;
      }
      if (num % 2 == 0)
      {
        len++;
      }
      else
      {
        if (max_len < len)
        {
          max_len = len;
        }
        len = 0;
      }
    }
    throw std::runtime_error("Writed not a int");
=======
    try
    {
      if (std::cin >> num)
      {
        while (num != 0)
        {
          if (std::cin >> num)
          {
            if (num > 0)
            {
              len += 1;
            }
            else
            {
              max_len = len;
              len = 0;
            }
          }
          else
          {
            throw std::runtime_error("Write not a integer");
          }
        }
        return max_len;
      }
      else
      {
        throw std::runtime_error("Writed not a integer");
      }
      return max_len;
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << "\n";
      std::exit(1);
    }
>>>>>>> 6f0d363 (cherry-picking)
  }
}
