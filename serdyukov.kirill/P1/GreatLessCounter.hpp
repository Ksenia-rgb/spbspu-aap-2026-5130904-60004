#pragma once
#include "SequenceReader.hpp"

namespace serdyukov {
  struct GreatLessCounter {
  public:
    int calculate(SequenceReader& reader);
  };

}
