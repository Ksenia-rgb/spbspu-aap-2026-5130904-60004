#ifndef SEQUENCE_READER_HPP
#define SEQUENCE_READER_HPP

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
#endif
