#include <cstddef>
#include <iostream>
#include <limits>
#include "matrix_ops.h"

using std::size_t;

// вариант 19

bool read_int(int& x) {
    if (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    int** m = nullptr;
    size_t rows = 0;
    size_t cols = 0;
    bool running = true;

    while (running) {
        std::cout << "1. Create matrix" << std::endl;
        std::cout << "2. Fill with value" << std::endl;
        std::cout << "3. Print" << std::endl;
        std::cout << "4. Spiral read" << std::endl;
        std::cout << "0. Exit" << std::endl;

        int choice = 0;
        if (!read_int(choice)) {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }

        switch (choice) {
            case 1: {
                int r = 0;
                int c = 0;
                std::cout << "Rows: ";
                if (!read_int(r) || r <= 0) {
                    std::cout << "Invalid arguments!" << std::endl;
                    break;
                }
                std::cout << "Cols: ";
                if (!read_int(c) || c <= 0) {
                    std::cout << "Invalid arguments!" << std::endl;
                    break;
                }
                matrix_delete(m, rows);
                m = nullptr;
                rows = static_cast<size_t>(r);
                cols = static_cast<size_t>(c);
                m = matrix_create(rows, cols);
                break;
            }
            case 2: {
                if (m == nullptr) {
                    std::cout << "Create matrix first!" << std::endl;
                    break;
                }
                int value = 0;
                std::cout << "Value: ";
                if (!read_int(value)) {
                    std::cout << "Invalid input!" << std::endl;
                    break;
                }
                matrix_fill(m, rows, cols, value);
                break;
            }
            case 3: {
                matrix_print(m, rows, cols);
                break;
            }
            case 4: {
                if (m == nullptr) {
                    std::cout << "Create matrix first!" << std::endl;
                    break;
                }
                size_t n = 0;
                int* result = matrix_spiral_read(m, rows, cols, n);
                if (result == nullptr) {
                    std::cout << "NONE" << std::endl;
                    break;
                }
                for (size_t i = 0; i < n; i++) {
                    if (i > 0) {
                        std::cout << " ";
                    }
                    std::cout << result[i];
                }
                std::cout << std::endl;
                delete[] result;
                result = nullptr;
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default: {
                std::cout << "Unknown option!" << std::endl;
                break;
            }
        }
    }

    matrix_delete(m, rows);
    m = nullptr;
    return 0;
}