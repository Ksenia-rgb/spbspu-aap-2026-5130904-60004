#include <iostream>
#include <clocale>
int localMaxNumber();
int main()
{
  std::setlocale(LC_ALL, "Russian");
  std::cout << "Введите последовательность чисел, 0 - конец ввода\n";
  try
  {
    int res = localMaxNumber();
    std::cout << res << "\n";
  }
  catch (std::invalid_argument &e)
  {
    std::cout << e.what();
    return 1;
  }
  catch (std::logic_error &e)
  {
    std::cout << e.what();
    return 2;
  }
  return 0;
}
int localMaxNumber()
{
  int third = 0, second = 0, first = 0;
  int inputCount = 0, localMaxCount = 0;
  while (std::cin >> third && third != 0)
  {
    inputCount++;
    if (inputCount >= 3 && second > third && second > first)
    {
      localMaxCount++;
    }
    first = second;
    second = third;
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("Программа принимает только целые числа\n");
  }
  if (inputCount == 0)
  {
    throw std::logic_error("Слишшком мало значений\n");
  }
  return localMaxCount;
}
