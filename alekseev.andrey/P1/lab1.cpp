#include <iostream>

namespace alekseev {
int findAlmostMax() {
  int x = 0;
  int max1 = 0;
  int max2 = 0;
  int count = 0;

  if (!(std::cin >> x)) {
    std::cerr << "Input is not a sequence" << std::endl;
    return 1;
  }

  if (x == 0) {
    std::cerr << "Sequence is too short" << std::endl;
    return 2;
  }

  max1 = x;
  count = 1;

  while (true) {
    if (!(std::cin >> x)) {
      std::cerr << "The data cannot be identified as a sequence" << std::endl;
      return 1;
    }

    if (x == 0) {
      break;
    }

    count++;

    if (x > max1) {
      max2 = max1;
      max1 = x;
    } else if (count == 2 || (x > max2 && x < max1)) {
      max2 = x;
    }
  }

  if (count < 2) {
    std::cerr << "The second maximum cannot be found" << std::endl;
    return 2;
  }

  std::cout << max2 << std::endl;
  return 0;
}
}  // namespace alekseev

int main() { return alekseev::findAlmostMax(); }
