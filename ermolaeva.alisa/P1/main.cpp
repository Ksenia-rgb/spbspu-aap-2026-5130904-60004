#include <iostream>
#include <clocale>
#include <stdexcept>

int locMaxNum();
int main()
{
  std::setlocale(LC_ALL, "RU");
  std::cout<< "Введите последовательность чисел\n";
  try
  {
    const int result=locMaxNum();
    std::cout<< result <<"\n";
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}

int locMaxNum()
{
  int first=0, second=0, third=0;
  int input_count=0, locmaxcount=0;
  while (std::cin>>third&&third !=0)
  {
    input_count++;
    if (input_count >= 3 && second > third && second > first)
    {
      locmaxcount++;
    }
    first=second;
    second=third;
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("Только целые числа!!!");
  }
  if (input_count==0)
  {
    throw std::logic_error("где последовательсность?");
  }
  return locmaxcount;
}
