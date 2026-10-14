#include <iostream>

namespace alekseev
{
  int find_almost_max()
  {
    int x = 0;
    int max1 = 0;
    int max2 = 0;
    int count = 0;

    if (!(std::cin >> x))
    {
      std::cerr << "Данные нельзя идентифицировать как последовательность" << std::endl;
      return 1;
    }

    if (x == 0)
    {
      std::cerr << "Последовательность слишком коротка" << std::endl;
      return 2;
    }

    max1 = x;
    count = 1;

    while (true)
    {
      if (!(std::cin >> x))
      {
        std::cerr << "Данные нельзя идентифицировать как последовательность" << std::endl;
        return 1;
      }

      if (x == 0)
      {
        break;
      }

      count++;

      if (x > max1)
      {
        max2 = max1;
        max1 = x;
      }
      else if (count == 2 || (x > max2 && x < max1))
      {
        max2 = x;
      }
    }

    if (count < 2)
    {
      std::cerr << "Нельзя найти второй максимум" << std::endl;
      return 2;
    }

    if (max1 == max2 && count == 1)
    {
      std::cerr << "Нельзя найти второй максимум" << std::endl;
      return 2;
    }

    std::cout << max2 << std::endl;
    return 0;
  }
}

int main()
{
  return alekseev::find_almost_max();
}