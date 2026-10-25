#include <iostream>
#include <fstream>
namespace romanov 
{
  int matrixLocalMaxCount(int x, int y, int** arr);
  void creatingMatrix(int n, const char* inputFile, const char* outputFile);
}
int main(int arg_count, char* arg_values[])
{
  if (arg_count != 4)
  {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  if ((arg_values[1][0] != '1' && arg_values[1][0] != '2') || arg_values[1][1] != '\0')
  {
    std::cerr << "First parameter is not a number or number out of range\n";
    return 1;
  }
  int n = 0;
  if (arg_values[1][0] == '1')
  {
    n = 1;
  }
  else if (arg_values[1][0] == '2')
  {
    n = 2;
  }
  try
  {
  romanov::creatingMatrix(n, arg_values[2], arg_values[3]);
  }
  catch (std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
int romanov::matrixLocalMaxCount(int x, int y, int** arr)
{
  if (x < 3 || y < 3)
  {
    return 0;
  }
  int local_max_count = 0;
  for (int i = 1; i < x - 1; ++i)
  {
    for (int j = 1; j < y - 1; ++j)
    {
      bool is_local_max = (
         arr[i][j] > arr[i-1][j-1] &&
         arr[i][j] > arr[i-1][j] &&
         arr[i][j] > arr[i-1][j+1] &&
         arr[i][j] > arr[i][j-1] &&
         arr[i][j] > arr[i][j+1] &&
         arr[i][j] > arr[i+1][j-1] &&
         arr[i][j] > arr[i + 1][j] &&
         arr[i][j] > arr[i + 1][j + 1]
      );
      if (is_local_max)
      {
        ++local_max_count;
      }
    }
  }
  return local_max_count;
}
void romanov::creatingMatrix(int n, const char* inputFile, const char* outputFile)
{
  std::ifstream input(inputFile);
  int x = 0, y = 0;
  if (!(input >> x >> y) || x < 0 || y < 0)
  {
    throw std::logic_error("Not a matrix");
  }
  std::ofstream output(outputFile);
  int result = 0;
  if (n == 1 && x * y > 10000)
  {
    throw std::logic_error("Matrix too big");
  }
  if (n == 1)
  {
    int stack[10000];
    int* stack_matrix[10000];
    for (int i = 0; i < x; ++i)
    {
      stack_matrix[i] = &stack[i * y];
    }
    for (int i = 0; i < x; ++i)
    {
      for (int j = 0; j < y; ++j)
      {
        if (!(input >> stack_matrix[i][j]))
        {
           throw std::logic_error("Wrong matrix format");
        }
      }
    }
    result = matrixLocalMaxCount(x, y, stack_matrix);
  }
  else if (n == 2)
  {
    int** matrix = new int*[x];
    for (int i = 0; i < x; ++i)
    {
      matrix[i] = new int[y];
    }
    for (int i = 0; i < x; ++i)
    {
      for (int j = 0; j < y; ++j)
        if (!(input >> matrix[i][j]))
        {
          for (int k = 0; k < i; ++k)
          {
            delete[] matrix[k];
          }
          delete[] matrix;
          throw std::logic_error("Wrong matrix format");
        }
    }
    result = matrixLocalMaxCount(x, y, matrix);
    for (int i = 0; i < x; ++i)
    {
      delete matrix[i];
    }
    delete[] matrix;
  }
  output << result;
}

