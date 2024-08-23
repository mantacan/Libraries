#include "s21_string.h"

#define SPECIFIERS "cdieEfgGosuxXpn%\0"
#define FLAGS "0# +-\0"
#define ARG_LEN "Lhl"

#define IF_FROM_FIRST_ZERO                                 \
  if (from_first_not_zero) {                               \
    long double tempNum = num;                             \
    while ((int)tempNum == 0) tempNum *= 10, firstIndex++; \
    accuracy += firstIndex;                                \
    if ((long long)num == 0) accuracy--;                   \
    long long tempNum2 = num;                              \
    int lenght = 0;                                        \
    while (tempNum2 != 0) tempNum2 /= 10, lenght++;        \
    accuracy -= lenght;                                    \
  }

#define ADD_SIGN                                                    \
  if (tempArray[0] != '-' && signFlag) {                            \
    for (int i = s21_strlen(tempArray); i > 0; i--)                 \
      tempArray[i] = tempArray[i - 1];                              \
    tempArray[0] = '+';                                             \
  }                                                                 \
  if (spaceFlag && !(tempArray[0] == '-' || tempArray[0] == '+')) { \
    for (int i = s21_strlen(tempArray); i > 0; i--)                 \
      tempArray[i] = tempArray[i - 1];                              \
    tempArray[0] = ' ';                                             \
  }

#define ADD_ACCURACY_TO_NUMBER                                               \
  if (accuracy == -1)                                                        \
    accuracy = 1;                                                            \
  else                                                                       \
    zeroFlag = 0;                                                            \
  int isNegative = tempArray[0] == '-';                                      \
  if ((int)s21_strlen(tempArray) - isNegative < accuracy) {                  \
    for (int i1 = s21_strlen(tempArray) - isNegative; i1 < accuracy; i1++) { \
      for (int j = s21_strlen(tempArray); j > isNegative; j--)               \
        tempArray[j] = tempArray[j - 1];                                     \
      tempArray[isNegative] = '0';                                           \
    }                                                                        \
  }

#define PARSE_FLAGS_ETC                                                        \
  int stopParse = 0;                                                           \
  while (format[i] != '\0' && stopParse == 0) {                                \
    i++;                                                                       \
    int didSomething = 0;                                                      \
    if (parcerPhase == 0 && s21_strchr(FLAGS, format[i])) {                    \
      switch (format[i]) {                                                     \
        case '0':                                                              \
          zeroFlag = 1;                                                        \
          break;                                                               \
        case '#':                                                              \
          modifiedOutput = 1;                                                  \
          break;                                                               \
        case ' ':                                                              \
          spaceFlag = 1;                                                       \
          break;                                                               \
        case '+':                                                              \
          signFlag = 1;                                                        \
          break;                                                               \
        case '-':                                                              \
          leftFlag = 1;                                                        \
          break;                                                               \
        default:                                                               \
          break;                                                               \
      }                                                                        \
      didSomething = 1, error = 0;                                             \
    }                                                                          \
    if (parcerPhase == 1) {                                                    \
      if (format[i] == '*')                                                    \
        didSomething = 1, error = 0, parcerPhase++, width = va_arg(list, int); \
      else if (s21_strchr("0123456789", format[i]) &&                          \
               (format[i] != '0' || phaseLock == 1))                           \
        didSomething = 1, error = 0, phaseLock = 1,                            \
        width = width * 10 + (int)format[i] - (int)'0';                        \
    }                                                                          \
    if (parcerPhase == 2) {                                                    \
      if (format[i] == '.' && !phaseLock)                                      \
        didSomething = 1, phaseLock = 1, accuracy = 0;                         \
      else if (format[i] == '*' && phaseLock)                                  \
        didSomething = 1, parcerPhase++, accuracy = va_arg(list, int);         \
      else if (s21_strchr("0123456789", format[i]) && phaseLock)               \
        didSomething = 1, error = 0,                                           \
        accuracy = accuracy * 10 + format[i] - '0';                            \
    }                                                                          \
    if (s21_strchr(ARG_LEN, format[i]) && parcerPhase == 3)                    \
      arg_len = format[i], didSomething = 1;                                   \
    if (error == 2 || s21_strchr(SPECIFIERS, format[i]) ||                     \
        format[i] == '\0' || parcerPhase == 4) {                               \
      if (!s21_strchr(SPECIFIERS, format[i]) && parcerPhase == 4) error = 2;   \
      stopParse = 1;                                                           \
    }                                                                          \
    if (didSomething == 0 && stopParse == 0)                                   \
      phaseLock = 0, parcerPhase++, i--;                                       \
  }                                                                            \
  if (stopParse == 1)

#define G_TO_STR                                                          \
  tempArray = calloc(100, sizeof(char));                                  \
  if (tempArray != NULL) {                                                \
    long double number;                                                   \
    if (arg_len == 'L')                                                   \
      number = (long double)va_arg(list, long double);                    \
    else                                                                  \
      number = (double)va_arg(list, double);                              \
    if (accuracy == -1) accuracy = 6;                                     \
    modifiedOutput = !modifiedOutput;                                     \
    for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0';                \
    float_to_e(number, tempArray, smol, accuracy - 1, modifiedOutput);    \
    int lenE = s21_strlen(tempArray);                                     \
    for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0';                \
    float_to_string(number, tempArray, 1, accuracy, 0);                   \
    int lenFloat = s21_strlen(tempArray);                                 \
    if (!modifiedOutput) {                                                \
      for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0';              \
      float_to_string(number, tempArray, 1, accuracy, 1);                 \
    }                                                                     \
    int stop = 0;                                                         \
    for (int i1 = 0; i1 < (int)s21_strlen(tempArray) && stop == 0; i1++)  \
      if (!s21_strchr("123456789", tempArray[i1])) {                      \
      } else                                                              \
        stop = 1;                                                         \
    if (lenE < lenFloat) {                                                \
      for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0';              \
      float_to_e(number, tempArray, smol, accuracy - 1, !modifiedOutput); \
    }                                                                     \
    ADD_SIGN                                                              \
  }

#define E_TO_STR                                           \
  tempArray = calloc(250, sizeof(char));                   \
  if (tempArray != NULL) {                                 \
    if (accuracy == -1) accuracy = 6;                      \
    long double num;                                       \
    if (arg_len == 'L')                                    \
      num = (long double)va_arg(list, long double);        \
    else                                                   \
      num = (double)va_arg(list, double);                  \
    for (int i1 = 0; i1 < 250; i1++) tempArray[i1] = '\0'; \
    float_to_e(num, tempArray, smol, accuracy, 0);         \
    ADD_SIGN                                               \
  }

#define D_TO_STR                                           \
  tempArray = calloc(100, sizeof(char));                   \
  if (tempArray != NULL) {                                 \
    long long num;                                         \
    if (arg_len == 'h')                                    \
      num = (short int)va_arg(list, int);                  \
    else if (arg_len == 'l')                               \
      num = (long int)va_arg(list, long int);              \
    else                                                   \
      num = (int)va_arg(list, int);                        \
    for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0'; \
    int_to_string(num, tempArray);                         \
    ADD_ACCURACY_TO_NUMBER                                 \
    ADD_SIGN                                               \
  }

#define O_TO_STR                                                      \
  tempArray = calloc(150, sizeof(char));                              \
  if (tempArray != NULL) {                                            \
    if (accuracy == -1) accuracy = 1;                                 \
    for (int i1 = 0; i1 < 150; i1++) tempArray[i1] = '\0';            \
    unsigned long long num;                                           \
    if (arg_len == 'h')                                               \
      num = (unsigned short int)va_arg(list, unsigned int);           \
    else if (arg_len == 'l')                                          \
      num = (unsigned long int)va_arg(list, unsigned long int);       \
    else                                                              \
      num = (unsigned int)va_arg(list, unsigned int);                 \
    int_to_string(convert_to_oct(num), tempArray);                    \
    if (modifiedOutput && (num != 0))                                 \
      put_char_in_front_of_str(tempArray, '0', s21_strlen(tempArray), \
                               tempArray[0] == '-' ? 1 : 0);          \
    ADD_ACCURACY_TO_NUMBER                                            \
  }

#define X_TO_STR                                                              \
  tempArray = calloc(150, sizeof(char));                                      \
  if (tempArray != NULL) {                                                    \
    if (accuracy == -1) accuracy = 1;                                         \
    for (int i1 = 0; i1 < 150; i1++) tempArray[i1] = '\0';                    \
    unsigned long long num;                                                   \
    if (arg_len == 'h')                                                       \
      num = (unsigned short int)va_arg(list, unsigned int);                   \
    else if (arg_len == 'l')                                                  \
      num = (unsigned long int)va_arg(list, unsigned long int);               \
    else                                                                      \
      num = (unsigned int)va_arg(list, unsigned int);                         \
    convert_to_hex(num, tempArray, smol);                                     \
    ADD_ACCURACY_TO_NUMBER                                                    \
    if (modifiedOutput && (num != 0)) {                                       \
      int index = tempArray[0] == '-';                                        \
      char outputCh = smol ? 'x' : 'X';                                       \
      put_char_in_front_of_str(tempArray, outputCh, s21_strlen(tempArray),    \
                               index);                                        \
      put_char_in_front_of_str(tempArray, '0', s21_strlen(tempArray), index); \
    }                                                                         \
  }

#define P_TO_STR                                                    \
  tempArray = calloc(150, sizeof(char));                            \
  if (tempArray != NULL) {                                          \
    for (int i1 = 0; i1 < 15; i1++) tempArray[i1] = '\0';           \
    convert_to_hex(va_arg(list, unsigned long long), tempArray, 1); \
    put_char_in_front_of_str(tempArray, 'x', 149, 0);               \
    put_char_in_front_of_str(tempArray, '0', 149, 0);               \
    ADD_SIGN                                                        \
  }

#define U_TO_STR                                           \
  tempArray = calloc(150, sizeof(char));                   \
  if (tempArray != NULL) {                                 \
    unsigned long long num;                                \
    if (accuracy == -1) accuracy = 1;                      \
    for (int i1 = 0; i1 < 150; i1++) tempArray[i1] = '\0'; \
    if (arg_len == 'h')                                    \
      num = (unsigned short)va_arg(list, unsigned);        \
    else if (arg_len == 'l')                               \
      num = (unsigned long)va_arg(list, unsigned long);    \
    else                                                   \
      num = (unsigned)va_arg(list, unsigned);              \
    int_to_string(num, tempArray);                         \
    ADD_ACCURACY_TO_NUMBER                                 \
  }

#define F_TO_STR                                                          \
  tempArray = calloc(100, sizeof(char));                                  \
  if (tempArray != NULL) {                                                \
    long double num;                                                      \
    if (leftFlag) zeroFlag = 0;                                           \
    for (int i1 = 0; i1 < 100; i1++) tempArray[i1] = '\0';                \
    if (arg_len == 'L')                                                   \
      num = va_arg(list, long double);                                    \
    else                                                                  \
      num = va_arg(list, double);                                         \
    float_to_string(num, tempArray, 0, accuracy == -1 ? 6 : accuracy, 1); \
    ADD_SIGN                                                              \
  }

#define C_TO_STR                        \
  tempArray = calloc(20, sizeof(char)); \
  if (tempArray != NULL)                \
    tempArray[0] = (char)va_arg(list, int), tempArray[1] = '\0';

#define PERCENT_TO_STR                                            \
  tempArray = calloc(20, sizeof(char));                           \
  if (tempArray != NULL) tempArray[0] = '%', tempArray[1] = '\0'; \
  break;

#define STR_TO_STR                                                  \
  tempArrayStr = va_arg(list, char *);                              \
  tempArray = calloc(s21_strlen(tempArrayStr) + 100, sizeof(char)); \
  if (tempArray != NULL) {                                          \
    for (int i1 = 0; i1 < (int)s21_strlen(tempArrayStr); i1++)      \
      tempArray[i1] = tempArrayStr[i1];                             \
    if (accuracy != -1) tempArray[accuracy] = '\0';                 \
  }

#define N_TO_STR                                           \
  tempArray = calloc(150, sizeof(char));                   \
  if (tempArray != NULL) {                                 \
    for (int i1 = 0; i1 < 150; i1++) tempArray[i1] = '\0'; \
    int_to_string((int)s21_strlen(str), tempArray);        \
    ADD_ACCURACY_TO_NUMBER                                 \
    ADD_SIGN                                               \
  }

#define SPECIFIERS_SWITCH    \
  char *tempArrayStr = NULL; \
  switch (format[i]) {       \
    case 'G':                \
      smol = 0;              \
      G_TO_STR break;        \
    case 'g':                \
      G_TO_STR               \
      break;                 \
    case 'E':                \
      smol = 0;              \
      E_TO_STR break;        \
    case 'e':                \
      E_TO_STR               \
      break;                 \
    case 'd':                \
      D_TO_STR break;        \
    case 'i':                \
      D_TO_STR               \
      break;                 \
    case 'o':                \
      O_TO_STR               \
      break;                 \
    case 'X':                \
      smol = 0;              \
      X_TO_STR break;        \
    case 'x':                \
      X_TO_STR               \
      break;                 \
    case 'p':                \
      P_TO_STR               \
      break;                 \
    case 'u':                \
      U_TO_STR               \
      break;                 \
    case 'f':                \
      F_TO_STR               \
      break;                 \
    case 'c':                \
      C_TO_STR               \
      break;                 \
    case '%':                \
      PERCENT_TO_STR         \
    case 's':                \
      STR_TO_STR             \
      break;                 \
    case 'n':                \
      N_TO_STR               \
      break;                 \
    default:                 \
      break;                 \
  }

int s21_sprintf(char *str, const char *format, ...);
static void int_to_string(long long num, char *result_str);
static void float_to_string(long double num, char *result_str,
                            int from_first_not_zero, int accuracy,
                            int keepZero);
static void float_to_e(long double num, char *result_str, int isSmol,
                       int accuracy, int supressZeros);
static unsigned int convert_to_oct(unsigned int num);
static void convert_to_hex(unsigned long long num, char *result, int isSmol);
static char get_hex(unsigned int num, int smol);
static void put_char_in_front_of_str(char *str, char ch, int len, int start);
static void add_to_str(char *tempArray, int leftFlag, const char *format, int i,
                       int *j, char *str, int width, int zeroFlag, int old_len);
void get_zeros(int accuracy, int *zeros, long double *second);

int s21_sprintf(char *str, const char *format, ...) {
  int i = 0, j = 0;
  va_list list;
  va_start(list, format);
  int error = 0;
  for (; format[i] != 0 && error != 2; i++, j++) {
    str[j] = 0;
    if (format[i] != '%')
      str[j] = format[i];
    else {
      int accuracy = -1, parcerPhase = 0, zeroFlag = 0, modifiedOutput = 0,
          spaceFlag = 0, signFlag = 0, leftFlag = 0, phaseLock = 0, width = 0;
      char arg_len = 0;
      PARSE_FLAGS_ETC
      if (format[i] != '\0' && error != 2) {
        char *tempArray = NULL;
        int old_len = s21_strlen(str), smol = 1;
        SPECIFIERS_SWITCH
        if (tempArray != NULL) {
          add_to_str(tempArray, leftFlag, format, i, &j, str, width, zeroFlag,
                     old_len);
          free(tempArray);
        }
      }
    }
  }
  va_end(list);
  str[j] = 0;
  return 1;
}

static void add_to_str(char *tempArray, int leftFlag, const char *format, int i,
                       int *j, char *str, int width, int zeroFlag,
                       int old_len) {
  int len = s21_strlen(tempArray);
  if (!leftFlag && (format[i] != '%' || OS)) {
    char temptemp[3] = "";
    temptemp[0] = tempArray[0];
    if ((tempArray[0] == '-' || tempArray[0] == '+') &&
        s21_strchr("f", format[i])) {
      s21_strcat(str, temptemp);
      for (int i1 = 0; i1 < (int)s21_strlen(tempArray) - 1; i1++)
        tempArray[i1] = tempArray[i1 + 1];
      tempArray[s21_strlen(tempArray) - 1] = '\0';
    }
    while (len < width && width--) s21_strcat(str, zeroFlag ? "0" : " ");
  }
  s21_strcat(str, tempArray);
  if (leftFlag && (format[i] != '%' || OS))
    while (len < width && width--) s21_strcat(str, zeroFlag ? "0" : " ");
  *j += s21_strlen(str) - old_len - 1;
}

static void int_to_string(long long num, char *result_str) {
  if (num == 0)
    result_str[0] = '0';
  else {
    int i = 0, index = 0;
    if (num < 0) num *= -1, result_str[index] = '-', index++;
    long long tempNum = num;
    for (; tempNum != 0; i++) tempNum /= 10;
    i--;
    while (i >= 0) {
      tempNum = num;
      for (int j = 0; j != i; j++) tempNum /= 10;
      result_str[index] = tempNum % 10 + '0', i--, index++;
    }
    result_str[index] = '\0';
  }
}

static void float_to_string(long double num, char *result_str,
                            int from_first_not_zero, int accuracy,
                            int keepZero) {
  int negative = 0, firstIndex = 0, zeros = 0, foundNonZero = 0;
  if (num < 0) num *= -1, negative = 1;
  IF_FROM_FIRST_ZERO
  long long first = (long long)num;
  long double second = num - (long double)first;
  char firstArray[50] = "", secondArray[50] = "";
  int_to_string(first, firstArray);
  s21_strcat(result_str, firstArray);
  get_zeros(accuracy, &zeros, &second);
  int len = 0, lenAfter = 0;
  long long tempsecond = (long long)second;
  while (tempsecond != 0) tempsecond /= 10, len++;
  second = round(second), tempsecond = (long long)second;
  while (tempsecond != 0) tempsecond /= 10, lenAfter++;
  if (lenAfter > len) {
    if (zeros > 0)
      zeros--;
    else
      result_str[s21_strlen(result_str) - 1]++,
          second = (long long)second % (long long)pow(10, lenAfter - 1);
  }
  int_to_string((int)second, secondArray);
  for (int j = 0; j < zeros; j++)
    put_char_in_front_of_str(secondArray, '0', accuracy - 1, 0);
  for (int i = s21_strlen(secondArray); i < accuracy; i++) secondArray[i] = '0';
  for (int i = 0; i < (int)s21_strlen(secondArray) && foundNonZero == 0 &&
                  from_first_not_zero;
       i++)
    foundNonZero = secondArray[i] != '0';
  if ((((int)second != 0 || keepZero) &&
       (from_first_not_zero && foundNonZero)) ||
      !from_first_not_zero || keepZero) {
    s21_strcat(result_str, ".");
    for (int i = s21_strlen(secondArray) - 1;
         i > 0 && secondArray[i] == '0' && !keepZero; i--)
      secondArray[i] = '\0';
    s21_strcat(result_str, secondArray);
  }
  if (negative)
    put_char_in_front_of_str(result_str, '-', s21_strlen(result_str), 0);
}

static void float_to_e(long double num, char *result_str, int isSmol,
                       int accuracy, int supressZeros) {
  int isNegative = num < 0, vector = (long long)num != 0;
  num = isNegative ? -num : num;
  long long first = (long long)num;
  long double second = num - (long double)first;
  char firstArray[50] = "", secondArray[50] = "", counterStr[5] = "",
       dot = vector ? '.' : '\0';
  if (vector) {
    int counter = 0, zeros = 0;
    while (first / 10 > 0) first /= 10, counter++;
    get_zeros(accuracy - counter, &zeros, &second);
    long long leftPartOfSecond = (long long)num % (long long)pow(10, counter);
    int leftAlreadyAcc = (leftPartOfSecond > (long long)pow(10, accuracy) - 1);
    while (leftPartOfSecond > (long long)pow(10, accuracy) - 1)
      leftPartOfSecond /= 10;
    int_to_string(first, firstArray);
    int_to_string((int)counter, counterStr);
    if (leftPartOfSecond != 0) int_to_string(leftPartOfSecond, secondArray);
    if (leftAlreadyAcc == 0) {
      char rightPartOfSecondArray[50] = "";
      int_to_string((long long)round(second), rightPartOfSecondArray);
      if (second == 0) zeros--;
      for (int j = 0; j < zeros; j++)
        put_char_in_front_of_str(rightPartOfSecondArray, '0',
                                 s21_strlen(rightPartOfSecondArray), 0);
      s21_strcat(secondArray, rightPartOfSecondArray);
    }
    int len = s21_strlen(secondArray);
    for (int i = 0; i < accuracy - len; i++)
      put_char_in_front_of_str(secondArray, '0', accuracy - 1, 0);
    if (counter / 10 == 0) put_char_in_front_of_str(counterStr, '0', 3, 0);
    for (int i1 = s21_strlen(secondArray) - 1;
         i1 > 1 && (secondArray[i1] == '0' || secondArray[i1] == '.') &&
         supressZeros;
         i1--)
      secondArray[i1] = '\0';
    if (firstArray[0] == '0' && supressZeros) dot = '\0';
  } else {
    int counter = 0;
    while ((int)second == 0) second *= 10, counter++;
    float_to_string(second, firstArray, 0, accuracy, !supressZeros);
    int_to_string(counter, counterStr);
    if (counter / 10 == 0) put_char_in_front_of_str(counterStr, '0', 3, 0);
  }
  s21_sprintf(result_str, "%c%s%c%s%c%c%s", isNegative ? '-' : '\0', firstArray,
              dot, secondArray, isSmol ? 'e' : 'E', vector ? '+' : '-',
              counterStr);
}

static unsigned int convert_to_oct(unsigned int num) {
  unsigned int res = 0, counter = 0;
  do res += (num % 8) * pow(10, counter), num /= 8, counter++;
  while (num != 0);
  return res;
}

static void convert_to_hex(unsigned long long num, char *result, int isSmol) {
  int counter = 0;
  do {
    for (int i = counter; i > 0; i--) result[i] = result[i - 1];
    result[0] = get_hex(num % 16, isSmol);
    num /= 16, counter++;
  } while (num != 0);
}

static char get_hex(unsigned int num, int smol) {
  return num + '0' + (num > 9 ? (smol ? 39 : 7) : 0);
}

static void put_char_in_front_of_str(char *str, char ch, int len, int start) {
  for (int j = len; j > start; j--) str[j] = str[j - 1];
  str[0] = ch;
}

void get_zeros(int accuracy, int *zeros, long double *second) {
  for (int i = 0; i < accuracy; i++) {
    long long oldSecond = (long long)*second;
    *second = *second * 10;
    if ((long long)oldSecond == (long long)(*second)) *zeros += 1;
  }
}
#undef SPECIFIERS
#undef FLAGS
#undef ARG_LEN
#undef ADD_SIGN
#undef ADD_ACCURACY_TO_NUMBER
#undef PARSE_FLAGS_ETC
#undef SPECIFIERS_SWITCH
#undef G_TO_STR
#undef E_TO_STR
#undef F_TO_STR
#undef D_TO_STR
#undef O_TO_STR
#undef X_TO_STR
#undef P_TO_STR
#undef U_TO_STR
#undef C_TO_STR
#undef PERCENT_TO_STR
#undef STR_TO_STR
#undef N_TO_STR
#undef IF_FROM_FIRST_ZERO
