#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

auto printMatrix(const S21Matrix& matrix) {
  int rows = matrix.getRows();
  int cols = matrix.getCols();

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << matrix(i, j) << " ";
    }
    std::cout << std::endl;
  }
  printf("\n");
}

TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix matrix;

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 3);
}

TEST(ConstructorTest, ParameterizedConstructor) {
  S21Matrix matrix(4, 3, 5);

  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getCols(), 3);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(matrix(i, j), 5);
    }
  }
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix1(10, 10, 5);

  S21Matrix matrix2(matrix1);

  ASSERT_EQ(matrix1.getRows(), matrix2.getRows());
  ASSERT_EQ(matrix1.getCols(), matrix2.getCols());
  for (int i = 0; i < matrix1.getRows(); ++i) {
    for (int j = 0; j < matrix1.getCols(); ++j) {
      ASSERT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix1(10, 10, 5);

  S21Matrix matrix2(std::move(matrix1));

  ASSERT_EQ(matrix1.getRows(), 0);
  ASSERT_EQ(matrix1.getCols(), 0);
  ASSERT_EQ(matrix1.getData(), nullptr);

  ASSERT_EQ(matrix2.getRows(), 10);
  ASSERT_EQ(matrix2.getCols(), 10);
  for (int i = 0; i < matrix2.getRows(); ++i) {
    for (int j = 0; j < matrix2.getCols(); ++j) {
      ASSERT_EQ(matrix2(i, j), 5);
    }
  }
}

TEST(EqMatrixTest, Equality) {
  S21Matrix matrix1(4, 4, 5);
  S21Matrix matrix2(4, 4, 5);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));

  matrix2(1, 2) = 3.0f;
  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(SumMatrixTest, Sum) {
  S21Matrix matrix1(4, 4, 5);
  S21Matrix matrix2(4, 4, 59);
  matrix1.SumMatrix(matrix2);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_EQ(matrix1(i, j), 64.0);
    }
  }
}

TEST(SubMatrixTest, Subtraction) {
  S21Matrix matrix1(4, 4, 5);
  S21Matrix matrix2(4, 4, 59);
  matrix1.SubMatrix(matrix2);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_EQ(matrix1(i, j), -54.0);
    }
  }
}

TEST(MulNumberTest, Multiplication) {
  S21Matrix matrix1(4, 4, 5);
  matrix1.MulNumber(5);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_EQ(matrix1(i, j), 25.0);
    }
  }
}

TEST(MulMatrixTest, MatrixMultiplication) {
  S21Matrix matrix1(2, 2, 10);
  S21Matrix matrix2(2, 2, 10);
  matrix1.MulMatrix(matrix2);

  for (int i = 0; i < matrix1.getCols(); ++i) {
    for (int j = 0; j < matrix1.getRows(); ++j) {
      ASSERT_EQ(matrix1(i, j), 200);
    }
  }
}

TEST(TransposeTest, Transposition) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix matrix2 = matrix1.Transpose();

  ASSERT_EQ(matrix2(0, 0), 1.0);
  ASSERT_EQ(matrix2(0, 1), 4.0);
  ASSERT_EQ(matrix2(0, 2), 7.0);
  ASSERT_EQ(matrix2(1, 0), 2.0);
  ASSERT_EQ(matrix2(1, 1), 5.0);
  ASSERT_EQ(matrix2(1, 2), 8.0);
  ASSERT_EQ(matrix2(2, 0), 3.0);
  ASSERT_EQ(matrix2(2, 1), 6.0);
  ASSERT_EQ(matrix2(2, 2), 9.0);
}

TEST(CalcComplementsTest, Calculation) {
  S21Matrix matrix1(2, 2, 10);

  S21Matrix result = matrix1.CalcComplements();

  ASSERT_EQ(result(0, 0), 10.0);
  ASSERT_EQ(result(0, 1), -10.0);
  ASSERT_EQ(result(1, 0), -10.0);
  ASSERT_EQ(result(1, 1), 10.0);
}

TEST(DeterminantTest, Calculation) {
  S21Matrix matrix1(3, 3);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 42.0;
  matrix1(1, 1) = 51.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 75.0;
  matrix1(2, 1) = 84.0;
  matrix1(2, 2) = 92.0;

  double result = matrix1.Determinant();

  ASSERT_EQ(result, -3531.0);
}

TEST(InverseMatrixTest, Inversion) {
  S21Matrix matrix1(3, 3, 5);

  matrix1(0, 0) = 11;
  matrix1(0, 1) = 23;
  matrix1(0, 2) = 35;
  matrix1(1, 0) = 46;
  matrix1(1, 1) = 57;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix result = matrix1.InverseMatrix();

  ASSERT_NEAR(-0.10273972602739727, result(0, 0), 0.0001);
  ASSERT_NEAR(-0.016129, result(0, 1), 0.0001);
  ASSERT_NEAR(0.410296, result(0, 2), 0.0001);
  ASSERT_NEAR(0.0821918, result(1, 0), 0.0001);
  ASSERT_NEAR(0.0322581, result(1, 1), 0.0001);
  ASSERT_NEAR(-0.34114, result(1, 2), 0.0001);
  ASSERT_NEAR(0.00684932, result(2, 0), 0.0001);
  ASSERT_NEAR(-0.016129, result(2, 1), 0.0001);
  ASSERT_NEAR(0.0952276, result(2, 2), 0.0001);
}

TEST(OperatorOverloadingTest, Sum) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 4);
  S21Matrix matrix3 = matrix1 + matrix2;

  ASSERT_EQ(matrix3(0, 0), 9);
  ASSERT_EQ(matrix3(0, 1), 9);
  ASSERT_EQ(matrix3(0, 2), 9);
  ASSERT_EQ(matrix3(1, 0), 9);
  ASSERT_EQ(matrix3(1, 1), 9);
  ASSERT_EQ(matrix3(1, 2), 9);
  ASSERT_EQ(matrix3(2, 0), 9);
  ASSERT_EQ(matrix3(2, 1), 9);
  ASSERT_EQ(matrix3(2, 2), 9);
}

TEST(OperatorOverloadingTest, Sub) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 4);
  S21Matrix matrix3 = matrix1 - matrix2;

  ASSERT_EQ(matrix3(0, 0), 1);
  ASSERT_EQ(matrix3(0, 1), 1);
  ASSERT_EQ(matrix3(0, 2), 1);
  ASSERT_EQ(matrix3(1, 0), 1);
  ASSERT_EQ(matrix3(1, 1), 1);
  ASSERT_EQ(matrix3(1, 2), 1);
  ASSERT_EQ(matrix3(2, 0), 1);
  ASSERT_EQ(matrix3(2, 1), 1);
  ASSERT_EQ(matrix3(2, 2), 1);
}

TEST(OperatorOverloadingTest, MulNum) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix3 = matrix1 * 5;

  ASSERT_EQ(matrix3(0, 0), 25);
  ASSERT_EQ(matrix3(0, 1), 25);
  ASSERT_EQ(matrix3(0, 2), 25);
  ASSERT_EQ(matrix3(1, 0), 25);
  ASSERT_EQ(matrix3(1, 1), 25);
  ASSERT_EQ(matrix3(1, 2), 25);
  ASSERT_EQ(matrix3(2, 0), 25);
  ASSERT_EQ(matrix3(2, 1), 25);
  ASSERT_EQ(matrix3(2, 2), 25);
}

TEST(OperatorOverloadingTest, MulMat) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 4);
  S21Matrix matrix3 = matrix1 * matrix2;

  ASSERT_EQ(matrix3(0, 0), 60);
  ASSERT_EQ(matrix3(0, 1), 60);
  ASSERT_EQ(matrix3(0, 2), 60);
  ASSERT_EQ(matrix3(1, 0), 60);
  ASSERT_EQ(matrix3(1, 1), 60);
  ASSERT_EQ(matrix3(1, 2), 60);
  ASSERT_EQ(matrix3(2, 0), 60);
  ASSERT_EQ(matrix3(2, 1), 60);
  ASSERT_EQ(matrix3(2, 2), 60);
}

TEST(OperatorOverloadingTest, IsEq) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 5);

  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(OperatorOverloadingTest, Equally) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3);

  matrix2 = matrix1;

  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(OperatorOverloadingTest, EquallyAndSum) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 5);

  matrix1 += matrix2;

  ASSERT_EQ(matrix1(0, 0), 10);
  ASSERT_EQ(matrix1(0, 1), 10);
  ASSERT_EQ(matrix1(0, 2), 10);
  ASSERT_EQ(matrix1(1, 0), 10);
  ASSERT_EQ(matrix1(1, 1), 10);
  ASSERT_EQ(matrix1(1, 2), 10);
  ASSERT_EQ(matrix1(2, 0), 10);
  ASSERT_EQ(matrix1(2, 1), 10);
  ASSERT_EQ(matrix1(2, 2), 10);
}

TEST(OperatorOverloadingTest, EquallyAndSub) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 6);

  matrix1 -= matrix2;

  ASSERT_EQ(matrix1(0, 0), -1);
  ASSERT_EQ(matrix1(0, 1), -1);
  ASSERT_EQ(matrix1(0, 2), -1);
  ASSERT_EQ(matrix1(1, 0), -1);
  ASSERT_EQ(matrix1(1, 1), -1);
  ASSERT_EQ(matrix1(1, 2), -1);
  ASSERT_EQ(matrix1(2, 0), -1);
  ASSERT_EQ(matrix1(2, 1), -1);
  ASSERT_EQ(matrix1(2, 2), -1);
}

TEST(OperatorOverloadingTest, EquallyAndMul) {
  S21Matrix matrix1(3, 3, 5);
  S21Matrix matrix2(3, 3, 6);

  matrix1 *= matrix2;

  ASSERT_EQ(matrix1(0, 0), 90);
  ASSERT_EQ(matrix1(0, 1), 90);
  ASSERT_EQ(matrix1(0, 2), 90);
  ASSERT_EQ(matrix1(1, 0), 90);
  ASSERT_EQ(matrix1(1, 1), 90);
  ASSERT_EQ(matrix1(1, 2), 90);
  ASSERT_EQ(matrix1(2, 0), 90);
  ASSERT_EQ(matrix1(2, 1), 90);
  ASSERT_EQ(matrix1(2, 2), 90);
}

TEST(OperatorOverloadingTest, Index) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  double value = matrix(0, 0);
  ASSERT_EQ(value, 1);
}

int main(int argc, char** argv) {
  try {
    ::testing::InitGoogleTest(&argc, argv);

  } catch (const std::exception& e) {
    printf("ERROR\n");
  }

  return RUN_ALL_TESTS();
}
