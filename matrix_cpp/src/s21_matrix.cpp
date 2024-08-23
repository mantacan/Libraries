#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (_rows != other.getRows() || _cols != other.getCols()) {
    throw std::runtime_error("Something went wrong!");
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (fabs(_p[i][j] - other(i, j)) > EPSILON) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (_rows != other.getRows() || _cols != other.getCols()) {
    throw std::runtime_error("Something went wrong!");
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _p[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (_rows != other.getRows() || _cols != other.getCols()) {
    throw std::runtime_error("Something went wrong!");
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _p[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _p[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (_cols != other.getRows()) {
    throw std::runtime_error("Something went wrong!");
  }

  S21Matrix result(_rows, other.getCols());

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other.getCols(); j++) {
      double sum = 0;
      for (int k = 0; k < _cols; k++) {
        sum += _p[i][k] * other(k, j);
      }
      result(i, j) = sum;
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(_cols, _rows);

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result(j, i) = _p[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (_rows != _cols || _rows < 1 || _rows == 1 || _cols == 1) {
    throw std::runtime_error("Something went wrong!");
  }

  S21Matrix result(_rows, _cols);

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      S21Matrix minor = this->Minor(i, j);

      double determinant = minor.Determinant();

      result(i, j) = pow(-1, i + j) * determinant;
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  if (_rows != _cols || _rows < 1) {
    throw std::runtime_error("Something went wrong!");
  }

  if (_rows == 1 && _cols == 1) {
    return _p[0][0];
  }

  if (_rows == 2 && _cols == 2) {
    return _p[0][0] * _p[1][1] - _p[0][1] * _p[1][0];
  }

  double determinant = 0;

  for (int i = 0; i < _cols; i++) {
    S21Matrix minor = this->Minor(0, i);

    determinant += pow(-1, i) * _p[0][i] * minor.Determinant();
  }

  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (_rows != _cols || _rows <= 0) {
    throw std::runtime_error("Something went wrong!");
  }

  if (_rows == 1 && _cols == 1) {
    if (_p[0][0] != 0) {
      return S21Matrix(1, 1, 1 / _p[0][0]);
    } else {
      throw std::runtime_error("Something went wrong!");
    }
  }

  double determinant = Determinant();

  if (determinant != 0) {
    S21Matrix com = this->CalcComplements();
    S21Matrix comTranspose = com.Transpose();

    comTranspose.MulNumber(1 / determinant);

    return comTranspose;
  } else {
    throw std::runtime_error("Something went wrong!");
  }
}

S21Matrix S21Matrix::Minor(int ind_i, int ind_j) const {
  int minorRows = _rows - 1;
  int minorCols = _cols - 1;
  S21Matrix minor(minorRows, minorCols);

  for (int i = 0, k = 0; i < _rows; ++i) {
    if (i == ind_i) continue;
    for (int j = 0, m = 0; j < _cols; ++j) {
      if (j == ind_j) continue;
      minor(k, m) = _p[i][j];
      ++m;
    }
    ++k;
  }

  return minor;
}
