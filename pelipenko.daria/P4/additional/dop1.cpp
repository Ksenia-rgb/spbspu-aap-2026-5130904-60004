#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace pelipenko
{

  class MyString
  {
  public:
    MyString() : data_(new char[1]), size_(0)
    {
      data_[0] = '\0';
    }

    MyString(const char *str)
    {
      size_ = 0;
      if (str != nullptr)
      {
        while (str[size_] != '\0')
        {
          ++size_;
        }
      }
      data_ = new char[size_ + 1];
      for (std::size_t i = 0; i < size_; ++i)
      {
        data_[i] = str[i];
      }
      data_[size_] = '\0';
    }

    MyString(const MyString &other) : data_(new char[other.size_ + 1]), size_(other.size_)
    {
      for (std::size_t i = 0; i <= size_; ++i)
      {
        data_[i] = other.data_[i];
      }
    }

    MyString(MyString &&other) noexcept : data_(other.data_), size_(other.size_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
    }

    ~MyString()
    {
      delete[] data_;
    }

    MyString &operator=(const MyString &other)
    {
      if (this != &other)
      {
        char *const new_data = new char[other.size_ + 1];
        for (std::size_t i = 0; i <= other.size_; ++i)
        {
          new_data[i] = other.data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
      }
      return *this;
    }

    MyString &operator=(MyString &&other) noexcept
    {
      if (this != &other)
      {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void insert(std::size_t pos, char c)
    {
      if (pos > size_)
      {
        throw std::out_of_range("Index out of range");
      }
      char *const new_data = new char[size_ + 2];
      for (std::size_t i = 0; i < pos; ++i)
      {
        new_data[i] = data_[i];
      }
      new_data[pos] = c;
      for (std::size_t i = pos; i < size_; ++i)
      {
        new_data[i + 1] = data_[i];
      }
      new_data[size_ + 1] = '\0';
      delete[] data_;
      data_ = new_data;
      ++size_;
    }

    void erase(std::size_t pos)
    {
      if (pos >= size_)
      {
        throw std::out_of_range("Index out of range");
      }
      char *const new_data = new char[size_];
      for (std::size_t i = 0, j = 0; i < size_; ++i)
      {
        if (i != pos)
        {
          new_data[j++] = data_[i];
        }
      }
      new_data[size_ - 1] = '\0';
      delete[] data_;
      data_ = new_data;
      --size_;
    }

    char &operator[](std::size_t index)
    {
      return data_[index];
    }

    const char &operator[](std::size_t index) const
    {
      return data_[index];
    }

    const char *cStr() const
    {
      return data_;
    }

    const char *data() const
    {
      return data_;
    }

    std::size_t size() const
    {
      return size_;
    }

  private:
    char *data_;
    std::size_t size_;
  };

  void getline(std::istream &in, MyString &str)
  {
    str = MyString();
    char ch = 0;
    while (in.get(ch) && ch != '\n')
    {
      str.insert(str.size(), ch);
    }
  }

  MyString getCommon(const MyString &str1, const MyString &str2)
  {
    MyString out;
    for (std::size_t i = 0; i < str2.size(); ++i)
    {
      const char ch = str2[i];
      bool found = false;
      for (std::size_t j = 0; j < str1.size(); ++j)
      {
        if (str1[j] == ch)
        {
          found = true;
          break;
        }
      }
      if (found)
      {
        bool already_added = false;
        for (std::size_t k = 0; k < out.size(); ++k)
        {
          if (out[k] == ch)
          {
            already_added = true;
            break;
          }
        }
        if (!already_added)
        {
          out.insert(out.size(), ch);
        }
      }
    }
    for (std::size_t i = 0; i < out.size(); ++i)
    {
      for (std::size_t j = i + 1; j < out.size(); ++j)
      {
        if (out[i] > out[j])
        {
          const char temp = out[i];
          out[i] = out[j];
          out[j] = temp;
        }
      }
    }
    return out;
  }

} // namespace pelipenko

int main()
{
  try
  {
    pelipenko::MyString str1;
    if (!std::cin)
    {
      throw std::invalid_argument("Input error");
    }
    pelipenko::getline(std::cin, str1);
    if (str1.size() == 0)
    {
      throw std::invalid_argument("Empty input");
    }
    const pelipenko::MyString str2("def_ghk");
    const pelipenko::MyString res = pelipenko::getCommon(str1, str2);
    std::cout << res.cStr() << "\n";
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
