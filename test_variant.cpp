#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "matrix_ops.h"

using std::size_t;

static void fill_seq(int** m, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m[i][j] = static_cast<int>(i * cols + j + 1);
        }
    }
}

static void expect_spiral(size_t rows, size_t cols, const int* expected, size_t n) {
    int** m = matrix_create(rows, cols);
    ASSERT_NE(m, nullptr);
    fill_seq(m, rows, cols);

    size_t out_size = 999;
    int* result = matrix_spiral_read(m, rows, cols, out_size);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(out_size, n);
    for (size_t k = 0; k < n; k++) {
        EXPECT_EQ(result[k], expected[k]) << "k = " << k;
    }

    delete[] result;
    matrix_delete(m, rows);
}

TEST(MatrixCreate, NotNullAndZeroed) {
    int** m = matrix_create(2, 3);
    ASSERT_NE(m, nullptr);
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(m[i][j], 0);
        }
    }
    matrix_delete(m, 2);
}

TEST(MatrixCreate, ZeroRowsReturnsNull) {
    EXPECT_EQ(matrix_create(0, 3), nullptr);
}

TEST(MatrixCreate, ZeroColsReturnsNull) {
    EXPECT_EQ(matrix_create(3, 0), nullptr);
}

TEST(MatrixDelete, NullptrIsSafe) {
    matrix_delete(nullptr, 5);
    SUCCEED();
}

TEST(MatrixFill, FillsAllCells) {
    int** m = matrix_create(3, 4);
    ASSERT_NE(m, nullptr);
    matrix_fill(m, 3, 4, 7);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            EXPECT_EQ(m[i][j], 7);
        }
    }
    matrix_delete(m, 3);
}

TEST(MatrixFill, NullptrIsSafe) {
    matrix_fill(nullptr, 3, 4, 7);
    SUCCEED();
}

TEST(MatrixPrint, NullptrPrintsNone) {
    testing::internal::CaptureStdout();
    matrix_print(nullptr, 0, 0);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, "NONE\n");
}

TEST(MatrixSpiral, Square3x3) {
    const int expected[] = {1, 2, 3, 6, 9, 8, 7, 4, 5};
    expect_spiral(3, 3, expected, 9);
}

TEST(MatrixSpiral, Wide3x4) {
    const int expected[] = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
    expect_spiral(3, 4, expected, 12);
}

TEST(MatrixSpiral, Tall4x3) {
    const int expected[] = {1, 2, 3, 6, 9, 12, 11, 10, 7, 4, 5, 8};
    expect_spiral(4, 3, expected, 12);
}

TEST(MatrixSpiral, SingleRow1x3) {
    const int expected[] = {1, 2, 3};
    expect_spiral(1, 3, expected, 3);
}

TEST(MatrixSpiral, SingleColumn3x1) {
    const int expected[] = {1, 2, 3};
    expect_spiral(3, 1, expected, 3);
}

TEST(MatrixSpiral, SingleCell1x1) {
    const int expected[] = {1};
    expect_spiral(1, 1, expected, 1);
}

TEST(MatrixSpiral, NullptrMatrix) {
    size_t out_size = 999;
    int* result = matrix_spiral_read(nullptr, 3, 3, out_size);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(out_size, 0u);
}

TEST(MatrixSpiral, ZeroRows) {
    int** m = matrix_create(2, 2);
    ASSERT_NE(m, nullptr);
    size_t out_size = 999;
    int* result = matrix_spiral_read(m, 0, 2, out_size);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(out_size, 0u);
    matrix_delete(m, 2);
}

TEST(MatrixWrite, WritesValue) {
    int** m = matrix_create(2, 3);
    ASSERT_NE(m, nullptr);
    EXPECT_TRUE(matrix_write(m, 2, 3, 1, 2, 42));
    EXPECT_EQ(m[1][2], 42);
    matrix_delete(m, 2);
}

TEST(MatrixWrite, OutOfRangeRejected) {
    int** m = matrix_create(2, 3);
    ASSERT_NE(m, nullptr);
    EXPECT_FALSE(matrix_write(m, 2, 3, 2, 0, 1));
    EXPECT_FALSE(matrix_write(m, 2, 3, 0, 3, 1));
    matrix_delete(m, 2);
}

TEST(MatrixWrite, NullptrIsSafe) {
    EXPECT_FALSE(matrix_write(nullptr, 2, 3, 0, 0, 1));
}