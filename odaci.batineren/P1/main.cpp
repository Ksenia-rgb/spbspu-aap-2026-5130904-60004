namespace odaci
{
int countMax(std::istream & in, int & result)
{
  int value = 0;
  int maxValue = 0;
  int count = 0;
  bool hasElements = false;
while (in >> value && value != 0)
{
if (!hasElements || value > maxValue)
{
hasElements = true;
maxValue = value;
count = 1;
}
else if (value == maxValue)
{
++count;
}
}
if (!in)
{
return 1;
}
if (!hasElements)
{
return 2;
}
result = count;
return 0;
}
}
int main()
{
  int result = 0;
int status = odaci::countMax(std::cin, result);
if (status == 1)
{
std::cerr << "Error: not a sequence\n";
return 1;
}
if (status == 2)
{
std::cerr << "Error: no maximum\n";
return 2;
}
std::cout << result << '\n';
return 0;
}
