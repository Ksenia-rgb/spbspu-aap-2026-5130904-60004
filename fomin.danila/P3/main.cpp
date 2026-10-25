#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <charconv>
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Not enought arguments" << "\n";
        return 1;
    }
    if (argc > 4)
    {
        std::cerr << "Too many arguments";
        return 1;
    }
    std::string arg1 = argv[1];
    int numeric = 0;

    auto [ptr, ec] = std::from_chars(arg1.data(), arg1.data() + arg1.size(), numeric);
    if (ec != std::errc{} || ptr != arg1.data() + arg1.size())
    {
        std::cerr << "First parameter is not integer\n";
        return 1;
    }
    if (numeric != 1 && numeric != 2)
    {
        std::cerr << "First parametr out of range\n";
        return 1;
    }
    std::string input = argv[2];
    std::string output = argv[3];
    std::ifstream in(input);
    if (!in.is_open())
    {
        std::cerr << "Can't open this file, mb it's empty?";
        return 2;
    }
    std::ofstream out(output);
    if (!out.is_open())
    {
        std::cerr << "Error create out file";
        return 2;
    }
    int num;
    int size_x = 0;
    int size_y = 0;
    int k = 0;
    int g = 0;
    int static_massive[10000];
    int *matrix = nullptr;
    try
    {
        if (!(in >> size_y >> size_x) || size_x < 0 || size_y < 0)
        {
            throw std::invalid_argument("Size of matrix not integer which more than zero");
        }
        if (size_x == 0 || size_y == 0)
        {
            std::cout << "0";
            return 0;
        }
        if (numeric == 2)
        {
            matrix = new int[size_x * size_y];
        }
        else
        {
            matrix = static_massive;
        }
        while (in >> num)
        {
            if (k >= size_x * size_y)
            {
                throw std::invalid_argument("Too many arguments");
            }
            matrix[k] = num;
            ++k;
        }
        if (!in.eof())
        {
            throw std::invalid_argument("Writed not int in matrix");
        }
        if (k != size_x * size_y)
        {
            throw std::invalid_argument("Not enought arguments");
        }
    }
    catch (const std::invalid_argument &e)
    {
        if (numeric == 2)
        {
            delete[] matrix;
            matrix = nullptr;
        }
        std::cerr << "Error: " << e.what() << "\n";
        exit(1);
    }
    in.close();
    for (int i = 2; i < size_x - 1; ++i)
    {
        if (matrix[i] == matrix[i + 1])
        {
            ++g;
        }
    }
    for (int i = 1; i < size_y; ++i)
    {
        for (int h = 1; h < size_x - 1; ++h)
        {
            if (matrix[h + size_x * i - 1] == matrix[h + size_x * i])
            {
                ++g;
                h = size_x - 1;
            }
        }
    }
    out << size_y - g << "\n";
    if (numeric == 2)
    {
        delete[] matrix;
        matrix = nullptr;
    }
}
