#include <iostream>
namespace kibirev
{
  int PifTrip();
}

int main()
{
  try
  {
    return kibirev::PifTrip();
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
namespace kibirev
{
  int PifTrip()
  {
    int num = 0;
    int piftr = 0;
    int cntr = 0;
    bool bad = false;
    long long sum = 0;
    if(!(std::cin >> num))
    {
      throw std::invalid_argument("Not a number of int\n");
    }
    while(num != 0)
    {
      if(cntr < 2)
      {
        if(num > 0)
        {
          long long n = num;
          sum += n*n;
        }
        else
        {
          bad = true;
        }
        cntr++;
      }
      else
      {
        if(!bad && num > 0 && sum == num*num)
        {
          piftr++;
        }
        cntr = 0;
        sum = 0;
        bad = false;
      }
      if(!(std::cin >> num))
      {
        throw std::invalid_argument("Not a number of int\n");
      }
    }
    std::cout << piftr << "\n";
    return 0;
  }
}
   
