#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <limits>

namespace odaci
{
    constexpr int asciiSize = 128;
    constexpr int topCount = 3;

    int mostFrequent(const char* input, std::size_t length, char* output) noexcept
    {
        std::size_t counts[asciiSize] = {};
        for (std::size_t i = 0; i < length; ++i)
        {
            const unsigned char character = static_cast<unsigned char>(input[i]);
            if (character < asciiSize && std::isspace(character) == 0)
            {
                ++counts[character];
            }
        }

        int selected[asciiSize] = {};
        for (int i = 0; i < topCount; ++i)
        {
            int best = 0;
            std::size_t bestCount = 0;
            for (int code = 0; code < asciiSize; ++code)
            {
                if (counts[code] > bestCount)
                {
                    best = code;
                    bestCount = counts[code];
                }
            }
            if (bestCount == 0)
            {
                break;
            }
            selected[best] = 1;
            counts[best] = 0;
        }

        int lengthOut = 0;
        for (int code = 0; code < asciiSize; ++code)
        {
            if (selected[code] != 0)
            {
                output[lengthOut++] = static_cast<char>(code);
            }
        }
        output[lengthOut] = '\0';
        return lengthOut;
    }

    int memoryError(char* input)
    {
        std::free(input);
        std::fputs("Not enough memory\n", stderr);
        return 1;
    }
}

int main()
{
    std::size_t capacity = 64;
    std::size_t length = 0;
    char* input = static_cast<char*>(std::malloc(capacity));
    if (input == nullptr)
    {
        return odaci::memoryError(input);
    }

    int character = std::getchar();
    while (character != EOF && character != '\n')
    {
        if (length == capacity)
        {
            if (capacity > std::numeric_limits<std::size_t>::max() / 2)
            {
                return odaci::memoryError(input);
            }
            capacity *= 2;
            char* grown = static_cast<char*>(std::realloc(input, capacity));
            if (grown == nullptr)
            {
                return odaci::memoryError(input);
            }
            input = grown;
        }
        input[length++] = static_cast<char>(character);
        character = std::getchar();
    }

    if (std::ferror(stdin) != 0)
    {
        std::free(input);
        std::fputs("Could not read input\n", stderr);
        return 1;
    }

    char output[odaci::topCount + 1];
    const int outputLength = odaci::mostFrequent(input, length, output);
    std::free(input);
    std::fwrite(output, 1, static_cast<std::size_t>(outputLength), stdout);
    std::putchar('\n');
    return 0;
}
