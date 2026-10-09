#include <iostream>

namespace chervov
{
  void countSumOfPrevTwo()
  {
    const int MinSequenceLength = 3;
    int firstNumber = 0, secondNumber = 0, currentNumber = 0;
    int lengthSequence = 0;

    int count = 0;

    while (std::cin >> currentNumber)
    {
      if (currentNumber == 0)
      {
        if (lengthSequence < MinSequenceLength)
        {
          throw std::runtime_error("Lenght sequence short");
        }
        else
        {
          std::cout << count << "\n";
        }
      }

      lengthSequence++;

      if (lengthSequence > 2)
      {
        if (firstNumber + secondNumber == currentNumber)
        {
          count++;
        }
      }

      firstNumber = secondNumber;
      secondNumber = currentNumber;
    }

    throw std::invalid_argument("Invalid sequence number");
  }
}

int main()
{
  try
  {
    chervov::countSumOfPrevTwo();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
