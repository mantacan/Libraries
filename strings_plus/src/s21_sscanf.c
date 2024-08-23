#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int result = 0;

  va_list v_args;
  va_start(v_args, format);

  buffer(result, str, format, v_args);

  va_end(v_args);

  return result;
}

void buffer(int result, const char *str, const char *format, va_list v_args) {
  char bufferInput[100];
  char bufferFormat[100];
  int bufferFormatIndex = 0;
  int bufferInputIndex = 0;

  while (*str != '\0' || *format != '\0') {
    if (*str != ' ' && *str != '\0') {
      bufferInput[bufferInputIndex++] = *str;
    } else {
      bufferInput[bufferInputIndex] = '\0';

      if (*format == '%') {
        format++;

        while (*format != ' ' && *format != '\0') {
          bufferFormat[bufferFormatIndex++] = *format;
          format++;
        }
        bufferFormat[bufferFormatIndex] = '\0';

        valid(result, bufferFormat, bufferInput, v_args);

        if (*format != '\0') {
          format++;
        }

        bufferInputIndex = 0;
        bufferFormatIndex = 0;
      } else {
        bufferFormat[0] = '\0';

        if (*format != '\0') {
          format++;
        }

        bufferInputIndex = 0;
      }
    }

    if (*str != '\0') {
      str++;
    }
  }
}

void valid(int result, char *format, const char *input, va_list v_args) {
  char newFormat[100];
  char *currentNewFormat = newFormat;
  int width = 0;
  int asterisk = 0;

  while (*format != '\0') {
    if (*format == '*') {
      asterisk = 1;
      format++;
    }

    while (*format >= '0' && *format <= '9') {
      width = width * 10 + (*format - '0');
      format++;
    }

    while (*format != '\0' && *format != ' ' && *format != '*') {
      *currentNewFormat = *format;
      currentNewFormat++;
      format++;
    }

    *currentNewFormat = '\0';
  }

  if (asterisk == 1) {
    fake_taxi(newFormat, v_args);
  } else if (width != 0 && asterisk == 0) {
    width_value_assignment(result, newFormat, width, input, v_args);
  } else if (width == 0 && asterisk == 0) {
    value_assignment(result, newFormat, input, v_args);
  }
}
void fake_taxi(const char *format, va_list v_args) {
  if (s21_strcmp(format, "c") == 0) {
    va_arg(v_args, char *);

  } else if (s21_strcmp(format, "d") == 0 || s21_strcmp(format, "i") == 0 ||
             s21_strcmp(format, "u") == 0 || s21_strcmp(format, "o") == 0 ||
             s21_strcmp(format, "x") == 0 || s21_strcmp(format, "X") == 0) {
    va_arg(v_args, int *);

  } else if (s21_strcmp(format, "e") == 0 || s21_strcmp(format, "E") == 0 ||
             s21_strcmp(format, "f") == 0 || s21_strcmp(format, "g") == 0 ||
             s21_strcmp(format, "G") == 0) {
    va_arg(v_args, float *);

  } else if (s21_strcmp(format, "hi") == 0 || s21_strcmp(format, "hd") == 0 ||
             s21_strcmp(format, "ho") == 0 || s21_strcmp(format, "hu") == 0 ||
             s21_strcmp(format, "hx") == 0 || s21_strcmp(format, "hX") == 0) {
    va_arg(v_args, short int *);

  } else if (s21_strcmp(format, "li") == 0 || s21_strcmp(format, "ld") == 0 ||
             s21_strcmp(format, "lo") == 0 || s21_strcmp(format, "lu") == 0 ||
             s21_strcmp(format, "lx") == 0 || s21_strcmp(format, "lX") == 0 ||
             s21_strcmp(format, "lc") == 0 || s21_strcmp(format, "ls") == 0) {
    va_arg(v_args, long int *);

  } else if (s21_strcmp(format, "Le") == 0 || s21_strcmp(format, "LE") == 0 ||
             s21_strcmp(format, "Lf") == 0 || s21_strcmp(format, "Lg") == 0 ||
             s21_strcmp(format, "LG") == 0) {
    va_arg(v_args, long double *);

  } else if (s21_strcmp(format, "s") == 0) {
    va_arg(v_args, char *);

  } else if (s21_strcmp(format, "p") == 0) {
    va_arg(v_args, void **);

  } else if (format != NULL && s21_strcmp(format, "n") == 0) {
    va_arg(v_args, int *);

  } else {
  }
}

void width_value_assignment(int result, const char *format, int width,
                            const char *input, va_list v_args) {
  int flag = 0;
  if (format == NULL || input == NULL) {
    flag = 1;
  }
  if (flag == 0) {
    char bufferA[256];

    for (int i = 0; i < width && input[i] != '\0'; i++) {
      bufferA[i] = input[i];
    }

    value_assignment(result, format, bufferA, v_args);
  }
}

int value_assignment(int result, const char *format, const char *input,
                     va_list v_args) {
  int flag = 0;
  if (format == NULL || input == NULL) {
    flag = 1;
  }

  if (flag == 0) {
    if (s21_strcmp(format, "c") == 0) {
      char *a = va_arg(v_args, char *);
      *a = input[0];
      result++;
    } else if (s21_strcmp(format, "d") == 0) {
      int *a = va_arg(v_args, int *);
      *a = atoi(input);
      result++;
    } else if (s21_strcmp(format, "i") == 0) {
      int *a = va_arg(v_args, int *);
      *a = (int)strtol(input, NULL, 16);
      result++;
    } else if (s21_strcmp(format, "e") == 0) {
      float *a = va_arg(v_args, float *);
      *a = strtof(input, NULL);
      result++;
    } else if (s21_strcmp(format, "E") == 0) {
      float *a = va_arg(v_args, float *);
      *a = strtof(input, NULL);
      result++;
    } else if (s21_strcmp(format, "f") == 0) {
      float *a = va_arg(v_args, float *);
      *a = strtof(input, NULL);
      result++;
    } else if (s21_strcmp(format, "g") == 0) {
      float *a = va_arg(v_args, float *);
      *a = strtof(input, NULL);
      result++;
    } else if (s21_strcmp(format, "G") == 0) {
      float *a = va_arg(v_args, float *);
      *a = strtof(input, NULL);
      result++;
    } else if (s21_strcmp(format, "o") == 0) {
      unsigned int *a = va_arg(v_args, unsigned int *);
      *a = strtoul(input, NULL, 8);
      result++;
    } else if (s21_strcmp(format, "s") == 0) {
      char *a = va_arg(v_args, char *);
      s21_strcpy(a, input);
      result++;
    } else if (s21_strcmp(format, "u") == 0) {
      unsigned int *a = va_arg(v_args, unsigned int *);
      *a = atoi(input);
      result++;
    } else if (s21_strcmp(format, "x") == 0) {
      unsigned int *a = va_arg(v_args, unsigned int *);
      *a = (unsigned int)strtol(input, NULL, 16);
      result++;
    } else if (s21_strcmp(format, "X") == 0) {
      unsigned int *a = va_arg(v_args, unsigned int *);
      *a = (unsigned int)strtol(input, NULL, 16);
      result++;
    } else if (s21_strcmp(format, "p") == 0) {
      void **a = va_arg(v_args, void **);
      *a = (void *)strtoul(input, NULL, 16);
      result++;
    } else if (format != NULL && s21_strcmp(format, "n") == 0) {
      int *a = va_arg(v_args, int *);
      *a = result;
    } else if (s21_strcmp(format, "hi") == 0 || s21_strcmp(format, "hd") == 0 ||
               s21_strcmp(format, "ho") == 0 || s21_strcmp(format, "hu") == 0 ||
               s21_strcmp(format, "hx") == 0 || s21_strcmp(format, "hX") == 0) {
      short int *a = va_arg(v_args, short int *);
      *a = atoi(input);
      result++;
    } else if (s21_strcmp(format, "li") == 0 || s21_strcmp(format, "ld") == 0 ||
               s21_strcmp(format, "lo") == 0 || s21_strcmp(format, "lu") == 0 ||
               s21_strcmp(format, "lx") == 0 || s21_strcmp(format, "lX") == 0 ||
               s21_strcmp(format, "lc") == 0 || s21_strcmp(format, "ls") == 0) {
      long int *a = va_arg(v_args, long int *);
      *a = atol(input);
      result++;

    } else if (s21_strcmp(format, "Le") == 0 || s21_strcmp(format, "LE") == 0 ||
               s21_strcmp(format, "Lf") == 0 || s21_strcmp(format, "Lg") == 0 ||
               s21_strcmp(format, "LG") == 0) {
      long double *a = va_arg(v_args, long double *);
      *a = atof(input);
      result++;
    } else {
    }
  }

  return result;
}