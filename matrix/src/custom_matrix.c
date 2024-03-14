#include "custom_matrix.h"

int custom_create_matrix(int rows, int columns, matrix_t *result) {
  int return_code = OK;

  if (rows <= 0 || columns <= 0 || !result) return_code = ERROR;

  if (return_code == OK) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));

    if (result->matrix) {
      for (int i = 0; i < rows && return_code == OK; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i]) return_code = ERROR;
      }
    } else {
      return_code = ERROR;
    }
  }
  return return_code;
}

void custom_remove_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }

    if (A->matrix) free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}

int custom_eq_matrix(matrix_t *A, matrix_t *B) {
  int return_code = SUCCESS;

  if (!custom_matrix_check(A) || !custom_matrix_check(B)) return_code = FAILURE;

  if (return_code == SUCCESS) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows && return_code == 1; i++) {
        for (int j = 0; j < A->columns && return_code == 1; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON)
            return_code = FAILURE;
        }
      }
    } else {
      return_code = FAILURE;
    }
  }

  return return_code;
}

int custom_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = validate_matrices_for_operation(A, B, result);

  if (return_code == 0) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }

  return return_code;
}

int custom_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = validate_matrices_for_operation(A, B, result);

  if (return_code == 0) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }

  return return_code;
}

int custom_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_code = validate_matrix_for_operation(A, result);

  if (return_code == 0) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }

  return return_code;
}

int custom_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = validate_matrices_for_mult_operation(A, B, result);

  if (return_code == 0) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++) {
        double sum = 0;
        for (int k = 0; k < A->columns; k++)
          sum += A->matrix[i][k] * B->matrix[k][j];
        result->matrix[i][j] = sum;
      }
  }

  return return_code;
}

int custom_transpose(matrix_t *A, matrix_t *result) {
  int num = 0;
  if (A->rows < 1 || A->columns < 1 || A->matrix == NULL) num = 1;
  if (num == 0) {
    custom_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
  }
  return num;
}

int custom_matrix_check(matrix_t *A) {
  int return_code = 1;
  if (!A || A->rows <= 0 || A->columns <= 0) return_code = 0;
  return return_code;
}

int validate_matrices_for_operation(matrix_t *A, matrix_t *B,
                                    matrix_t *result) {
  if (!((A->columns == B->columns) && (A->rows == B->rows))) return 2;
  return validate_matrix_for_operation(A, result);
}

int validate_matrix_for_operation(matrix_t *A, matrix_t *result) {
  if (A->columns < 1 || A->rows < 1 || A->matrix == NULL) return 1;
  custom_create_matrix(A->rows, A->columns, result);
  return 0;
}

int validate_matrices_for_mult_operation(matrix_t *A, matrix_t *B,
                                         matrix_t *result) {
  if (A->columns < 1 || A->rows < 1 || B->columns < 1 || B->rows < 1 ||
      A->matrix == NULL || B->matrix == NULL)
    return 1;

  return A->columns != B->rows
             ? 2
             : validate_matrix_for_mult_operation(A, B, result);
}

int validate_matrix_for_mult_operation(matrix_t *A, matrix_t *B,
                                       matrix_t *result) {
  custom_create_matrix(A->rows, B->columns, result);
  return 0;
}

int custom_determinant(matrix_t *A, double *res) {
  int stat = OK;
  if (res && !incorrect_matrix(A)) {
    if (is_nan_inf(A))
      stat = CALCULATION_ERROR;
    else {
      *res = 0;
      double buf = 0;
      if ((A->rows == A->columns) && (A->rows >= 1)) {
        if (A->rows == 1 && A->columns == 1) {
          *res = A->matrix[0][0];
        } else if (A->rows == 2 && A->columns == 2) {
          custom_determinant2x2(A, res);
        } else {
          for (int i = 0; i < A->columns; i++) {
            matrix_t minor;
            calc_certain_minor(A, &minor, 0, i);
            custom_determinant(&minor, &buf);
            custom_remove_matrix(&minor);
            *res += pow(-1., (double)i) * A->matrix[0][i] * buf;
          }
        }
      } else
        stat = CALCULATION_ERROR;
    }
  } else
    stat = ERROR;
  return stat;
}

void custom_determinant2x2(matrix_t *A, double *res) {
  *res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
}

int calc_certain_minor(matrix_t *A, matrix_t *minor, int ind_i, int ind_j) {
  int stat = custom_create_matrix(A->rows - 1, A->columns - 1, minor);
  if (stat == OK) {
    for (int i = 0, k = 0; i < A->rows; i++) {
      if (i == ind_i) continue;
      for (int j = 0, m = 0; j < A->columns; j++) {
        if (j == ind_j) continue;
        minor->matrix[k][m] = A->matrix[i][j];
        m++;
      }
      k++;
    }
  }
  return stat;
}

int incorrect_matrix(matrix_t *matrix) {
  int stat = OK;
  if (!matrix)
    stat = ERROR;
  else if (matrix->rows < 1 || matrix->columns < 1) {
    stat = ERROR;
  }
  return stat;
}

int is_nan_inf(matrix_t *A) {
  int stat = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        stat = 1;
        break;
      }
      if (stat) break;
    }
  }
  return stat;
}

int custom_inverse_matrix(matrix_t *A, matrix_t *res) {
  int stat = OK;
  int single_matrix = 0;

  if (A->rows <= 0 || A->columns <= 0)
    stat = ERROR;

  else if (A->rows != A->columns)
    stat = CALCULATION_ERROR;

  else if (A->rows == 1 && A->columns == 1) {
    if (A->matrix[0][0] != 0) {
      custom_create_matrix(1, 1, res);
      res->matrix[0][0] = 1 / A->matrix[0][0];
      single_matrix = 1;
    } else
      stat = CALCULATION_ERROR;
  }

  if (stat == OK && !single_matrix) {
    double det = 0;
    custom_determinant(A, &det);
    if (det != 0) {
      matrix_t buf1, buf2;
      custom_calc_complements(A, &buf1);
      custom_transpose(&buf1, &buf2);
      custom_mult_number(&buf2, 1 / det, res);
      custom_remove_matrix(&buf1);
      custom_remove_matrix(&buf2);
    } else
      stat = CALCULATION_ERROR;
  }
  return stat;
}

int custom_calc_complements(matrix_t *A, matrix_t *res) {
  int stat = OK;
  if (res && !incorrect_matrix(A)) {
    if (is_nan_inf(A) || (A->rows != A->columns) || (A->rows < 1) ||
        (A->rows == 1) || (A->columns == 1))
      stat = CALCULATION_ERROR;
    else {
      stat = custom_create_matrix(A->rows, A->columns, res);
      if (stat == OK) {
        matrix_t minor;
        double buf = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            calc_certain_minor(A, &minor, i, j);
            custom_determinant(&minor, &buf);
            res->matrix[i][j] = pow(-1., (double)(i + j)) * buf;
            buf = 0;
            custom_remove_matrix(&minor);
          }
        }
      }
    }
  } else
    stat = ERROR;
  return stat;
}
