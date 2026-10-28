#include <iostream>
#include <fstream>
#include <new>

namespace alekseev
{
  const long long MAX_FIXED = 10000;

  bool readSize(std::istream & in, int & rows, int & cols)
  {
    if (!(in >> rows >> cols))
    {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::istream & in, int * data, long long count)
  {
    for (long long i = 0; i < count; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  int countLocMin(const int * m, int rows, int cols)
  {
    int result = 0;
    for (int i = 1; i < rows - 1; ++i)
    {
      for (int j = 1; j < cols - 1; ++j)
      {
        int v = m[i * cols + j];
        bool isMin = true;
        for (int di = -1; di <= 1 && isMin; ++di)
        {
          for (int dj = -1; dj <= 1; ++dj)
          {
            if (di == 0 && dj == 0)
            {
              continue;
            }
            if (m[(i + di) * cols + (j + dj)] <= v)
            {
              isMin = false;
              break;
            }
          }
        }
        if (isMin)
        {
          ++result;
        }
      }
    }
    return result;
  }
}




int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }

  int num = 0;
  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    num = 1;
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    num = 2;
  }
  else
  {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!alekseev::readSize(input, rows, cols))
  {
    std::cerr << "Invalid matrix size\n";
    return 2;
  }

  long long count = static_cast< long long >(rows) * cols;
  int result = 0;

  if (num == 1)
  {
    if (count > alekseev::MAX_FIXED)
    {
      std::cerr << "Matrix is too large for fixed array\n";
      return 2;
    }
    int fixed[alekseev::MAX_FIXED] = {};
    if (!alekseev::readElements(input, fixed, count))
    {
      std::cerr << "Invalid matrix data\n";
      return 2;
    }
    result = alekseev::countLocMin(fixed, rows, cols);
  }
  else
  {
    int * dynamic = nullptr;
    try
    {
      dynamic = new int[count];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Cannot allocate memory\n";
      return 2;
    }
    if (!alekseev::readElements(input, dynamic, count))
    {
      delete[] dynamic;
      std::cerr << "Invalid matrix data\n";
      return 2;
    }
    result = alekseev::countLocMin(dynamic, rows, cols);
    delete[] dynamic;
  }

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Cannot open output file\n";
    return 2;
  }
  output << result << '\n';
  return 0;
}