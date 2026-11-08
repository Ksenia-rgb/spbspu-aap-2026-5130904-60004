#include <iostream>
#include <stdexcept>

namespace chervov
{
  struct SumDupCount
  {
  public:
    SumDupCount();
    void operator()(int num);
    int operator()() const;
  private:
    const int min_sequence_length_;
    int first_;
    int second_;
    int length_;
    int count_;
  };
}

int main()
{
  try
  {
    chervov::SumDupCount counter;
    int value = 0;
    while (true)
    {
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Invalid sequence number");
      }

      if (value == 0)
      {
        break;
      }
      counter(value);
    }
    std::cout << counter() << "\n";
    return 0;
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
}

void chervov::SumDupCount::operator()(int num)
{
  ++length_;
  if (length_ >= min_sequence_length_ && num == first_ + second_)
  {
    ++count_;
  }
  second_ = first_;
  first_ = num;
}

int chervov::SumDupCount::operator()() const
{
  if (length_ < min_sequence_length_)
  {
    throw std::runtime_error("Length sequence short");
  }
  return count_;
}

chervov::SumDupCount::SumDupCount():
  min_sequence_length_(3),
  first_(0),
  second_(0),
  length_(0),
  count_(0)
{}

