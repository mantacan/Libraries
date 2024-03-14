#ifndef CUSTOM_MATRIX_LIBRARY
#define CUSTOM_MATRIX_LIBRARY

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1
#define CALCULATION_ERROR 3

#define SUCCESS 1
#define FAILURE 0

#define EPSILON 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int custom_create_matrix(int rows, int columns, matrix_t *result);
void custom_remove_matrix(matrix_t *A);
int custom_eq_matrix(matrix_t *A, matrix_t *B);
int custom_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_mult_number(matrix_t *A, double number, matrix_t *result);
int custom_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int custom_transpose(matrix_t *A, matrix_t *result);
int custom_calc_complements(matrix_t *A, matrix_t *result);
int custom_determinant(matrix_t *A, double *result);
int custom_inverse_matrix(matrix_t *A, matrix_t *result);

matrix_t *custom_create_minor(int excluded_row, int excluded_column, matrix_t *A);
int custom_matrix_check(matrix_t *A);
int validate_inputs(matrix_t *A, matrix_t *result);
int initialize_result_matrix(matrix_t *A, matrix_t *result);
int compute_determinant(matrix_t *minor, double *det);
void cleanup_minor_matrix(matrix_t *minor);
int validate_matrix(matrix_t *A);
matrix_t *initialize_minor_matrix(matrix_t *A);
void fill_minor_matrix(int excluded_row, int excluded_column, matrix_t *A,
                       matrix_t *minor);
int validate_matrices_for_operation(matrix_t *A, matrix_t *B, matrix_t *result);
int validate_matrix_for_operation(matrix_t *A, matrix_t *result);
int validate_matrices_for_mult_operation(matrix_t *A, matrix_t *B,
                                         matrix_t *result);
int validate_matrix_for_mult_operation(matrix_t *A, matrix_t *B,
                                       matrix_t *result);
void custom_determinant2x2(matrix_t *A, double *res);
int calc_certain_minor(matrix_t *A, matrix_t *minor, int ind_i, int ind_j);
int incorrect_matrix(matrix_t *matrix);
int is_nan_inf(matrix_t *A);

#endif
