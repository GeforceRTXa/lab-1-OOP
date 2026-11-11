#pragma once
#include <cstddef>

int** matrix_create(std::size_t rows, std::size_t cols); // массив указателей на строки

void matrix_delete(int** m, std::size_t rows); // каждая строка, затем массив строк

void matrix_fill(int** m, std::size_t rows, std::size_t cols, int value);

void matrix_print(const int* const* m, std::size_t rows, std::size_t cols);

int* matrix_spiral_read(const int* const*m, std::size_t rows, std::size_t cols, std::size_t &out_size);

bool matrix_write(int** m, std::size_t rows, std::size_t cols, std::size_t row, std::size_t col, int value);