#ifndef GREAT_LESS_COUNTER_HPP
#define GREAT_LESS_COUNTER_HPP
#include "SequenceReader.hpp"

namespace serdyukov {
  struct GreatLessCounter {
  public:
    int calculate(SequenceReader& reader);
  };

}
#endif
