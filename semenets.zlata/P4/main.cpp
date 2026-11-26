#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>

namespace semenets {
  class String {
    char* data_;
    size_t size_;

  public:
    String();
    String(const char* str);
    String(const String& other);
    String(String&& other) noexcept;
    ~String();

    size_t size() const;
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;
    char& operator[](size_t i);
    const char& operator[](size_t i) const;
    const char* data() const;

    String& add(size_t pos, const char* str);
    String& add(size_t pos, char str);
    String& del(size_t start, size_t end);

    friend std::istream& getLine(std::istream& in, String& str);
  };
  std::istream& getLine(std::istream& in, String& str);
  String uncSym(const String& str, String literal);
}

int main()
{
  try {
    const semenets::String literal("abc_ef");
    semenets::String str;
    if (!semenets::getLine(std::cin, str)) {
      std::cerr << "Error: no input\n";
      return 1;
    }
    const semenets::String result = semenets::uncSym(str, literal);
    std::cout << result.data() << "\n";
  } catch (const std::bad_alloc&) {
    std::cerr << "Error: insufficient memory\n";
    return 1;
  }
  return 0;
}

namespace semenets {
  String::String():
    data_(new char[1]),
    size_(0)
  {
    data_[0] = '\0';
  }

  String::String(const char* str):
    data_(nullptr),
    size_(std::strlen(str))
  {
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; i++) {
      data_[i] = str[i];
    }
    data_[size_] = '\0';
  }

  String::String(const String& other):
    data_(new char[other.size_ + 1]),
    size_(other.size_)
  {
    for (size_t i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
  }

  String::String(String&& other) noexcept:
    data_(other.data_),
    size_(other.size_)
  {
    other.data_ = nullptr;
    other.size_ = 0;
  }

  String::~String()
  {
    delete[] data_;
  }

  String& String::operator=(const String& other)
  {
    if (this != &other) {
      char* s = new char[other.size_ + 1];
      for (size_t i = 0; i < other.size_; i++) {
        s[i] = other.data_[i];
      }
      s[other.size_] = '\0';
      delete[] data_;
      data_ = s;
      size_ = other.size_;
    }
    return *this;
  }

  String& String::operator=(String&& other) noexcept
  {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      other.data_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  char& String::operator[](size_t i)
  {
    return data_[i];
  }

  const char& String::operator[](size_t i) const
  {
    return data_[i];
  }

  size_t String::size() const
  {
    return size_;
  }

  const char* String::data() const
  {
    return data_ ? data_ : "";
  }

  String& String::add(size_t pos, const char* str)
  {
    if (pos > size_) {
      throw std::out_of_range("The string length is less then the position");
    }
    const size_t len_str_add = std::strlen(str);
    const size_t len_str = size_ + len_str_add;
    char* const new_str = new char[len_str + 1];
    for (size_t i = 0; i < pos; i++) {
      new_str[i] = data_[i];
    }
    size_t j = 0;
    for (size_t i = pos; i < pos + len_str_add; i++) {
      new_str[i] = str[j];
      ++j;
    }
    size_t k = pos;
    for (size_t i = pos + len_str_add; i < len_str; i++) {
      new_str[i] = data_[k];
      ++k;
    }
    new_str[len_str] = '\0';
    delete[] data_;
    data_ = new_str;
    size_ = len_str;
    return *this;
  }

  String& String::add(size_t pos, char str)
  {
    const char str1[2] = {str, '\0'};
    return add(pos, str1);
  }

  String& String::del(size_t start, size_t end)
  {
    if (start > size_) {
      throw std::out_of_range("The position more than length");
    }
    if (end > size_) {
      end = size_;
    }
    if (end < start) {
      end = start;
    }
    const size_t new_size = size_ - (end - start);
    char* const str = new char[new_size + 1];
    for (size_t i = 0; i < start; i++) {
      str[i] = data_[i];
    }
    size_t j = start;
    for (size_t i = end; i < size_; i++) {
      str[j] = data_[i];
      ++j;
    }
    str[new_size] = '\0';
    delete[] data_;
    data_ = str;
    size_ = new_size;
    return *this;
  }

  std::istream& getLine(std::istream& in, String& str)
  {
    const size_t i_size = 16;
    size_t izn_size = i_size;
    size_t size = 0;
    char* buf = new char[izn_size];
    char c = 0;
    while (in.get(c) && c != '\n') {
      if (size + 1 == izn_size) {
        izn_size *= 2;
        char* more_big = nullptr;
        try {
          more_big = new char[izn_size];
        } catch (const std::bad_alloc&) {
          delete[] buf;
          throw;
        }
        for (size_t i = 0; i < size; i++) {
          more_big[i] = buf[i];
        }
        delete[] buf;
        buf = more_big;
      }
      buf[size] = c;
      ++size;
    }
    if (size == 0 && in.fail()) {
      delete[] buf;
      return in;
    }
    if (in.eof()) {
      in.clear();
    }
    buf[size] = '\0';
    delete[] str.data_;
    str.data_ = buf;
    str.size_ = size;
    return in;
  }

  String uncSym(const String& str, String literal)
  {
    size_t len_lit = literal.size();
    literal.add(literal.size(), str.data());
    size_t i = 0;
    while (i < len_lit) {
      bool flag = false;
      for (size_t j = len_lit; j < literal.size();) {
        if (literal.data()[i] == literal.data()[j]) {
          flag = true;
          literal.del(j, j + 1);
        } else {
          j++;
        }
      }
      if (flag) {
        literal.del(i, i + 1);
        --len_lit;
      } else {
        ++i;
      }
    }
    return literal;
  }
}
