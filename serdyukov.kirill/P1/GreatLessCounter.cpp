#include "SequenceReader.hpp"
#include "GreatLessCounter.hpp"

namespace serdyukov {
  int GreatLessCounter::calculate(SequenceReader& reader)
  {
    int result = 0;
    int previous = 0;
    int current = 0;
    int next = reader.getNext();

    if (next == 0) {
      return 0;
    }

    while (next != 0) {
      previous = current;
      current = next;
      next = reader.getNext();

      if (previous != 0 && next != 0 && current < previous && current > next) {
        result++;
      }
    }
    return result;
  }
}
