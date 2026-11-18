#include "SequenceReader.hpp"
#include <stdexcept>
#include <iostream>

namespace serdyukov {
  SequenceReader::SequenceReader():
    finished_(false)
  {}
  int SequenceReader::getNext()
  {
    int val = 0;

    if (!(std::cin >> val)) {
      throw std::invalid_argument("You should try harder");
    }

    if (val == 0) {
      finished_ = true;
    }
    return val;
  }
  bool SequenceReader::finished() const
  {
    return finished_;
  }
}
