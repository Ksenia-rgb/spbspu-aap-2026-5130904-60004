#include <iostream>
#include <stdexcept>

namespace ibragimov
{
  struct SequenceCounter
  {
  public:
    SequenceCounter();
    void operator()(int next);
    int operator()() const;

  private:
    int count_;
  };

  struct DivRemCounter
  {
  public:
    DivRemCounter();
    void operator()(int next);
    int operator()() const;

  private:
    SequenceCounter total_;
    int count_;
    int prev_;
  };
}

int main()
{
  try
  {
    ibragimov::DivRemCounter counter;
    int value = 0;

    while (true)
    {
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Not a number");
      }
      if (value == 0)
      {
        break;
      }
      counter(value);
    }
    std::cout << counter() << std::endl;
    return 0;
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
}

ibragimov::SequenceCounter::SequenceCounter():
  count_(0)
{}

void ibragimov::SequenceCounter::operator()(int)
{
  ++count_;
}

int ibragimov::SequenceCounter::operator()() const
{
  return count_;
}

ibragimov::DivRemCounter::DivRemCounter():
  total_(),
  count_(0),
  prev_(0)
{}

void ibragimov::DivRemCounter::operator()(int next)
{
  if (prev_ != 0 && (next % prev_ == 0))
  {
    count_++;
  }
  total_(next);
  prev_ = next;
}

int ibragimov::DivRemCounter::operator()() const
{
  if (total_() < 2)
  {
    throw std::logic_error("Not enough numbers");
  }
  return count_;
}
