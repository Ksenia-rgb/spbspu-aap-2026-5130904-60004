#include <iostream>
#include <fstream>
#include <cstdlib>

namespace maldonado {

    long long calculateMinSumSDG(const int* const* matrix, int rows, int cols) {
        bool first = true;
        long long min_sum = 0;

        for (int diff = -(rows - 1); diff < cols; ++diff) {
            long long current_sum = 0;
            bool has_elements = false;

            for (int i = 0; i < rows; ++i) {
                int j = i + diff;
                if (j >= 0 && j < cols) {
                    current_sum += matrix[i][j];
                    has_elements = true;
                }
            }

            if (has_elements) {
                if (first || current_sum < min_sum) {
                    min_sum = current_sum;
                    first = false;
                }
            }
        }
        return min_sum;
    }

    long long calculateMinSumSDGFlat(const int* matrix, int rows, int cols) {
        bool first = true;
        long long min_sum = 0;

        for (int diff = -(rows - 1); diff < cols; ++diff) {
            long long current_sum = 0;
            bool has_elements = false;

            for (int i = 0; i < rows; ++i) {
                int j = i + diff;
                if (j >= 0 && j < cols) {
                    current_sum += matrix[i * cols + j];
                    has_elements = true;
                }
            }

            if (has_elements) {
                if (first || current_sum < min_sum) {
                    min_sum = current_sum;
                    first = false;
                }
            }
        }
        return min_sum;
    }

} // namespace maldonado

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments.\n";
        return 1;
    }

    int mode = 0;
    try {
        std::string arg1(argv[1]);
        if (arg1 != "1" && arg1 != "2") {
            std::cerr << "Error: First parameter must be 1 or 2.\n";
            return 1;
        }
        mode = std::stoi(arg1);
    } catch (...) {
        std::cerr << "Error: First parameter is not a valid number.\n";
        return 1;
    }

    std::ifstream inFile(argv[2]);
    if (!inFile.is_open()) {
        std::cerr << "Error: Cannot open input file.\n";
        return 2;
    }

    int rows = 0;
    int cols = 0;
    if (!(inFile >> rows >> cols) || rows <= 0 || cols <= 0) {
        std::cerr << "Error: Invalid matrix dimensions.\n";
        return 2;
    }

    if (mode == 1 && rows * cols > 10000) {
        std::cerr << "Error: Matrix too large for static allocation.\n";
        return 2;
    }

    long long result = 0;

    if (mode == 1) {
        const int MAX_SIZE = 100; 
        if (rows > MAX_SIZE || cols > MAX_SIZE || rows * cols > 10000) {
            int static_matrix[10000];
            for (int i = 0; i < rows * cols; ++i) {
                if (!(inFile >> static_matrix[i])) {
                    std::cerr << "Error: Failed to read matrix elements.\n";
                    return 2;
                }
            }
            int dummy;
            if (inFile >> dummy) {
                std::cerr << "Error: Extra data in input file.\n";
                return 2;
            }
            result = maldonado::calculateMinSumSDGFlat(static_matrix, rows, cols);
        } else {
            int static_matrix[MAX_SIZE][MAX_SIZE];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (!(inFile >> static_matrix[i][j])) {
                        std::cerr << "Error: Failed to read matrix elements.\n";
                        return 2;
                    }
                }
            }
            int dummy;
            if (inFile >> dummy) {
                std::cerr << "Error: Extra data in input file.\n";
                return 2;
            }
            const int* ptrs[MAX_SIZE];
            for(int i=0; i<rows; ++i) ptrs[i] = static_matrix[i];
            result = maldonado::calculateMinSumSDG(ptrs, rows, cols);
        }
    } else {
        int* flat_matrix = nullptr;
        int** dyn_matrix = nullptr;
        try {
            flat_matrix = new int[rows * cols];
            dyn_matrix = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                dyn_matrix[i] = flat_matrix + (i * cols);
            }

            for (int i = 0; i < rows * cols; ++i) {
                if (!(inFile >> flat_matrix[i])) {
                    delete[] flat_matrix;
                    delete[] dyn_matrix;
                    std::cerr << "Error: Failed to read matrix elements.\n";
                    return 2;
                }
            }

            int dummy;
            if (inFile >> dummy) {
                delete[] flat_matrix;
                delete[] dyn_matrix;
                std::cerr << "Error: Extra data in input file.\n";
                return 2;
            }

            result = maldonado::calculateMinSumSDG(const_cast<const int* const*>(dyn_matrix), rows, cols);

            delete[] flat_matrix;
            delete[] dyn_matrix;
        } catch (...) {
            delete[] flat_matrix;
            delete[] dyn_matrix;
            std::cerr << "Error: Memory allocation failed.\n";
            return 2;
        }
    }

    inFile.close();

    std::ofstream outFile(argv[3]);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open output file.\n";
        return 2;
    }

    outFile << result << "\n";
    outFile.close();

    return 0;
}
