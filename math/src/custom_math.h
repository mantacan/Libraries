#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#define CUSTOM_E 2.7182818284590452354
#define CUSTOM_PI 3.14159265358979323846
#define CUSTOM_PI_2 1.57079632679489661923
#define CUSTOM_PI_4 0.78539816339744830962
#define CUSTOM_NAN 0.0 / 0.0
#define CUSTOM_POS_INF 1.0 / 0.0
#define CUSTOM_NEG_INF -1.0 / 0.0
#define CUSTOM_DBL_MAX 1.79769e+308
#define CUSTOM_EPS 1e-16L
#define CUSTOM_EPS_TAN 1e-6
#define CUSTOM_TEST_EPS 1e-6

long double factorial(int n);
long double custom_sin(long double x);
long double custom_cos(long double x);
long double custom_tan(long double x);
long double custom_asin(long double x);
long double custom_acos(long double x);
long double custom_atan(long double x);
long double custom_exp(double x);
long double custom_log(double x);
long double custom_pow(double base, double exp);
long double custom_sqrt(double x);
long double custom_fmod(double x, double y);
long double custom_floor(double x);
long double custom_ceil(double x);
long double custom_fabs(double x);
int custom_abs(int x);

int custom_isnan(double x);
int custom_isint(double x);
int custom_iseven(double x);
int custom_isodd(double x);

#endif