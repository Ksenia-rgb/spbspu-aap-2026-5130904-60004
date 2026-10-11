#include <iostream>
#include <exception>
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
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
namespace fomin
{
  int func()
  {
    long int num;
    int len = 0;
    int max_len = 0;
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
      exit(1);
    }
  }
}
