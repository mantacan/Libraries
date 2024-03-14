#include "custom_math.h"

#include <stdio.h>

long double custom_exp(double x) {
  long double exp = 0;

  if (custom_isnan(x)) {
    exp = CUSTOM_NAN;
  } else if (x < 0) {
    exp = 1 / custom_exp(-x);
  } else {
    long double term = 1;
    long double sum = 0;
    long double last_sum = 1;
    for (int i = 1; custom_fabs(sum - last_sum) > CUSTOM_EPS && sum <= CUSTOM_DBL_MAX;
         i++) {
      last_sum = sum;
      sum += term;
      term = (term * x / i);
    }
    exp = (sum <= CUSTOM_DBL_MAX ? sum : CUSTOM_POS_INF);
  }

  return exp;
}

long double custom_log(double x) {
  long double log = 0;

  if (custom_isnan(x) || x < 0) {
    log = CUSTOM_NAN;
  } else if (x == 0) {
    log = CUSTOM_NEG_INF;
  } else if (x > CUSTOM_DBL_MAX) {
    log = CUSTOM_POS_INF;
  } else {
    long long approx_log = 0;
    for (; x > 1; approx_log++, x /= CUSTOM_E) {
      ;
    }
    for (; x < 1e-4; approx_log--, x *= CUSTOM_E) {
      ;
    }

    long double term_nominator = -1;
    long double term = 1;
    long double sum = 0;
    long double last_sum = 1;
    for (int i = 1; custom_fabs(sum - last_sum) > CUSTOM_EPS; i++) {
      term_nominator *= (x - 1) * -1;
      term = term_nominator / i;
      last_sum = sum;
      sum += term;
    }

    log = approx_log + sum;
  }

  return log;
}

long double custom_pow(double base, double exp) {
  long double pow = 0;

  if ((base == -1 && (exp == CUSTOM_POS_INF || exp == CUSTOM_NEG_INF)) || base == 1 ||
      exp == 0) {
    pow = 1;
  } else if ((base == +0.0 && exp < 0) ||
             (base == -0.0 && exp < 0 &&
              (custom_iseven(exp) || !custom_isint(exp))) ||
             (custom_fabs(base) < 1 && exp == CUSTOM_NEG_INF) ||
             (custom_fabs(base) > 1 && exp == CUSTOM_POS_INF) ||
             (base == CUSTOM_POS_INF && exp > 0) ||
             (base == CUSTOM_NEG_INF && exp > 0 &&
              (custom_iseven(exp) || !custom_isint(exp)))) {
    pow = CUSTOM_POS_INF;
  } else if ((base == -0.0 && exp < 0 && custom_isodd(exp)) ||
             (base == CUSTOM_NEG_INF && exp > 0 && custom_isodd(exp))) {
    pow = CUSTOM_NEG_INF;
  } else if ((base == +0.0 && exp > 0) ||
             (base == -0.0 && exp > 0 &&
              (custom_iseven(exp) || !custom_isint(exp))) ||
             (custom_fabs(base) < 1 && exp == CUSTOM_POS_INF) ||
             (custom_fabs(base) > 1 && exp == CUSTOM_NEG_INF) ||
             (base == CUSTOM_POS_INF && exp < 0) ||
             (base == CUSTOM_NEG_INF && exp < 0 &&
              (custom_iseven(exp) || !custom_isint(exp)))) {
    pow = +0.0;
  } else if ((base == -0.0 && exp > 0 && custom_isodd(exp)) ||
             (base == CUSTOM_NEG_INF && exp < 0 && custom_isodd(exp))) {
    pow = -0.0;
  } else if ((base < 0 && !custom_isint(exp)) || custom_isnan(base) ||
             custom_isnan(exp)) {
    pow = CUSTOM_NAN;
  } else if (base < 0) {
    if (custom_iseven(exp)) {
      pow = custom_exp(exp * custom_log(-base));
    } else {
      pow = -1 * custom_exp(exp * custom_log(-base));
    }
  } else {
    pow = custom_exp(exp * custom_log(base));
  }

  return pow;
}

long double custom_sqrt(double x) {
  double sqrt = 0;

  if (x < -0.0) {
    sqrt = CUSTOM_NAN;
  } else if (x == -0.0 || x == 0.0 || x == CUSTOM_POS_INF) {
    sqrt = x;
  } else {
    sqrt = custom_pow(x, 0.5);
  }

  return sqrt;
}

long double custom_fmod(double x, double y) {
  long double fmod = 0;

  if (y == 0 || custom_isnan(x) || custom_isnan(y) || x == CUSTOM_POS_INF ||
      x == CUSTOM_NEG_INF) {
    fmod = CUSTOM_NAN;
  } else if (y == CUSTOM_POS_INF || y == CUSTOM_NEG_INF) {
    fmod = x;
  } else {
    long double quot = x / y;
    long double int_quot = (quot > 0 ? custom_floor(quot) : custom_ceil(quot));
    fmod = (x - y * int_quot);

    while ((x < 0 && fmod > 0) || (x > 0 && fmod < 0)) {
      if (int_quot > 0) {
        int_quot -= 1;
      } else {
        int_quot += 1;
      }
      fmod = (x - y * int_quot);
    }
  }

  return fmod;
}

long double custom_floor(double x) {
  long double floor = 0;

  if (x == CUSTOM_POS_INF || x == CUSTOM_NEG_INF || x == CUSTOM_DBL_MAX ||
      custom_isnan(x)) {
    floor = x;
  } else if (x < 0) {
    floor = -1 * custom_ceil(-x);
  } else {
    floor = (long long)x;
  }

  return floor;
}

long double custom_ceil(double x) {
  long double ceil = 0;

  if (x == CUSTOM_POS_INF || x == CUSTOM_NEG_INF || x == CUSTOM_DBL_MAX ||
      custom_isnan(x)) {
    ceil = x;
  } else if (x < 0) {
    ceil = -1 * custom_floor(-x);
  } else {
    long double floor = custom_floor(x);
    ceil = (x == floor ? floor : floor + 1);
  }

  return ceil;
}

long double custom_fabs(double x) { return (x < 0 ? -x : x); }

int custom_abs(int x) { return (x < 0 ? -x : x); }

int custom_isnan(double x) { return (x != x); }

int custom_isint(double x) { return (x == (long long)x); }

int custom_iseven(double x) { return (custom_isint(x) && (long long)x % 2 == 0); }

int custom_isodd(double x) { return (custom_isint(x) && (long long)x % 2 != 0); }

long double factorial(int n) {
  long double fact = 1;
  for (int i = 1; i <= n; i++) {
    fact *= i;
  }
  return fact;
}

long double custom_sin(long double x) {
  long double res = 0, term = 1;
  if (custom_fabs(x) == CUSTOM_POS_INF || custom_isnan(x)) {
    res = CUSTOM_NAN;
  } else {
    x = custom_fmod(x, 2 * CUSTOM_PI);
    if (x < -CUSTOM_PI) {
      x += 2 * CUSTOM_PI;
    } else if (x > CUSTOM_PI) {
      x -= 2 * CUSTOM_PI;
    }
    int i = 0, j = 0;

    if (custom_fabs(x) <= CUSTOM_PI_2) {
      for (i = 1; custom_fabs((double)term) > CUSTOM_EPS; i += 2) {
        term = custom_pow(x, i) / factorial(i);
        if (j % 2 == 0) {
          res += term;
        } else {
          res -= term;
        }
        j++;
      }
    } else if (x > CUSTOM_PI_2) {
      res = custom_cos(x - CUSTOM_PI_2);
    } else {
      res = -1 * custom_cos(x + CUSTOM_PI_2);
    }
  }

  return res;
}

long double custom_cos(long double x) {
  long double res = 1, term = 1;
  if (custom_fabs(x) == CUSTOM_POS_INF || custom_isnan(x)) {
    res = CUSTOM_NAN;
  } else {
    x = custom_fmod(x, 2 * CUSTOM_PI);
    if (x < -CUSTOM_PI) {
      x += 2 * CUSTOM_PI;
    } else if (x > CUSTOM_PI) {
      x -= 2 * CUSTOM_PI;
    }
    int i = 0, j = 0;

    if (custom_fabs(x) <= CUSTOM_PI_2) {
      for (i = 2; custom_fabs((double)term) > CUSTOM_EPS; i += 2) {
        term = custom_pow(x, i) / factorial(i);
        if (j % 2 == 0) {
          res -= term;
        } else {
          res += term;
        }
        j++;
      }
    } else if (x > CUSTOM_PI_2) {
      res = -1 * custom_sin(x - CUSTOM_PI_2);
    } else {
      res = custom_sin(x + CUSTOM_PI_2);
    }
  }
  return res;
}

long double custom_tan(long double x) {
  long double sinx = custom_sin(x);
  long double cosx = custom_cos(x);
  long double res = 0;
  if (custom_fabs(custom_cos(x)) < CUSTOM_EPS && custom_sin(x) > 0)
    res = CUSTOM_POS_INF;
  else if (custom_fabs(custom_cos(x)) < CUSTOM_EPS && custom_sin(x) < 0)
    res = CUSTOM_NEG_INF;
  else {
    res = sinx / cosx;
  }

  return res;
}

long double custom_asin(long double x) {
  long double res = 0;
  if (x < -1 || x > 1) {
    res = CUSTOM_NAN;
  } else {
    res = 2 * custom_atan(x / (1 + custom_sqrt(1 - x * x)));
  }
  return res;
}

long double custom_acos(long double x) {
  long double res = 0;
  if (x < -1 || x > 1) {
    res = CUSTOM_NAN;
  } else {
    res = CUSTOM_PI_2 - custom_asin(x);
  }
  return res;
}

long double custom_atan(long double x) {
  long double res = 0;
  if (custom_isnan(x)) {
    res = CUSTOM_NAN;
  } else if (x < -1) {
    res = -CUSTOM_PI / 2 - custom_atan(1 / x);
  } else if (x > 1) {
    res = CUSTOM_PI / 2 - custom_atan(1 / x);
  } else if (custom_fabs(x - 1) < CUSTOM_EPS_TAN) {
    res = CUSTOM_PI_4;
  } else if (custom_fabs(x + 1) < CUSTOM_EPS_TAN) {
    res = -CUSTOM_PI_4;
  } else {
    if (x > -1 && x < 1) res = 0;
    if (x > 1) res = CUSTOM_PI_2;
    if (x < -1) res = -CUSTOM_PI_2;

    long double term = x;
    int i = 0;

    for (i = 0; custom_fabs((double)term) > CUSTOM_EPS; i++) {
      term = custom_pow(-1, i) * custom_pow(x, 2 * i + 1) / (2 * i + 1);
      res += term;
    }
  }
  return res;
}
