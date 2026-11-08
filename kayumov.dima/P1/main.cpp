#include <iostream>
#include <stdexcept>

namespace kayumov
{
  int maxChislo();
}

int main()
{
  try
  {
    const int result = kayumov::maxChislo();
    std::cout << result << "\n";
    return 0;
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error & a)
  {
    std::cerr << a.what() << "\n";
    return 2;
  }
}
