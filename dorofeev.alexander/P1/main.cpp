#include <iostream>

namespace dorofeev
{
  int maxMonoInt(bool & ok)
  {
    int x = 0;
    int prev = 0;
    int cur = 0;
    int best = 0;
    bool first = true;
    ok = false;

    while (std::cin >> x)
    {
      if (x = 0)
      {
        ok = true;
        break;
      }
      if (!first && x >= prev)
      {
        cur++;
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
      first = false;
    }
  return best;
  }
}

int main()
{
  bool ok = false;
  int result = dorofeev::maxMonoInt(ok);
  if (!ok)
  {
    std::cerr << "Error: input is not a valid sequence\n";
    return 1;
  }
  std::cout << result << "\n";
  return 0;
}
