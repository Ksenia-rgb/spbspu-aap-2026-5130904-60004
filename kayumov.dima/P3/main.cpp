#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace kayumov
{
  constexpr std::size_t MAX_STATIC_SIZE = 10000;

  std::size_t findLongestSeriesRow(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if ((rows == 0) || (cols == 0))
    {
      return 0;
    }

    std::size_t bestRow = 0;
    std::size_t maxGlobalStreak = 0;

    for (std::size_t i = 0; i < rows; ++i)
    {
      std::size_t currentStreak = 1;
      std::size_t rowMaxStreak = 1;

      for (std::size_t j = 1; j < cols; ++j)
      {
        if (matrix[(i * cols) + j] == matrix[(i * cols) + j - 1])
        {
          ++currentStreak;
        }
        else
        {
          currentStreak = 1;
        }

        if (currentStreak > rowMaxStreak)
        {
          rowMaxStreak = currentStreak;
        }
      }

      if (rowMaxStreak > maxGlobalStreak)
      {
        maxGlobalStreak = rowMaxStreak;
        bestRow = i + 1;
      }
    }

    return bestRow;
  }
}

int main(int argc, char** argv)
{
  constexpr int REQUIRED_ARGC = 4;

  if (argc != REQUIRED_ARGC)
  {
    std::cerr << "Error: Exactly 3 arguments are required.\n";
    return 1;
  }

  if (!((argv[1][0] == '1' || argv[1][0] == '2') && (argv[1][1] == '\0')))
  {
    std::cerr << "Error: First parameter must be exactly 1 or 2.\n";
    return 1;
  }

  const int mode = argv[1][0] - '0';
  int* dynamicMatrix = nullptr;

  try
  {
    std::ifstream in(argv[2]);
    if (!in.is_open())
    {
      throw std::runtime_error("Error: Cannot open input file.");
    }

    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!(in >> rows >> cols))
    {
      throw std::runtime_error("Error: Cannot read matrix dimensions.");
    }

    int* matrix = nullptr;
    int stackMatrix[kayumov::MAX_STATIC_SIZE];

    if (mode == 1)
    {
      if ((rows * cols) > kayumov::MAX_STATIC_SIZE)
      {
        throw std::runtime_error("Error: Matrix size exceeds static array limit.");
      }
      matrix = stackMatrix;
    }
    else
    {
      dynamicMatrix = new int[rows * cols];
      matrix = dynamicMatrix;
    }

    for (std::size_t i = 0; i < (rows * cols); ++i)
    {
      if (!(in >> matrix[i]))
      {
        throw std::runtime_error("Error: Not enough elements in the file.");
      }
    }

    const std::size_t answer = kayumov::findLongestSeriesRow(matrix, rows, cols);

    std::ofstream out(argv[3]);
    if (!out.is_open())
    {
      throw std::runtime_error("Error: Cannot open output file.");
    }
    out << answer << '\n';

    delete[] dynamicMatrix;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    delete[] dynamicMatrix;
    return 2;
  }

  return 0;
}
