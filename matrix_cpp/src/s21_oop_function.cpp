#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  _rows = 3;
  _cols = 3;

  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols]();
  }
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols]();
  }
}

S21Matrix::S21Matrix(int rows, int cols, double init_value)
    : _rows(rows), _cols(cols) {
  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols];
    for (int j = 0; j < _cols; ++j) {
      _p[i][j] = init_value;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols];
    std::memcpy(_p[i], o._p[i], _cols * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& o) {
  _rows = o._rows;
  _cols = o._cols;

  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols];
    std::memcpy(_p[i], o._p[i], _cols * sizeof(double));
  }

  for (int i = 0; i < o._rows; ++i) {
    delete[] o._p[i];
  }
  delete[] o._p;

  o._rows = 0;
  o._cols = 0;
  o._p = nullptr;
}

S21Matrix::~S21Matrix() {
  if (_p) {
    for (int i = 0; i < _rows; i++) {
      delete[] _p[i];
    }
    delete[] _p;
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this == &o) {
    return *this;
  }
  if (_p) {
    for (int i = 0; i < _rows; ++i) {
      delete[] _p[i];
    }
    delete[] _p;
  }
  _rows = o._rows;
  _cols = o._cols;
  _p = new double*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _p[i] = new double[_cols];
    std::memcpy(_p[i], o._p[i], _cols * sizeof(double));
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= _rows || col >= _cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return _p[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= _rows || col >= _cols) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return _p[row][col];
}

int S21Matrix::getRows() const { return _rows; }

int S21Matrix::getCols() const { return _cols; }

void S21Matrix::setRows(int rows_args) { _rows = rows_args; }

void S21Matrix::setCols(int cols_args) { _cols = cols_args; }

double** S21Matrix::getData() const { return _p; }
