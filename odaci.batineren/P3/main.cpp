#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <new>

namespace odaci
{
    bool readMatrix(std::ifstream& input, int* matrix, std::size_t total)
    {
        for (std::size_t i = 0; i < total; ++i)
        {
            if (!(input >> matrix[i]))
            {
                std::cerr << "Invalid matrix element\n";
                return false;
            }
        }

        // Only whitespace is allowed after the last element.
        if (!input.eof())
        {
            input >> std::ws;
        }
        if (input.bad() || !input.eof())
        {
            std::cerr << "Unexpected data after matrix\n";
            return false;
        }

        return true;
    }

    bool isLowerTriangular(const int* matrix, std::size_t rows, std::size_t cols)
    {
        const std::size_t squareSize = rows < cols ? rows : cols;
        if (squareSize == 0)
        {
            return false;
        }

        for (std::size_t row = 0; row < squareSize; ++row)
        {
            for (std::size_t col = row + 1; col < squareSize; ++col)
            {
                if (matrix[row * cols + col] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }

    int processMatrix(std::ifstream& input, int* matrix, std::size_t rows,
        std::size_t cols, const char* outputPath)
    {
        if (!readMatrix(input, matrix, rows * cols))
        {
            return 2;
        }

        const bool isLower = isLowerTriangular(matrix, rows, cols);
        input.close();

        std::ofstream output(outputPath);
        if (!output)
        {
            std::cerr << "Cannot open output file\n";
            return 2;
        }

        output << std::boolalpha << isLower << '\n';
        output.close();
        if (!output)
        {
            std::cerr << "Cannot write output file\n";
            return 2;
        }

        return 0;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Invalid number of arguments\n";
        return 1;
    }

    const bool useStack = std::strcmp(argv[1], "1") == 0;
    if (!useStack && std::strcmp(argv[1], "2") != 0)
    {
        std::cerr << "Invalid array type\n";
        return 1;
    }

    std::ifstream input(argv[2]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 2;
    }

    int rows;
    int cols;
    if (!(input >> rows >> cols))
    {
        std::cerr << "Invalid matrix dimensions\n";
        return 2;
    }

    if (rows < 0 || cols < 0)
    {
        std::cerr << "Negative matrix dimensions\n";
        return 2;
    }

    const std::size_t rowCount = static_cast<std::size_t>(rows);
    const std::size_t colCount = static_cast<std::size_t>(cols);
    constexpr std::size_t stackCapacity = 10000;
    const std::size_t maxElements = useStack ? stackCapacity
        : (std::numeric_limits<std::size_t>::max)() / sizeof(int);

    // Check the limit before multiplying, so the element count cannot overflow.
    if (colCount != 0 && rowCount > maxElements / colCount)
    {
        std::cerr << "Matrix is too large\n";
        return 2;
    }

    if (useStack)
    {
        int matrix[stackCapacity];
        return odaci::processMatrix(input, matrix, rowCount, colCount, argv[3]);
    }

    const std::size_t total = rowCount * colCount;
    // unique_ptr releases the heap array automatically when main returns.
    std::unique_ptr<int[]> matrix(new (std::nothrow) int[total]);
    if (!matrix)
    {
        std::cerr << "Memory allocation failed\n";
        return 2;
    }

    return odaci::processMatrix(input, matrix.get(), rowCount, colCount, argv[3]);
}
