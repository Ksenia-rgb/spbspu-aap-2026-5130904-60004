#include <iostream>
#include <clocale>
int LocalMaxNumber();
int main()
{
  std::setlocale(LC_ALL, "Russian");
  std::cout << "Введите последовательность чисел, 0 - конец ввода, в последовательность не входит\n";
  try 
  {
    int res = LocalMaxNumber();
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
int LocalMaxNumber()
{
  int third = 0, second = 0, first = 0;
  int InputCount = 0, MaxNumber = 0;
  while (std::cin >> third && third != 0)
  {
    InputCount++;
    if (InputCount >= 3 && second > third && second > first)
    {
      MaxNumber++;
    }
  
    first = second;
    second = third;
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("Программа принимает только целые числа\n");
  }
  if (InputCount < 3)
  {
    throw std::logic_error("Подсчет количества локальных максимумов требует как минимум 3 числа\n");
  }
  return MaxNumber;
}
