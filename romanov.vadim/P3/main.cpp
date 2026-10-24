#include <iostream>
#include <fstream>
namespace romanov 
{
  int matrixLocalMaxCount(int x, int y, int** arr);
  void creatingMatrix(int n, const char* inputFile, const char* outputFile)
}
int main() 
{

}
int matrixLocalMaxCount(int x, int y, int** arr)
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

    }
  }
}
void creatingMatrix(int n, const char* inputFile, const char* outputFile)
{
  std::ifstream input(inputFile);
  int x = 0, y = 0;
  if (!(input >> x >> y) || x < 0 || y < 0)
  {
    throw std::logic_error("Not a matrix");
  }
  std::ofstream output(outputFile);
  int result = 0
}
