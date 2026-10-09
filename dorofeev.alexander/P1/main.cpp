#include <iostream>

namespace dorofeev
{
  bool maxIncreasingRun(std::istream & in, std::size_t & result)
  {
    int prev = 0;
    int x = 0;
    std::size_t cur = 0;
    std::size_t best 0;

    while (in >> x)
    {
      if (x == 0)
      {
        result = best;
	return true;
      }
      if (cur > 0 && x >= prev)
      {
        ++cur;
      }
      else
      {
	cur = 1;
      }
      if (cur > best)
      {
	best = cur;
      }
      prev = x;
    }
    return false;
  }
}

int main()
{
  std::size_t result = 0;
  if (!dorofeev::maxIncreasingRun(std::cin, result))
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }
  std::cout << result << '\n';
  return 0;
}
