#include <iostream>
#include <stdexcept>

namespace semenets {
  struct ISeqProperty {
    size_t operator()() const;
    void operator()(int value);
    virtual ~ISeqProperty() = default;

  private:
    virtual size_t result() const = 0;
    virtual void next(int value) = 0;
  };

  struct countSignChanges: ISeqProperty {
    countSignChanges();
  private:
    virtual size_t result() const override;
    virtual void next(int value) override;
    int count_;
    int count_num_;
    int znak_past_;
    int znak_new_;
  };

  size_t ISeqProperty::operator()() const
  {
    return result();
  }

  void ISeqProperty::operator()(int value)
  {
    return next(value);
  }

  countSignChanges::countSignChanges():
    count_(0),
    count_num_(0),
    znak_past_(0),
    znak_new_(0)
  {}

  void countSignChanges::next(int value)
  {
    ++count_num_;
    if (value > 0) {
      znak_new_ = 1;
    } else {
      znak_new_ = -1;
    }
    if (count_num_ != 1 && znak_new_ != znak_past_) {
      ++count_;
    }
    znak_past_ = znak_new_;
  }

  size_t countSignChanges::result() const
  {
    return count_;
  }
}
int main()
{
  try {
    semenets::countSignChanges counter_;
    semenets::countSignChanges& counter = counter_;

    while (true) {
      int value = 0;
      if (!(std::cin >> value)) {
        throw std::invalid_argument("Not a number enter");
      }
      if (value == 0) {
        break;
      }
      counter(value);
    }
    std::cout << counter() << "\n";
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
