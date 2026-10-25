#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <limits>
#include <cstring>
#include <cstdlib>

namespace zabrodotsy
{
  bool isNumber(const char* str)
  {
    if (str == nullptr || str[0] == '\0')
    {
      return false;
    }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
      if (str[1] == '\0')
      {
        return false;
      }
      start = 1;
    }
    for (size_t i = start; str[i] != '\0'; ++i)
    {
      if (!std::isdigit(static_cast< unsigned char >(str[i])))
      {
        return false;
      }
    }
    return true;
  }

  int processMatrix(const int* matrix, int rows, int columns)
  {
    if (rows == 0 || columns == 0)
    {
      return 0;
    }
    int valid_columns = 0;
    for (int j = 0; j < columns; ++j)
    {
      bool duplicates = false;
      for (int i = 0; i < rows - 1; ++i)
      {
        if (matrix[i * columns + j] == matrix[(i + 1) * columns + j])
        {
          duplicates = true;
          break;
        }
      }
      if (!duplicates)
      {
        valid_columns++;
      }
    }
    return valid_columns;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid number of arguments. Expected 3 parameters." << std::endl;
    return 1;
  }
  const char* const num_param = argv[1];
  const char* const input_param = argv[2];
  const char* const output_param = argv[3];
  if (!zabrodotsy::isNumber(num_param))
  {
    std::cerr << "Error: Not a number" << std::endl;
    return 1;
  }
  const int mode = std::atoi(num_param);
  if (mode != 1 && mode != 2)
  {
    std::cerr << "Error: Parameter is out of range" << std::endl;
    return 1;
  }
  std::ifstream in_file(input_param);
  if (!in_file.is_open())
  {
    std::cerr << "Error: Can't open input file" << std::endl;
    return 2;
  }
  const int max_element_buf = 100;
  char buf[max_element_buf];
  std::vector< int > parsed_elements;
  while (in_file >> buf)
  {
    if (!zabrodotsy::isNumber(buf))
    {
      std::cerr << "Error: Not a integer number" << std::endl;
      return 2;
    }
    char* end_ptr = nullptr;
    long long temp = std::strtoll(buf, &end_ptr, 10);
    if (temp < std::numeric_limits< int >::min() || temp > std::numeric_limits< int >::max())
    {
      std::cerr << "Error: Integer overflow" << std::endl;
      return 2;
    }
    parsed_elements.push_back(static_cast< int >(temp));
  }
  in_file.close();
  if (parsed_elements.empty())
  {
    std::cerr << "Error: File is empty" << std::endl;
    return 2;
  }
  if (parsed_elements.size() < 2)
  {
    std::cerr << "Error: Matrix dimensions are missing" << std::endl;
    return 2;
  }
  const int rows = parsed_elements[0];
  const int cols = parsed_elements[1];
  if (rows < 0 || cols < 0)
  {
    std::cerr << "Error: Matrix dimensions cannot be negative" << std::endl;
    return 2;
  }
  const size_t expected_size = static_cast< size_t >(rows) * static_cast< size_t >(cols) + 2;
  if (parsed_elements.size() != expected_size)
  {
    std::cerr << "Error: Matrix size and elements error" << std::endl;
    return 2;
  }
  int result = 0;
  if (mode == 1)
  {
    const int max_element = 10000;
    if (rows * cols > max_element)
    {
      std::cerr << "Error: Exceeding the 10000 elements limit matrix" << std::endl;
      return 2;
    }
    int static_matrix[max_element];
    for (int i = 0; i < rows * cols; ++i)
    {
      static_matrix[i] = parsed_elements[i + 2];
    }
    result = zabrodotsy::processMatrix(static_matrix, rows, cols);
  }
  else
  {
    int* const dynamic_matrix = new int[rows * cols];
    for (int i = 0; i < rows * cols; ++i)
    {
      dynamic_matrix[i] = parsed_elements[i + 2];
    }
    result = zabrodotsy::processMatrix(dynamic_matrix, rows, cols);
    delete[] dynamic_matrix;
  }
  std::ofstream out_file(output_param);
  if (!out_file.is_open())
  {
    std::cerr << "Error: Can't open output file" << std::endl;
    return 1;
  }
  out_file << result << std::endl;
  out_file.close();
  return 0;
}
