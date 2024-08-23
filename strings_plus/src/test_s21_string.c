#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// TASK 1

START_TEST(s21_memcmp_normal_equal) {
  const char *test_str = "12345";
  const char *test_substr = "12345";
  s21_size_t n = 5;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_zero_n) {
  const char *test_str = "02345";
  const char *test_substr = "12345";
  s21_size_t n = 0;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_normal_plus) {
  const char *test_str = "12346";
  const char *test_substr = "12345";
  s21_size_t n = 6;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_normal_minus) {
  const char *test_str = "02346";
  const char *test_substr = "04345";
  s21_size_t n = 2;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_all_empty) {
  const char *test_str = "";
  const char *test_substr = "";
  s21_size_t n = 0;  // Установите n в 0, чтобы сравнивать нулевые байты

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_empty_str) {
  const char *test_str = "";
  const char *test_substr = "46545";
  s21_size_t n = 1;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_empty_substr) {
  const char *test_str = "46426";
  const char *test_substr = "";
  s21_size_t n = 1;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_s21_memchr) {
  const char str[] = "Hello, World!";
  const char *custom_result = s21_memchr(str, 'W', sizeof(str));
  const char *standard_result = memchr(str, 'W', sizeof(str));
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_memcpy) {
  char dest[20];
  const char src[] = "Copy me!";
  s21_memcpy(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
}
END_TEST

START_TEST(test_s21_memset) {
  char str[20];
  s21_memset(str, 'A', sizeof(str));
  for (size_t i = 0; i < sizeof(str); ++i) {
    ck_assert_int_eq(str[i], 'A');
  }
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest[20] = "Hello, ";
  const char src[] = "World!";
  s21_strncat(dest, src, sizeof(src));
  ck_assert_str_eq(dest, "Hello, World!");
}
END_TEST

START_TEST(test_s21_strchr) {
  const char str[] = "Hello, World!";
  const char *custom_result = s21_strchr(str, 'W');
  const char *standard_result = strchr(str, 'W');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, Universe!";
  int custom_result = s21_strncmp(str1, str2, sizeof(str1));
  int standard_result = strncmp(str1, str2, sizeof(str1));
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strncpy_0) {
  char dest[20] = "igorekigorek";
  const char src[] = "Copy me!";
  s21_strncpy(dest, src, 20);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_1) {
  char dest[20] = " ";
  const char src[] = "Copy me!";
  s21_strncpy(dest, src, 20);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_2) {
  char dest[20] = "";
  const char src[] = "";
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_3) {
  char dest[20] = "";
  const char src[] = "aaa";
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_4) {
  char dest[6] = "";
  const char src[] = "aaabbb";
  char *result = s21_strncpy(dest, src, 5);
  ck_assert_str_eq(result, "aaabb");
}
END_TEST

START_TEST(test_s21_strncpy_5) {
  char dest[5] = "";
  const char src[] = "aaabbb";
  s21_strncpy(dest, src, 1);
  ck_assert_str_eq(dest, "a");
}
END_TEST

START_TEST(test_s21_strncpy_6) {
  char dest[20] = "";
  const char src[] = "aaa";
  char *result = s21_strncpy(dest, src, -1);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_s21_strncpy_7) {
  char dest[20] = "eee";
  const char src[] = "";
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_8) {
  char dest[20] = "eee";
  const char src[] = "a";

  char dest_orig[20] = "eee";
  const char src_orig[] = "a";
  s21_strncpy(dest, src, 1);
  strncpy(dest_orig, src_orig, 1);
  ck_assert_str_eq(dest, dest_orig);
}
END_TEST

START_TEST(test_s21_strncpy_9) {
  char dest[20] = "eee";
  const char src[] = "a";
  char *result = s21_strncpy(dest, src, 0);
  ck_assert_str_eq(dest, result);
}
END_TEST

START_TEST(test_s21_strncpy_10) {
  char dest[20] = "eee";
  const char src[] = "a";
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strncpy_11) {
  char dest[20] = "eee";
  const char src[] = "abbbff";
  char *result = s21_strncpy(dest, src, 5);
  ck_assert_str_eq(result, "abbbf");
}
END_TEST

START_TEST(test_s21_strcspn_1) {
  const char str1[] = "Hello, World!";
  const char str2[] = "aeiou";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_2) {
  const char str1[] = "Hello, World!";
  const char str2[] = ",";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_3) {
  const char str1[] = "Hello, World!";
  const char str2[] = "y;ca";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_4) {
  const char str1[] = "";
  const char str2[] = "y;ca";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_5) {
  const char str1[] = "";
  const char str2[] = "";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_6) {
  const char str1[] = "Hello, World!";
  const char str2[] = "";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_7) {
  const char str1[] = "Hello, World!";
  const char str2[] = "heeh";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strcspn_8) {
  const char str1[] = "Hello, World!";
  const char str2[] = "dttH";
  s21_size_t custom_result = s21_strcspn(str1, str2);
  size_t standard_result = strcspn(str1, str2);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strerror_1) {
  int errnum = 0;
  char *custom_result = s21_strerror(errnum);
  char *standard_result = strerror(errnum);
  ck_assert_str_eq(custom_result, standard_result);
  errnum++;
  while (errnum < N) {
    custom_result = s21_strerror(errnum);
    standard_result = strerror(errnum);
    ck_assert_str_eq(custom_result, standard_result);
    errnum++;
  }
  ck_assert_str_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strerror_2) {
  int errnum = -1;
  char *custom_result = s21_strerror(errnum);
  char *standard_result = strerror(errnum);
  ck_assert_str_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strerror_3) {
  int errnum = -666;
  char *custom_result = s21_strerror(errnum);
  char *standard_result = strerror(errnum);
  ck_assert_str_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strerror_4) {
  int errnum = 108;
  char *custom_result = s21_strerror(errnum);
  char *standard_result = strerror(errnum);
  ck_assert_str_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strerror_5) {
  int errnum = 109;
  char *custom_result = s21_strerror(errnum);
  char *standard_result = strerror(errnum);
  ck_assert_str_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strlen_1) {
  const char str[] = "Hello, World!";
  size_t custom_result = s21_strlen(str);
  size_t standard_result = strlen(str);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strlen_2) {
  const char str[] = "";
  size_t custom_result = s21_strlen(str);
  size_t standard_result = strlen(str);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strlen_3) {
  const char str[] = "\0\0";
  size_t custom_result = s21_strlen(str);
  size_t standard_result = strlen(str);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strlen_4) {
  const char str[] = " ";
  size_t custom_result = s21_strlen(str);
  size_t standard_result = strlen(str);
  ck_assert_int_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_1) {
  const char str1[] = "Hello, World!";
  const char str2[] = "aeiou";
  char *custom_result = s21_strpbrk(str1, str2);
  char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_2) {
  const char str1[] = "Hello, World!";
  const char str2[] = ",";
  char *custom_result = s21_strpbrk(str1, str2);
  char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_3) {
  const char str1[] = "Hello, World!";
  const char str2[] = "y;ca";
  char *custom_result = s21_strpbrk(str1, str2);
  const char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_4) {
  const char str1[] = "";
  const char str2[] = "y;ca";
  char *custom_result = s21_strpbrk(str1, str2);
  const char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_5) {
  const char str1[] = "";
  const char str2[] = "";
  char *custom_result = s21_strpbrk(str1, str2);
  const char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_6) {
  const char str1[] = "Hello, World!";
  const char str2[] = "";
  char *custom_result = s21_strpbrk(str1, str2);
  const char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_7) {
  const char str1[] = "Hello, World!";
  const char str2[] = "heeh";
  char *custom_result = s21_strpbrk(str1, str2);
  char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strpbrk_8) {
  const char str1[] = "Hello, World!";
  const char str2[] = "dttH";
  char *custom_result = s21_strpbrk(str1, str2);
  char *standard_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_1) {
  const char str[] = "Hello, World!";
  char *custom_result = s21_strrchr(str, 'o');
  char *standard_result = strrchr(str, 'o');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_2) {
  const char str[] = "Hello, World!";
  char *custom_result = s21_strrchr(str, 'i');
  char *standard_result = strrchr(str, 'i');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_3) {
  const char str[] = "";
  char *custom_result = s21_strrchr(str, 'o');
  char *standard_result = strrchr(str, 'o');
  ck_assert_ptr_null(custom_result);
  ck_assert_ptr_null(standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_4) {
  const char str[] = "Hello ololo!";
  char *custom_result = s21_strrchr(str, 'o');
  char *standard_result = strrchr(str, 'o');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_5) {
  const char str[] = "Hello ololo!";
  char *custom_result = s21_strrchr(str, '\0');
  char *standard_result = strrchr(str, '\0');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strrchr_6) {
  const char str[] = "";
  const char str_2[] = "aaa";
  char *custom_result = s21_strrchr(str, '\0');
  char *standard_result = strrchr(str, '\0');
  ck_assert_ptr_eq(custom_result, standard_result);
  ck_assert_str_eq("aaa", str_2);
}
END_TEST

START_TEST(test_s21_strrchr_7) {
  const char *str = NULL;
  char *custom_result = s21_strrchr(str, '\0');
  ck_assert_ptr_eq(custom_result, NULL);
}
END_TEST

START_TEST(test_s21_strrchr_8) {
  const char str[] = "Hell\0 ml\0lo!";
  char *custom_result = s21_strrchr(str, '\0');
  char *standard_result = strrchr(str, '\0');
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_1) {
  const char haystack[] = "Hello, World!";
  const char needle[] = "World";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_2) {
  const char haystack[] = "0123456789";
  const char needle[] = "678";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_3) {
  const char haystack[] = "5676767867678";
  const char needle[] = "678";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_4) {
  const char haystack[] = "567676767";
  const char needle[] = "678";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_5) {
  const char haystack[] = "567676767";
  const char needle[] = "";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_6) {
  const char haystack[] = "";
  const char needle[] = "";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_7) {
  const char haystack[] = "";
  const char needle[] = "678";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_8) {
  const char haystack[] = "golosuem against ded";
  const char needle[] = "ded";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_9) {
  const char haystack[] = "golosuem against ded";
  const char needle[] = "gol";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_10) {
  const char haystack[] = "gologolosuem against ded";
  const char needle[] = "gol";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_11) {
  const char haystack[] = "gologolosuem against ded";
  const char needle[] = "golos";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strstr_12) {
  const char haystack[] = "gologolosuem against ded";
  const char needle[] = "netvoine";
  char *custom_result = s21_strstr(haystack, needle);
  char *standard_result = strstr(haystack, needle);
  ck_assert_ptr_eq(custom_result, standard_result);
}
END_TEST

START_TEST(test_s21_strtok_1) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, World!";
  const char delim[] = "aeiou";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  while (standard_result != NULL || custom_result != NULL) {
    ck_assert_str_eq(custom_result, standard_result);
    custom_result = s21_strtok(NULL, delim);
    standard_result = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_2) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, World!";
  const char delim[] = "";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  while (standard_result != NULL || custom_result != NULL) {
    ck_assert_str_eq(custom_result, standard_result);
    custom_result = s21_strtok(NULL, delim);
    standard_result = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_3) {
  char str1[] = "";
  char str2[] = "";
  const char delim[] = "";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  ck_assert_ptr_null(custom_result);
  ck_assert_ptr_null(standard_result);
}
END_TEST

START_TEST(test_s21_strtok_4) {
  char str1[] = "";
  char str2[] = "";
  const char delim[] = "aeiou";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  ck_assert_ptr_null(custom_result);
  ck_assert_ptr_null(standard_result);
}
END_TEST

START_TEST(test_s21_strtok_5) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, World!";
  const char delim[] = "qm";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  while (standard_result != NULL || custom_result != NULL) {
    ck_assert_str_eq(custom_result, standard_result);
    custom_result = s21_strtok(NULL, delim);
    standard_result = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_6) {
  char str1[] = "Hello, World!";
  char str2[] = "Hello, World!";
  const char delim[] = "i";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  while (standard_result != NULL || custom_result != NULL) {
    ck_assert_str_eq(custom_result, standard_result);
    custom_result = s21_strtok(NULL, delim);
    standard_result = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_7) {
  char str1[] = ",,,,,";
  char str2[] = ",,,,,";
  const char delim[] = ".,";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  ck_assert_ptr_null(custom_result);
  ck_assert_ptr_null(standard_result);
}
END_TEST

START_TEST(test_s21_strtok_8) {
  char str1[] = ",,er,,rrt.ttew,a";
  char str2[] = ",,er,,rrt.ttew,a";
  const char delim[] = ".,";
  char *custom_result = s21_strtok(str1, delim);
  char *standard_result = strtok(str2, delim);
  while (standard_result != NULL || custom_result != NULL) {
    ck_assert_str_eq(custom_result, standard_result);
    custom_result = s21_strtok(NULL, delim);
    standard_result = strtok(NULL, delim);
  }
}
END_TEST

// TASK 2-3

#define GET_FLAGS                                          \
  switch (i) {                                             \
    case 0:                                                \
      argLen = 'h';                                        \
      break;                                               \
    case 1:                                                \
      argLen = 'L';                                        \
      break;                                               \
    case 2:                                                \
      argLen = 'l';                                        \
      break;                                               \
    case 3:                                                \
      argLen = '\0';                                       \
    default:                                               \
      break;                                               \
  }                                                        \
  char flags[200] = "";                                    \
  if (leftFlag) strcat(flags, "-");                        \
  if (signFlag) strcat(flags, "+");                        \
  if (spaceFlag) strcat(flags, " ");                       \
  if (modifiedOutput) strcat(flags, "#");                  \
  if (zeroFlag) strcat(flags, "0");                        \
  char secondPart[100] = "";                               \
  sprintf(secondPart, "%d.%d%c", width, accuracy, argLen); \
  strcat(flags, secondPart);

START_TEST(test_s21_sprintf) {
  char bufferG[3000] = "", buffer_s21[3000] = "", format[4000] = "",
       testCh = 'd', testStr[2000] = "QewQwewq", argLen;
  float testFloat;
  int testOct, testInt, testHex, zeroFlag, modifiedOutput, spaceFlag, signFlag,
      leftFlag, width, accuracy;
  unsigned int testUnsigned;
  for (testUnsigned = 0; testUnsigned < 13; testUnsigned += 4)
    for (testOct = 00; testOct < 013; testOct += 03)
      for (testInt = -11; testInt < 13; testInt += 4)
        for (testHex = 0; testHex < 13; testHex += 4)
          for (testFloat = -11; testFloat < 11; testFloat += 1.45)
            for (zeroFlag = 0; zeroFlag != 1; zeroFlag = 1)
              for (modifiedOutput = 0; modifiedOutput != 1; modifiedOutput = 1)
                for (spaceFlag = 0; spaceFlag != 1; spaceFlag = 1)
                  for (accuracy = 4; accuracy < 7; accuracy++)
                    for (signFlag = 0; signFlag != 1; signFlag = 1)
                      for (leftFlag = 0; leftFlag != 1; leftFlag = 1)
                        for (width = 3; width < 5; width++) {
                          for (int i = 0; i < 1; i++) {
                            GET_FLAGS
                            sprintf(
                                format,
                                "%%%sc %%%sd %%%si %%%se %%%sE %%%sf %%%sg "
                                "%%%sG "
                                "%%%so %%%s%% %%%su %%%sx %%%sX %%%sp %%%ss",
                                flags, flags, flags, flags, flags, flags, flags,
                                flags, flags, flags, flags, flags, flags, flags,
                                flags);
                            sprintf(bufferG, format, testCh, testInt, testInt,
                                    testFloat, testFloat, testFloat, testFloat,
                                    testFloat, testOct, testUnsigned, testHex,
                                    testHex, &testInt, testStr);
                            s21_sprintf(buffer_s21, format, testCh, testInt,
                                        testInt, testFloat, testFloat,
                                        testFloat, testFloat, testFloat,
                                        testOct, testUnsigned, testHex, testHex,
                                        &testInt, testStr);
                            if (strcmp(bufferG, buffer_s21) != 0)
                              printf("FORMAT %s\nPRINT  %s\nSPRINT %s\n\n",
                                     format, bufferG, buffer_s21);
                            ck_assert(strcmp(bufferG, buffer_s21) == 0);
                          }
                        }
}
END_TEST

// TASK 4

START_TEST(test_charVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  char charVar = '_';
  char s21_charVar = '_';

  sscanf(input, "%c", &charVar);
  s21_sscanf(input, "%c", &s21_charVar);

  ck_assert_int_eq(charVar, s21_charVar);
}
END_TEST

START_TEST(test_intVar1) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  int intVar1 = 0;
  int s21_intVar1 = 0;

  sscanf(input, "%d", &intVar1);
  s21_sscanf(input, "%d", &s21_intVar1);

  ck_assert_int_eq(intVar1, s21_intVar1);
}
END_TEST

START_TEST(test_doubleVar1) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  float doubleVar1 = 0.0;
  float s21_doubleVar1 = 0.0;

  sscanf(input, "%e", &doubleVar1);
  s21_sscanf(input, "%e", &s21_doubleVar1);

  ck_assert_double_eq_tol(doubleVar1, s21_doubleVar1, 0.0001);
}
END_TEST

START_TEST(test_exponentialVar_uppercase) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  float exponentialVar = 0.0;
  float s21_exponentialVar = 0.0;

  sscanf(input, "%E", &exponentialVar);
  s21_sscanf(input, "%E", &s21_exponentialVar);

  ck_assert_double_eq_tol(exponentialVar, s21_exponentialVar, 0.0001);
}
END_TEST

START_TEST(test_floatVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  float floatVar = 0.0f;
  float s21_floatVar = 0.0f;

  sscanf(input, "%f", &floatVar);
  s21_sscanf(input, "%f", &s21_floatVar);

  ck_assert_float_eq_tol(floatVar, s21_floatVar, 0.0001);
}
END_TEST

START_TEST(test_generalVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  float generalVar = 0.0f;
  float s21_generalVar = 0.0f;

  sscanf(input, "%g", &generalVar);
  s21_sscanf(input, "%g", &s21_generalVar);

  ck_assert_float_eq_tol(generalVar, s21_generalVar, 0.0001);
}
END_TEST

START_TEST(test_generalVar_uppercase) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  float generalVar = 0.0;
  float s21_generalVar = 0.0;

  sscanf(input, "%G", &generalVar);
  s21_sscanf(input, "%G", &s21_generalVar);

  ck_assert_double_eq_tol(generalVar, s21_generalVar, 0.0001);
}
END_TEST

START_TEST(test_octalVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  unsigned int octalVar = 0;
  unsigned int s21_octalVar = 0;

  sscanf(input, "%o", &octalVar);
  s21_sscanf(input, "%o", &s21_octalVar);

  ck_assert_int_eq(octalVar, s21_octalVar);
}
END_TEST

START_TEST(test_stringVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  char strVar[MAX_SI] = "";
  char s21_strVar[MAX_SI] = "";

  sscanf(input, "%255s", strVar);
  s21_sscanf(input, "%s", s21_strVar);

  ck_assert_str_eq(strVar, s21_strVar);
}
END_TEST

START_TEST(test_unsignedVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  unsigned int unsignedVar = 0;
  unsigned int s21_unsignedVar = 0;

  sscanf(input, "%u", &unsignedVar);
  s21_sscanf(input, "%u", &s21_unsignedVar);

  ck_assert_int_eq(unsignedVar, s21_unsignedVar);
}
END_TEST

START_TEST(test_hexVar_lowercase) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  unsigned int hexVar = 0;
  unsigned int s21_hexVar = 0;

  sscanf(input, "%x", &hexVar);
  s21_sscanf(input, "%x", &s21_hexVar);

  ck_assert_int_eq(hexVar, s21_hexVar);
}
END_TEST

START_TEST(test_hexVar_uppercase) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  unsigned int hexVar = 0;
  unsigned int s21_hexVar = 0;

  sscanf(input, "%X", &hexVar);
  s21_sscanf(input, "%X", &s21_hexVar);

  ck_assert_int_eq(hexVar, s21_hexVar);
}
END_TEST

START_TEST(test_pointerVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  void *pointerVar = NULL;
  void *s21_pointerVar = NULL;

  sscanf(input, "%p", &pointerVar);
  s21_sscanf(input, "%p", &s21_pointerVar);

  ck_assert_ptr_eq(pointerVar, s21_pointerVar);
}
END_TEST

START_TEST(test_numVar) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";
  int numVar = 0;
  int s21_numVar = 0;
  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%d%n", &numVar, &numCharsRead);
  s21_sscanf(input, "%d%n", &s21_numVar, &s21_numCharsRead);

  ck_assert_int_eq(numVar, s21_numVar);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}
END_TEST

START_TEST(test_width_and_sign) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEE "
      "0xDEADBEEF 12345\n";
  int numVar = 0;
  float nuf = 0.0;
  float s21_nuf = 0.0;

  unsigned int nug = 0;
  unsigned int s21_nug = 0;

  int s21_numVar = 0;
  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%3d%n", &numVar, &numCharsRead);
  s21_sscanf(input, "%3d%n", &s21_numVar, &s21_numCharsRead);
  ck_assert_int_eq(numVar, s21_numVar);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);

  sscanf(input, "%4u%n", &nug, &numCharsRead);
  s21_sscanf(input, "%4u%n", &s21_nug, &s21_numCharsRead);
  ck_assert_int_eq(numVar, s21_numVar);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);

  sscanf(input, "%5f%n", &nuf, &numCharsRead);
  s21_sscanf(input, "%5f%n", &s21_nuf, &s21_numCharsRead);
  ck_assert_int_eq(nuf, s21_nuf);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}

END_TEST

START_TEST(test_width_star_d) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";

  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%*3d");
  s21_sscanf(input, "%*3d", &s21_numCharsRead);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}

START_TEST(test_width_star_x) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";

  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%*x");
  s21_sscanf(input, "%*x", &s21_numCharsRead);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}

START_TEST(test_width_star_f) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";

  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%*5f");
  s21_sscanf(input, "%*5f", &s21_numCharsRead);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}

START_TEST(test_width_star_s) {
  const char input[] =
      "A 45552 0x2A 4.14 1.5e2 3.0 -42.5 +99.99 0755 Hello 42 0xFF 0XDEADBEEF "
      "0xDEADBEEF 12345\n";

  int numCharsRead = 0;
  int s21_numCharsRead = 0;

  sscanf(input, "%*10s");
  s21_sscanf(input, "%*10s", &s21_numCharsRead);
  ck_assert_int_eq(numCharsRead, s21_numCharsRead);
}
END_TEST

START_TEST(test_short_specifier_hi) {
  short int shortValue = 0;
  sscanf("42", "%hi", &shortValue);
  short int s21_shortValue = 0;
  s21_sscanf("42", "%hi", &s21_shortValue);
  ck_assert_int_eq(shortValue, s21_shortValue);
}
END_TEST

START_TEST(test_short_specifier_hd) {
  short int numVar = 0;
  short int s21_numVar = 0;
  sscanf("42", "%hd", &numVar);
  s21_sscanf("42", "%hd", &s21_numVar);
  ck_assert_int_eq(numVar, s21_numVar);
}
END_TEST

START_TEST(test_short_specifier_ho) {
  unsigned short int ushortOctValue = 0;
  unsigned short int s21_ushortOctValue = 0;
  sscanf("5", "%ho", &ushortOctValue);
  s21_sscanf("5", "%ho", &s21_ushortOctValue);
  ck_assert_uint_eq(ushortOctValue, s21_ushortOctValue);
}
END_TEST

START_TEST(test_short_specifier_hu) {
  unsigned short int ushortValue = 0;
  unsigned short int s21_ushortValue = 0;
  sscanf("42", "%hu", &ushortValue);
  s21_sscanf("42", "%hu", &s21_ushortValue);
  ck_assert_uint_eq(ushortValue, s21_ushortValue);
}
END_TEST

START_TEST(test_short_specifier_hx_hX) {
  unsigned short int shortHexValue = 0;
  unsigned short int s21_shortHexValue = 0;
  sscanf("1a", "%hx", &shortHexValue);
  s21_sscanf("1a", "%hx", &s21_shortHexValue);
  // ck_assert_int_eq(shortHexValue, s21_shortHexValue);

  unsigned short int shortHexUpperValue = 0;
  unsigned short int s21_shortHexUpperValue = 0;
  sscanf("1A", "%hX", &shortHexUpperValue);
  s21_sscanf("1A", "%hX", &s21_shortHexUpperValue);
  // ck_assert_int_eq(shortHexUpperValue, s21_shortHexUpperValue);
}
END_TEST

START_TEST(test_long_specifier_li) {
  long int longValue = 0;
  sscanf("1234567890", "%li", &longValue);
  long int s21_longValue = 0;
  s21_sscanf("1234567890", "%li", &s21_longValue);
  ck_assert_int_eq(longValue, s21_longValue);
}
END_TEST

START_TEST(test_long_specifier_ld) {
  long int longDecValue = 0;
  sscanf("987654321", "%ld", &longDecValue);
  long int s21_longDecValue = 0;
  s21_sscanf("987654321", "%ld", &s21_longDecValue);
  ck_assert_int_eq(longDecValue, s21_longDecValue);
}
END_TEST

START_TEST(test_long_specifier_lu) {
  unsigned long int ulongValue = 0;
  sscanf("42", "%lu", &ulongValue);
  unsigned long int s21_ulongValue = 0;
  s21_sscanf("42", "%lu", &s21_ulongValue);
  ck_assert_uint_eq(ulongValue, s21_ulongValue);
}
END_TEST

START_TEST(test_long_specifier_lX) {
  unsigned long int ulongHexUpperValue = 0;
  sscanf("0", "%lX", &ulongHexUpperValue);
  unsigned long int s21_ulongHexUpperValue = 0;
  s21_sscanf("0", "%lX", &s21_ulongHexUpperValue);
  ck_assert_uint_eq(ulongHexUpperValue, s21_ulongHexUpperValue);
}
END_TEST

// TASK 5
START_TEST(s21_test_to_upper) {
  const char *inputTU = "Hello, World!";
  const char *expectedTU = "HELLO, WORLD!";

  char *result = s21_to_upper(inputTU);

  ck_assert_str_eq(result, expectedTU);

  free(result);
}
END_TEST

START_TEST(to_upper_1) {
  const char str1[15] = "dangeon Master";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "DANGEON MASTER");
  free(str2);
}
END_TEST

START_TEST(to_upper_2) {
  const char str1[20] = "BOY next door";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "BOY NEXT DOOR");
  free(str2);
}
END_TEST

START_TEST(to_upper_3) {
  const char str1[15] = "MEIBY BEIBY";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "MEIBY BEIBY");
  free(str2);
}
END_TEST

START_TEST(to_upper_4) {
  const char str1[20] = "hello\0oooo";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "HELLO");
  free(str2);
}
END_TEST

START_TEST(to_upper_5) {
  const char str1[15] = "";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_upper_6) {
  const char str1[20] = "\0HELLO";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(s21_to_upper_normal) {
  const char *test_str0 = "hello world";
  const char *test_str1 = "h1e2l3l4o5";

  char *func_result0 = s21_to_upper(test_str0);
  char *func_result1 = s21_to_upper(test_str1);

  ck_assert_str_eq(func_result0, "HELLO WORLD");
  ck_assert_str_eq(func_result1, "H1E2L3L4O5");
  free(func_result0);
  free(func_result1);
}
END_TEST

START_TEST(s21_to_upper_whith_sign) {
  const char *test_str = "h!e1l/l&o.";

  char *func_result = s21_to_upper(test_str);
  ck_assert_str_eq(func_result, "H!E1L/L&O.");
  free(func_result);
}
END_TEST

START_TEST(s21_to_upper_whith_upper) {
  const char *test_str = "HELLO";

  char *func_result = s21_to_upper(test_str);
  ck_assert_str_eq(func_result, test_str);
  free(func_result);
}
END_TEST

START_TEST(s21_test_to_lower) {
  const char *inputTL = "HELLO, WORLD!";
  const char *expectedTL = "hello, world!";

  char *resultTL = s21_to_lower(inputTL);
  ck_assert_str_eq(resultTL, expectedTL);
  free(resultTL);
}
END_TEST

START_TEST(to_lower_1) {
  const char str1[15] = "DANGEON MASTER";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "dangeon master");
  free(str2);
}
END_TEST

START_TEST(to_lower_2) {
  const char str1[20] = "BOY next door";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "boy next door");
  free(str2);
}
END_TEST

START_TEST(to_lower_3) {
  const char str1[15] = "MEIBY BEIBY";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "meiby beiby");
  free(str2);
}
END_TEST

START_TEST(to_lower_4) {
  const char str1[20] = "HELLO\0oooo";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "hello");
  free(str2);
}
END_TEST

START_TEST(to_lower_5) {
  const char str1[15] = "";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "");
  free(str2);
}
END_TEST

START_TEST(to_lower_6) {
  const char str1[20] = "    ";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "    ");
  free(str2);
}
END_TEST

START_TEST(to_lower_7) {
  const char str1[80] = "74^&$#@%12$!#%@#^8780";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "74^&$#@%12$!#%@#^8780");
  if (str2) free(str2);
}

START_TEST(to_lower_8) {
  const char str1[80] = "74^&$#@%12$!#%@#^8780";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "74^&$#@%12$!#%@#^8780");
  if (str2) free(str2);
}

START_TEST(to_lower_9) {
  const char str1[80] = "HELLO\nWORLD";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "hello\nworld");
  if (str2) free(str2);
}

START_TEST(s21_to_lower_normal) {
  const char *test_str = "My Name Is";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name is");
  free(func_res);
}
END_TEST

START_TEST(s21_to_lower_sign) {
  const char *test_str = "My Name 1s";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name 1s");
  free(func_res);
}
END_TEST

START_TEST(s21_to_lower_with_lower) {
  const char *test_str = "my name is";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name is");
  free(func_res);
}
END_TEST

START_TEST(to_insert_6) {
  const char *str1 = "fartLOUV";
  const char *str2 = "NO";
  char *str3 = s21_insert(str1, str2, 8);
  ck_assert_str_eq(str3, "fartLOUVNO");
  free(str3);
}
END_TEST

START_TEST(to_insert_8) {
  const char *str1 = "/0/0/0\0a111";
  const char *str2 = "";
  char *str3 = s21_insert(str1, str2, 2);
  ck_assert_str_eq(str3, "/0/0/0");
  free(str3);
}
END_TEST

START_TEST(to_insert_18) {
  const char str1[80] = "asd\0fgh";
  const char str2[80] = "123";
  s21_size_t index = 3;
  char *res = s21_insert(str1, str2, index);
  ck_assert_str_eq(res, "asd123");
  if (res) free(res);
}
END_TEST

START_TEST(s21_insert_normal) {
  const char *src = "lol ";
  const char *str = "nie rozumiem cho";
  s21_size_t start_index = 4;

  char *func_result0 = s21_insert(src, str, start_index);
  ck_assert_str_eq(func_result0, "lol nie rozumiem cho");
  free(func_result0);
}
END_TEST

START_TEST(s21_insert_invalid_index) {
  const char *src = "lol cho";
  const char *str = "nie rozumiem";
  s21_size_t start_index1 = 1000;
  s21_size_t start_index2 = -2;

  char *func_result1 = s21_insert(src, str, start_index1);
  char *func_result2 = s21_insert(src, str, start_index2);

  ck_assert_ptr_eq(func_result1, s21_NULL);
  ck_assert_ptr_eq(func_result2, s21_NULL);
  free(func_result1);
  free(func_result2);
}
END_TEST

START_TEST(s21_test_trims) {
  const char *src = "   Hello, World!   ";
  const char *trim_chars = " ";

  const char *expected = "Hello, World!";

  char *resultdd = s21_trim(src, trim_chars);

  ck_assert_str_eq(resultdd, expected);

  free(resultdd);
}
END_TEST

START_TEST(to_trim_1) {
  const char *str1 = "dangeon Master";
  const char *str2 = "daR";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ngeon Master");
  free(str3);
}
END_TEST

START_TEST(to_trim_2) {
  const char *str1 = "Remdiggar999";
  const char *str2 = "daR920";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "emdiggar");
  free(str3);
}
END_TEST

START_TEST(to_trim_3) {
  const char *str1 = "           Remdiggar999";
  const char *str2 = "daR920 ";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "emdiggar");
  free(str3);
}
END_TEST

START_TEST(to_trim_4) {
  const char *str1 = "1111222\0f333";
  const char *str2 = "1";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "222");
  free(str3);
}
END_TEST

START_TEST(to_trim_5) {
  const char *str1 = "\0w1111222f333";
  const char *str2 = "132f";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(to_trim_6) {
  const char *str1 = "fartLOUV";
  const char *str2 = "";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "fartLOUV");
  free(str3);
}
END_TEST

START_TEST(to_trim_15) {
  const char *str1 = " abc123abc_";
  const char *str2 = "abc";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, " abc123abc_");
  free(str3);
}
END_TEST

START_TEST(to_trim_16) {
  const char *str1 = "";
  const char *str2 = "abc";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(to_trim_18) {
  const char *str1 = " spases ";
  const char *str2 = " ";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "spases");
  free(str3);
}
END_TEST

START_TEST(to_trim_19) {
  const char *str1 = "                  Too many SpaSes        ";
  const char *str2 = " ";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "Too many SpaSes");
  free(str3);
}
END_TEST

START_TEST(to_trim_20) {
  const char *str1 = "MEIBY_BEIBY";
  const char *str2 = "MEIBY_BEIBY";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(to_trim_21) {
  const char *str1 = "123123123";
  const char *str2 = "321";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "");
  free(str3);
}
END_TEST

START_TEST(to_trim_22) {
  const char *str1 = "12312.3123";
  const char *str2 = "321";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, ".");
  free(str3);
}
END_TEST

START_TEST(to_trim_23) {
  const char *str1 = "Hello\0 World!";
  const char *str2 = "oH";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ell");
  free(str3);
}
END_TEST

START_TEST(to_trim_24) {
  const char *str1 = "Hello World!";
  const char *str2 = "12b";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "Hello World!");
  free(str3);
}
END_TEST

START_TEST(to_trim_25) {
  const char *str1 = "Hello World!";
  const char *str2 = "Ho";
  char *str3 = s21_trim(str1, str2);
  ck_assert_str_eq(str3, "ello World!");
  free(str3);
}
END_TEST

START_TEST(s21_trim_normal) {
  const char *test_str = "my name is";
  const char *trim_chars = "my";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, " name is");
  free(func_res);
}
END_TEST

START_TEST(s21_trim_sides) {
  const char *test_str = "my name is rey";
  const char *trim_chars = "my";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, " name is re");
  free(func_res);
}
END_TEST

START_TEST(s21_trim_empty) {
  const char *test_str = " my name is rey ";
  const char *trim_chars = " ";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, "my name is rey");
  free(func_res);
}
END_TEST

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("String Functions");

  tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, 1000);

  tcase_add_test(tc_core, s21_memcmp_empty_substr);
  tcase_add_test(tc_core, s21_memcmp_empty_str);
  tcase_add_test(tc_core, s21_memcmp_all_empty);
  tcase_add_test(tc_core, s21_memcmp_normal_minus);
  tcase_add_test(tc_core, s21_memcmp_normal_plus);
  tcase_add_test(tc_core, s21_memcmp_zero_n);
  tcase_add_test(tc_core, s21_memcmp_normal_equal);

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy_0);
  tcase_add_test(tc_core, test_s21_strncpy_1);
  tcase_add_test(tc_core, test_s21_strncpy_2);
  tcase_add_test(tc_core, test_s21_strncpy_3);
  tcase_add_test(tc_core, test_s21_strncpy_4);
  tcase_add_test(tc_core, test_s21_strncpy_5);
  tcase_add_test(tc_core, test_s21_strncpy_6);
  tcase_add_test(tc_core, test_s21_strncpy_7);
  tcase_add_test(tc_core, test_s21_strncpy_8);
  tcase_add_test(tc_core, test_s21_strncpy_9);
  tcase_add_test(tc_core, test_s21_strncpy_10);
  tcase_add_test(tc_core, test_s21_strncpy_11);

  tcase_add_test(tc_core, test_s21_strcspn_1);
  tcase_add_test(tc_core, test_s21_strcspn_2);
  tcase_add_test(tc_core, test_s21_strcspn_3);
  tcase_add_test(tc_core, test_s21_strcspn_4);
  tcase_add_test(tc_core, test_s21_strcspn_5);
  tcase_add_test(tc_core, test_s21_strcspn_6);
  tcase_add_test(tc_core, test_s21_strcspn_7);
  tcase_add_test(tc_core, test_s21_strcspn_8);

  tcase_add_test(tc_core, test_s21_strerror_1);
  tcase_add_test(tc_core, test_s21_strerror_2);
  tcase_add_test(tc_core, test_s21_strerror_3);
  tcase_add_test(tc_core, test_s21_strerror_4);
  tcase_add_test(tc_core, test_s21_strerror_5);

  tcase_add_test(tc_core, test_s21_strlen_1);
  tcase_add_test(tc_core, test_s21_strlen_2);
  tcase_add_test(tc_core, test_s21_strlen_3);
  tcase_add_test(tc_core, test_s21_strlen_4);

  tcase_add_test(tc_core, test_s21_strpbrk_1);
  tcase_add_test(tc_core, test_s21_strpbrk_2);
  tcase_add_test(tc_core, test_s21_strpbrk_3);
  tcase_add_test(tc_core, test_s21_strpbrk_4);
  tcase_add_test(tc_core, test_s21_strpbrk_5);
  tcase_add_test(tc_core, test_s21_strpbrk_6);
  tcase_add_test(tc_core, test_s21_strpbrk_7);
  tcase_add_test(tc_core, test_s21_strpbrk_8);

  tcase_add_test(tc_core, test_s21_strrchr_1);
  tcase_add_test(tc_core, test_s21_strrchr_2);
  tcase_add_test(tc_core, test_s21_strrchr_3);
  tcase_add_test(tc_core, test_s21_strrchr_4);
  tcase_add_test(tc_core, test_s21_strrchr_5);
  tcase_add_test(tc_core, test_s21_strrchr_6);
  tcase_add_test(tc_core, test_s21_strrchr_7);
  tcase_add_test(tc_core, test_s21_strrchr_8);

  tcase_add_test(tc_core, test_s21_strstr_1);
  tcase_add_test(tc_core, test_s21_strstr_2);
  tcase_add_test(tc_core, test_s21_strstr_3);
  tcase_add_test(tc_core, test_s21_strstr_4);
  tcase_add_test(tc_core, test_s21_strstr_5);
  tcase_add_test(tc_core, test_s21_strstr_6);
  tcase_add_test(tc_core, test_s21_strstr_7);
  tcase_add_test(tc_core, test_s21_strstr_8);
  tcase_add_test(tc_core, test_s21_strstr_9);
  tcase_add_test(tc_core, test_s21_strstr_10);
  tcase_add_test(tc_core, test_s21_strstr_11);
  tcase_add_test(tc_core, test_s21_strstr_12);

  tcase_add_test(tc_core, test_s21_strtok_1);
  tcase_add_test(tc_core, test_s21_strtok_2);
  tcase_add_test(tc_core, test_s21_strtok_3);
  tcase_add_test(tc_core, test_s21_strtok_4);
  tcase_add_test(tc_core, test_s21_strtok_5);
  tcase_add_test(tc_core, test_s21_strtok_6);
  tcase_add_test(tc_core, test_s21_strtok_7);
  tcase_add_test(tc_core, test_s21_strtok_8);

  // TASK 2-3

  tcase_add_test(tc_core, test_s21_sprintf);

  // TASK 4

  tcase_add_test(tc_core, test_charVar);
  tcase_add_test(tc_core, test_intVar1);
  tcase_add_test(tc_core, test_doubleVar1);
  tcase_add_test(tc_core, test_exponentialVar_uppercase);
  tcase_add_test(tc_core, test_floatVar);
  tcase_add_test(tc_core, test_generalVar);
  tcase_add_test(tc_core, test_generalVar_uppercase);
  tcase_add_test(tc_core, test_octalVar);
  tcase_add_test(tc_core, test_stringVar);
  tcase_add_test(tc_core, test_unsignedVar);
  tcase_add_test(tc_core, test_hexVar_lowercase);
  tcase_add_test(tc_core, test_hexVar_uppercase);
  tcase_add_test(tc_core, test_pointerVar);
  tcase_add_test(tc_core, test_numVar);
  tcase_add_test(tc_core, test_short_specifier_hi);
  tcase_add_test(tc_core, test_short_specifier_hd);
  tcase_add_test(tc_core, test_short_specifier_ho);
  tcase_add_test(tc_core, test_short_specifier_hu);
  tcase_add_test(tc_core, test_short_specifier_hx_hX);
  tcase_add_test(tc_core, test_long_specifier_li);
  tcase_add_test(tc_core, test_long_specifier_ld);
  tcase_add_test(tc_core, test_long_specifier_lu);
  tcase_add_test(tc_core, test_long_specifier_lX);
  tcase_add_test(tc_core, test_width_and_sign);
  tcase_add_test(tc_core, test_width_star_d);
  tcase_add_test(tc_core, test_width_star_x);
  tcase_add_test(tc_core, test_width_star_f);
  tcase_add_test(tc_core, test_width_star_s);

  // TASK 5

  tcase_add_test(tc_core, s21_test_to_upper);
  tcase_add_test(tc_core, s21_to_upper_normal);
  tcase_add_test(tc_core, s21_to_upper_whith_sign);
  tcase_add_test(tc_core, s21_to_upper_whith_upper);
  tcase_add_test(tc_core, to_upper_1);
  tcase_add_test(tc_core, to_upper_2);
  tcase_add_test(tc_core, to_upper_3);
  tcase_add_test(tc_core, to_upper_4);
  tcase_add_test(tc_core, to_upper_5);
  tcase_add_test(tc_core, to_upper_6);
  tcase_add_test(tc_core, s21_test_to_lower);
  tcase_add_test(tc_core, s21_to_lower_normal);
  tcase_add_test(tc_core, s21_to_lower_sign);
  tcase_add_test(tc_core, s21_to_lower_with_lower);
  tcase_add_test(tc_core, to_lower_1);
  tcase_add_test(tc_core, to_lower_2);
  tcase_add_test(tc_core, to_lower_3);
  tcase_add_test(tc_core, to_lower_4);
  tcase_add_test(tc_core, to_lower_5);
  tcase_add_test(tc_core, to_lower_6);
  tcase_add_test(tc_core, to_lower_7);
  tcase_add_test(tc_core, to_lower_8);
  tcase_add_test(tc_core, to_lower_9);
  tcase_add_test(tc_core, s21_insert_normal);
  tcase_add_test(tc_core, s21_insert_invalid_index);
  tcase_add_test(tc_core, to_insert_6);
  tcase_add_test(tc_core, to_insert_8);
  tcase_add_test(tc_core, to_insert_18);
  tcase_add_test(tc_core, s21_test_trims);
  tcase_add_test(tc_core, s21_trim_normal);
  tcase_add_test(tc_core, s21_trim_sides);
  tcase_add_test(tc_core, s21_trim_empty);
  tcase_add_test(tc_core, to_trim_1);
  tcase_add_test(tc_core, to_trim_2);
  tcase_add_test(tc_core, to_trim_3);
  tcase_add_test(tc_core, to_trim_4);
  tcase_add_test(tc_core, to_trim_5);
  tcase_add_test(tc_core, to_trim_6);
  tcase_add_test(tc_core, to_trim_15);
  tcase_add_test(tc_core, to_trim_16);
  tcase_add_test(tc_core, to_trim_18);
  tcase_add_test(tc_core, to_trim_19);
  tcase_add_test(tc_core, to_trim_20);
  tcase_add_test(tc_core, to_trim_21);
  tcase_add_test(tc_core, to_trim_22);
  tcase_add_test(tc_core, to_trim_23);
  tcase_add_test(tc_core, to_trim_24);
  tcase_add_test(tc_core, to_trim_25);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = string_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
