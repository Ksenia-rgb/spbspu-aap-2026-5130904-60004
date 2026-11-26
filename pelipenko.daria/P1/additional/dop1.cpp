#include <exception>
#include <iostream>
#include <stdexcept>

namespace pelipenko {

struct ISeqProperty {
  size_t operator()() const { return result(); }

  void operator()(int i) { next(i); }

  virtual ~ISeqProperty() = default;

private:
  virtual size_t result() const = 0;
  virtual void next(int i) = 0;
};

class MaxEqualRun : public ISeqProperty {
public:
  MaxEqualRun() = default;

private:
  size_t result() const override {
    if (!is_started) {
      throw std::invalid_argument("Input is not a sequence");
    }
    return max_length;
  }

  void next(int i) override {
    curr = i;

    if (!is_started) {
      prev = curr;
      length = 1;
      max_length = 1;
      is_started = true;
      return;
    }

    if (curr == prev) {
      ++length;
    } else {
      length = 1;
      prev = curr;
    }

    if (length > max_length) {
      max_length = length;
    }
  }

  long long prev = 0;
  long long curr = 0;
  int length = 0;
  int max_length = 0;
  bool is_started = false;
};

}

int main() {
  try {
    pelipenko::ISeqProperty *prop = new pelipenko::MaxEqualRun();

    int val = 0;
    bool has_elements = false;

    while (std::cin >> val) {
      if (val == 0) {
        break;
      }
      (*prop)(val);
      has_elements = true;
    }

    if (std::cin.fail() && !std::cin.eof()) {
      delete prop;
      std::cerr << "Input error\n";
      return 1;
    }

    if (!has_elements) {
      delete prop;
      std::cerr << "Input is not a sequence\n";
      return 1;
    }

    const size_t answer = (*prop)();
    std::cout << answer << "\n";

    delete prop;
    return 0;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
