#include <cstddef>
#include "matrix_ops.h"
#include <algorithm>
#include <iostream>

using std::size_t;

int** matrix_create(const size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return nullptr;
    }
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols]();
    }
    return matrix;
}

void matrix_delete(int** m, const size_t rows) {
    if (m == nullptr) {
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        delete[] m[i];
    }
    delete[] m;
}

void matrix_fill(int** m, size_t rows, size_t cols, int value) {
    if (m == nullptr) {
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m[i][j] = value;
        }
    }
}

void matrix_print(const int* const* m, size_t rows, size_t cols) {
    if (m == nullptr) {
        std:: cout << "NONE" << std:: endl;
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (j > 0) {
                std::cout << " ";
            }
            std:: cout << m[i][j];
        }
        std::cout << std::endl;
    }
}

int *matrix_spiral_read(const int *const *m, size_t rows, size_t cols, size_t &out_size) {
    out_size = 0;
    if (m == nullptr || rows == 0 || cols == 0) {
        return nullptr;
    }
    out_size = rows * cols;
    int* array = new int[out_size];
    size_t k = 0;
    size_t border = std::min((rows + 1) / 2, (cols + 1) / 2);
    for (size_t i = 0; i < border; i++) {
        size_t rows_border = rows - 2 * i;
        size_t cols_border = cols - 2 * i;

        size_t ring;
        if (rows_border == 1) {
            ring = cols_border;
        } else if (cols_border == 1) {
            ring = rows_border;
        } else {
            ring = 2 * (rows_border + cols_border) - 4;
        }

        for (size_t j = 0; j < ring; j++) {
            if (j < cols_border) {
                array[k] = m[i][i + j];
            }
            else if (j < cols_border + rows_border - 1) {
                array[k] = m[i + j - cols_border + 1][i + cols_border - 1];
            }
            else if (j < 2 * cols_border + rows_border - 2) {
                array[k] = m[i + rows_border - 1][i + 2 * cols_border + rows_border - 3 - j];
            }
            else {
                array[k] = m[i + 2 * cols_border + 2 * rows_border - 4 - j][i];
            }
            k++;
        }
    }
    return array;
}