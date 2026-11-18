#pragma once

namespace serdyukov {
  struct SequenceReader {
  private:
    bool finished_;
  public:
    SequenceReader();
    int getNext();
    bool finished() const;
  };

}
