#include <iostream>
#include <stdexcept>

namespace zabrodotsky
{
  struct SignChangeCounter
  {
    void operator()(int next)
    {
      if ((prev_ < 0 && next > 0) || (prev_ > 0 && next < 0))
      {
        if (count_ == static_cast< size_t >(-1))
        {
          throw std::overflow_error("Overflow");
        }
        ++count_;
      }
      prev_ = next;
    }
    size_t operator()() const
    {
      return count_;
    }

  private:
    int prev_ = 0;
    size_t count_ = 0;
  };
}
int main()
{
  zabrodotsky::SignChangeCounter counter;
  int value = 0;
  try
  {
    while (std::cin >> value && value != 0)
    {
      counter(value);
    }
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }
  std::cout << counter() << "\n";
  return 0;
}
