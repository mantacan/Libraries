#ifndef S21_MATRIX_LIBRARY
#define S21_MATRIX_LIBRARY

#include <cmath>
#include <cstring>
#include <iostream>

#define OK 0
#define ERROR 1
#define CALCULATION_ERROR 3

#define SUCCESS 1
#define FAILURE 0

#define EPSILON 1e-7

class S21Matrix {
 private:
  int _rows, _cols;
  double** _p;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(int rows, int cols, double initialValue);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int row, int col);
  double& operator()(int row, int col) const;

  void setRows(int rows_args);
  void setCols(int cols_args);
  int getRows() const;
  int getCols() const;
  double** getData() const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix Minor(int ind_i, int ind_j) const;

  void printMatrix(const S21Matrix& matrix);
};

#endif
