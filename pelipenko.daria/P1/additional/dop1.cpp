#include <iostream>
#include <stdexcept>

namespace pelipenko
{

  struct ISeqProperty
  {
    size_t operator()() const
    {
      return result();
    }
    void operator()(int i)
    {
      next(i);
    }
    virtual ~ISeqProperty() = default;

  private:
    virtual size_t result() const = 0;
    virtual void next(int i) = 0;
  };

  class MaxEqualRun: public ISeqProperty
  {
  public:
    MaxEqualRun():
      prev_(0),
      curr_(0),
      length_(0),
      max_length_(0),
      is_started_(false)
    {}

  private:
    size_t result() const override
    {
      if (!is_started_)
      {
        throw std::invalid_argument("Input is not a sequence");
      }
      return max_length_;
    }

    void next(int i) override
    {
      curr_ = i;
      if (!is_started_)
      {
        prev_ = curr_;
        length_ = 1;
        max_length_ = 1;
        is_started_ = true;
        return;
      }
      if (curr_ == prev_)
      {
        ++length_;
      }
      else
      {
        length_ = 1;
        prev_ = curr_;
      }
      if (length_ > max_length_)
      {
        max_length_ = length_;
      }
    }

    long long prev_;
    long long curr_;
    int length_;
    int max_length_;
    bool is_started_;
  };

}

int main()
{
  try
  {
    pelipenko::ISeqProperty *const prop = new pelipenko::MaxEqualRun();
    int val = 0;
    bool has_elements = false;
    while (std::cin >> val)
    {
      if (val == 0)
      {
        break;
      }
      (*prop)(val);
      has_elements = true;
    }
    if (std::cin.fail() && !std::cin.eof())
    {
      delete prop;
      std::cerr << "Input error\n";
      return 1;
    }
    if (!has_elements)
    {
      delete prop;
      std::cerr << "Input is not a sequence\n";
      return 1;
    }
    const size_t answer = (*prop)();
    std::cout << answer << "\n";
    delete prop;
    return 0;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
