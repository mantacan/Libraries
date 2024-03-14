#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../custom_math.h"

int fequal(long double x, long double y);

START_TEST(exp_test) {
  double tdata[] = {0.0,
                    1.0,
                    -1.0,
                    1.2,
                    1.5,
                    1.99999999999999999,
                    76,
                    -42,
                    4.00374,
                    87626483658,
                    -123237468.1847,
                    1e1,
                    1e2,
                    1e3,
                    1e10,
                    1e16,
                    1e20,
                    1e100,
                    -1e1,
                    -1e2,
                    -1e3,
                    -1e10,
                    -1e16,
                    -1e100,
                    1e-1,
                    1e-2,
                    1e-3,
                    1e-10,
                    1e-16,
                    1e-100,
                    -1e-1,
                    -1e-2,
                    -1e-3,
                    -1e-10,
                    -1e-16,
                    -1e-100,
                    CUSTOM_DBL_MAX,
                    CUSTOM_POS_INF,
                    CUSTOM_NEG_INF,
                    CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_exp(tdata[i]), exp(tdata[i])));
  }
}
END_TEST

START_TEST(log_test) {
  double tdata[] = {0.0,
                    1.0,
                    -1.0,
                    1.2,
                    1.5,
                    1.99999999999999999,
                    76,
                    -42,
                    4.00374,
                    87626483658,
                    -123237468.1847,
                    1e1,
                    1e2,
                    1e3,
                    1e10,
                    1e16,
                    1e20,
                    1e100,
                    -1e1,
                    -1e2,
                    -1e3,
                    -1e10,
                    -1e16,
                    -1e100,
                    1e-1,
                    1e-2,
                    1e-3,
                    1e-10,
                    1e-16,
                    1e-100,
                    -1e-1,
                    -1e-2,
                    -1e-3,
                    -1e-10,
                    -1e-16,
                    -1e-100,
                    CUSTOM_DBL_MAX,
                    CUSTOM_POS_INF,
                    CUSTOM_NEG_INF,
                    CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_log(tdata[i]), log(tdata[i])));
  }
}
END_TEST

START_TEST(pow_test) {
  double tdata[] = {0.0, -0.0, 1.0,     42,          123,         3.1415,
                    -42, -123, -3.1415, CUSTOM_POS_INF, CUSTOM_NEG_INF, CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    double base = tdata[i];
    for (size_t j = 0; j < sizeof(tdata) / sizeof(*tdata); j++) {
      double exp = tdata[j];
      ck_assert(fequal(custom_pow(base, exp), pow(base, exp)));
    }
  }
}
END_TEST

START_TEST(sqrt_test) {
  double tdata[] = {0.0, -0.0, 1.0,     42,          123,         3.1415,
                    -42, -123, -3.1415, CUSTOM_POS_INF, CUSTOM_NEG_INF, CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_sqrt(tdata[i]), sqrt(tdata[i])));
  }
}
END_TEST

START_TEST(fmod_test) {
  double tdata[] = {
      0.0,   1.0,   -1.0,    1.2,         1.5,         1.99999999999999999,
      76,    -42,   4.00374, 1e1,         1e2,         1e3,
      -1e1,  -1e2,  -1e3,    1e-1,        1e-2,        1e-3,
      -1e-1, -1e-2, -1e-3,   CUSTOM_POS_INF, CUSTOM_NEG_INF, CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    double x = tdata[i];
    for (size_t j = 0; j < sizeof(tdata) / sizeof(*tdata); j++) {
      double y = tdata[j];
      ck_assert(fequal(custom_fmod(x, y), fmod(x, y)));
    }
  }
}
END_TEST

START_TEST(floor_test) {
  double tdata[] = {0.0,
                    1.0,
                    -1.0,
                    1.2,
                    1.5,
                    1.99999999999999999,
                    76,
                    -42,
                    4.00374,
                    87626483658,
                    -123237468.1847,
                    1e1,
                    1e2,
                    1e3,
                    1e10,
                    1e16,
                    1e20,
                    1e100,
                    -1e1,
                    -1e2,
                    -1e3,
                    -1e10,
                    -1e16,
                    -1e100,
                    1e-1,
                    1e-2,
                    1e-3,
                    1e-10,
                    1e-16,
                    1e-100,
                    -1e-1,
                    -1e-2,
                    -1e-3,
                    -1e-10,
                    -1e-16,
                    -1e-100,
                    CUSTOM_DBL_MAX,
                    CUSTOM_POS_INF,
                    CUSTOM_NEG_INF,
                    CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_floor(tdata[i]), floor(tdata[i])));
  }
}
END_TEST

START_TEST(ceil_test) {
  double tdata[] = {0.0,
                    1.0,
                    -1.0,
                    1.2,
                    1.5,
                    1.99999999999999999,
                    76,
                    -42,
                    4.00374,
                    87626483658,
                    -123237468.1847,
                    1e1,
                    1e2,
                    1e3,
                    1e10,
                    1e16,
                    1e20,
                    1e100,
                    -1e1,
                    -1e2,
                    -1e3,
                    -1e10,
                    -1e16,
                    -1e100,
                    1e-1,
                    1e-2,
                    1e-3,
                    1e-10,
                    1e-16,
                    1e-100,
                    -1e-1,
                    -1e-2,
                    -1e-3,
                    -1e-10,
                    -1e-16,
                    -1e-100,
                    CUSTOM_DBL_MAX,
                    CUSTOM_POS_INF,
                    CUSTOM_NEG_INF,
                    CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_ceil(tdata[i]), ceil(tdata[i])));
  }
}
END_TEST

START_TEST(fabs_test) {
  double tdata[] = {
      0.0,   1.0,   -1.0,    1.2,         1.5,         1.99999999999999999,
      76,    -42,   4.00374, 1e1,         1e2,         1e3,
      -1e1,  -1e2,  -1e3,    1e-1,        1e-2,        1e-3,
      -1e-1, -1e-2, -1e-3,   CUSTOM_POS_INF, CUSTOM_NEG_INF, CUSTOM_NAN};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert(fequal(custom_fabs(tdata[i]), fabs(tdata[i])));
  }
}
END_TEST

START_TEST(abs_test) {
  int tdata[] = {0, 1, -1, 42, 100500};
  for (size_t i = 0; i < sizeof(tdata) / sizeof(*tdata); i++) {
    ck_assert_int_eq(custom_abs(tdata[i]), abs(tdata[i]));
  }
}
END_TEST

START_TEST(acos_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert(fequal(custom_acos(i), acos(i)));
  }
}
END_TEST

START_TEST(asin_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert(fequal(custom_asin(i), asin(i)));
  }
}
END_TEST

START_TEST(atan_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert_ldouble_eq_tol(custom_atan(i), atan(i), CUSTOM_TEST_EPS);
  }
}
END_TEST

START_TEST(cos_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert_ldouble_eq_tol(custom_cos(i), cos(i), CUSTOM_TEST_EPS);
  }
}
END_TEST

START_TEST(sin_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert_ldouble_eq_tol(custom_sin(i), sin(i), CUSTOM_TEST_EPS);
  }
}
END_TEST

START_TEST(tan_test) {
  for (double i = -10; i < 10; i += 0.1) {
    ck_assert_ldouble_eq_tol(custom_tan(i), tan(i), CUSTOM_TEST_EPS);
  }
}
END_TEST

int main() {
  TCase *tc_exp = tcase_create("custom_exp");
  tcase_add_test(tc_exp, exp_test);
  TCase *tc_log = tcase_create("custom_log");
  tcase_add_test(tc_log, log_test);
  TCase *tc_pow = tcase_create("custom_pow");
  tcase_add_test(tc_pow, pow_test);
  TCase *tc_sqrt = tcase_create("custom_sqrt");
  tcase_add_test(tc_sqrt, sqrt_test);
  TCase *tc_fmod = tcase_create("custom_fmod");
  tcase_add_test(tc_fmod, fmod_test);
  TCase *tc_floor = tcase_create("custom_floor");
  tcase_add_test(tc_floor, floor_test);
  TCase *tc_ceil = tcase_create("custom_ceil");
  tcase_add_test(tc_ceil, ceil_test);
  TCase *tc_fabs = tcase_create("custom_fabs");
  tcase_add_test(tc_fabs, fabs_test);
  TCase *tc_abs = tcase_create("custom_abs");
  tcase_add_test(tc_abs, abs_test);
  TCase *tc_acos = tcase_create("custom_acos");
  tcase_add_test(tc_acos, acos_test);
  TCase *tc_asin = tcase_create("custom_asin");
  tcase_add_test(tc_asin, asin_test);
  TCase *tc_atan = tcase_create("custom_atan");
  tcase_add_test(tc_atan, atan_test);
  TCase *tc_cos = tcase_create("custom_cos");
  tcase_add_test(tc_cos, cos_test);
  TCase *tc_sin = tcase_create("custom_sin");
  tcase_add_test(tc_sin, sin_test);
  TCase *tc_tan = tcase_create("custom_tan");
  tcase_add_test(tc_tan, tan_test);

  Suite *suite = suite_create("custom_math");
  suite_add_tcase(suite, tc_exp);
  suite_add_tcase(suite, tc_log);
  suite_add_tcase(suite, tc_pow);
  suite_add_tcase(suite, tc_sqrt);
  suite_add_tcase(suite, tc_fmod);
  suite_add_tcase(suite, tc_floor);
  suite_add_tcase(suite, tc_ceil);
  suite_add_tcase(suite, tc_fabs);
  suite_add_tcase(suite, tc_abs);
  suite_add_tcase(suite, tc_acos);
  suite_add_tcase(suite, tc_asin);
  suite_add_tcase(suite, tc_atan);
  suite_add_tcase(suite, tc_cos);
  suite_add_tcase(suite, tc_sin);
  suite_add_tcase(suite, tc_tan);

  SRunner *srunner = srunner_create(suite);
  srunner_run_all(srunner, CK_ENV);
  int nf = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  exit(nf ? EXIT_FAILURE : EXIT_SUCCESS);
}

int fequal(long double x, long double y) {
  ;
  return (fabsl(x - y) <
          CUSTOM_TEST_EPS)
         ||
         (fabsl(x) > 1e16 &&
          fabsl(y) >
              1e16)
         || (x == CUSTOM_POS_INF && y == CUSTOM_POS_INF) ||
         (x == CUSTOM_NEG_INF && y == CUSTOM_NEG_INF) || (isnan(x) && isnan(y));
}