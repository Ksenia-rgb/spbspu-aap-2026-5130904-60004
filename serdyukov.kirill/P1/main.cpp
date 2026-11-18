#include <iostream>
#include <stdexcept>
#include "SequenceReader.hpp"
#include "GreatLessCounter.hpp"
int main()
{
  try {
    serdyukov::SequenceReader reader;
    serdyukov::GreatLessCounter counter;

    const int result = counter.calculate(reader);
    std::cout << result << '\n';
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

