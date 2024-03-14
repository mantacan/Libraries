#include <check.h>

#include "custom_matrix.h"

START_TEST(test_custom_create_matrix) {
  matrix_t mat;
  int result = custom_create_matrix(3, 4, &mat);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);

  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_ne(mat.matrix[i], NULL);
  }

  custom_remove_matrix(&mat);
}
END_TEST

START_TEST(test_custom_remove_matrix) {
  matrix_t mat;
  int result = custom_create_matrix(2, 2, &mat);

  ck_assert_int_eq(result, OK);

  custom_remove_matrix(&mat);

  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_custom_eq_matrix) {
  matrix_t mat1, mat2;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &mat2);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);

  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 2;
  mat1.matrix[1][0] = 3;
  mat1.matrix[1][1] = 4;

  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 2;
  mat2.matrix[1][0] = 3;
  mat2.matrix[1][1] = 4;

  int result = custom_eq_matrix(&mat1, &mat2);

  ck_assert_int_eq(result, 1);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&mat2);
}
END_TEST

START_TEST(test_custom_sum_matrix) {
  matrix_t mat1, mat2, result;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &mat2);
  int result3 = custom_create_matrix(2, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);
  ck_assert_int_eq(result3, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = 4.0;

  mat2.matrix[0][0] = 5.0;
  mat2.matrix[0][1] = 6.0;
  mat2.matrix[1][0] = 7.0;
  mat2.matrix[1][1] = 8.0;

  int result4 = custom_sum_matrix(&mat1, &mat2, &result);

  ck_assert_int_eq(result4, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 12.0, 1e-7);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&mat2);
  custom_remove_matrix(&result);
}
END_TEST

START_TEST(test_custom_sub_matrix) {
  matrix_t mat1, mat2, result;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &mat2);
  int result3 = custom_create_matrix(2, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);
  ck_assert_int_eq(result3, OK);

  mat1.matrix[0][0] = 5.0;
  mat1.matrix[0][1] = 6.0;
  mat1.matrix[1][0] = 7.0;
  mat1.matrix[1][1] = 8.0;

  mat2.matrix[0][0] = 1.0;
  mat2.matrix[0][1] = 2.0;
  mat2.matrix[1][0] = 3.0;
  mat2.matrix[1][1] = 4.0;

  int result4 = custom_sub_matrix(&mat1, &mat2, &result);

  ck_assert_int_eq(result4, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-7);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&mat2);
  custom_remove_matrix(&result);
}
END_TEST

START_TEST(test_custom_mult_number) {
  matrix_t mat1, result;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = 4.0;

  int result3 = custom_mult_number(&mat1, 2.0, &result);

  ck_assert_int_eq(result3, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 8.0, 1e-7);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&result);
}
END_TEST

START_TEST(test_custom_mult_matrix) {
  matrix_t mat1, mat2, result;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &mat2);
  int result3 = custom_create_matrix(2, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);
  ck_assert_int_eq(result3, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = 4.0;

  mat2.matrix[0][0] = 5.0;
  mat2.matrix[0][1] = 6.0;
  mat2.matrix[1][0] = 7.0;
  mat2.matrix[1][1] = 8.0;

  int result4 = custom_mult_matrix(&mat1, &mat2, &result);

  ck_assert_int_eq(result4, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 19.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 22.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 43.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 50.0, 1e-7);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&mat2);
  custom_remove_matrix(&result);
}
END_TEST

START_TEST(test_custom_transpose) {
  matrix_t mat1, result;

  int result1 = custom_create_matrix(2, 3, &mat1);
  int result2 = custom_create_matrix(3, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[0][2] = 3.0;
  mat1.matrix[1][0] = 4.0;
  mat1.matrix[1][1] = 5.0;
  mat1.matrix[1][2] = 6.0;

  int result3 = custom_transpose(&mat1, &result);

  ck_assert_int_eq(result3, OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, 1e-7);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&result);
}
END_TEST

START_TEST(test_custom_determinant) {
  matrix_t mat1;
  double result;

  int result1 = custom_create_matrix(3, 3, &mat1);

  ck_assert_int_eq(result1, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[0][2] = 3.0;
  mat1.matrix[1][0] = 4.0;
  mat1.matrix[1][1] = 5.0;
  mat1.matrix[1][2] = 6.0;
  mat1.matrix[2][0] = 7.0;
  mat1.matrix[2][1] = 8.0;
  mat1.matrix[2][2] = 9.0;

  int result2 = custom_determinant(&mat1, &result);
  ck_assert_int_eq(result2, OK);

  ck_assert_double_eq_tol(result, 0.0, 1e-7);

  custom_remove_matrix(&mat1);
}
END_TEST

START_TEST(test_custom_inverse_matrix) {
  matrix_t mat1, result;

  int result1 = custom_create_matrix(2, 2, &mat1);
  int result2 = custom_create_matrix(2, 2, &result);

  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);

  mat1.matrix[0][0] = 1.0;
  mat1.matrix[0][1] = 2.0;
  mat1.matrix[1][0] = 3.0;
  mat1.matrix[1][1] = 4.0;

  int result3 = custom_inverse_matrix(&mat1, &result);

  ck_assert_int_eq(result3, OK);

  custom_remove_matrix(&mat1);
  custom_remove_matrix(&result);
}
END_TEST

int main() {
  Suite *s1 = suite_create("MATRIX");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_custom_create_matrix);
  tcase_add_test(tc, test_custom_remove_matrix);
  tcase_add_test(tc, test_custom_eq_matrix);
  tcase_add_test(tc, test_custom_sum_matrix);
  tcase_add_test(tc, test_custom_sub_matrix);
  tcase_add_test(tc, test_custom_mult_number);
  tcase_add_test(tc, test_custom_mult_matrix);
  tcase_add_test(tc, test_custom_transpose);
  tcase_add_test(tc, test_custom_determinant);
  tcase_add_test(tc, test_custom_inverse_matrix);

  suite_add_tcase(s1, tc);

  SRunner *sr = srunner_create(s1);
  srunner_set_fork_status(sr, CK_FORK);
  srunner_set_log(sr, "-");
  srunner_run_all(sr, CK_NORMAL | CK_SILENT);

  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
