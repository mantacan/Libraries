#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *data = (const unsigned char *)str;
  unsigned char symbol = (unsigned char)c;

  void *result = ((void *)0);
  int flag = 0;
  for (s21_size_t i = 0; flag == 0 && i < n; i++) {
    if (data[i] == symbol) {
      result = (void *)(data + i);
      flag = 1;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1;
  const unsigned char *s2;
  s1 = str1;
  s2 = str2;
  char count = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      count = s1[i] - s2[i];
      break;
    }
  }
  return count;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest != s21_NULL && src != NULL) {
    char *copied = (char *)dest;
    const char *sourse = (const char *)src;

    while (n--) {
      *copied++ = *sourse++;
    }
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  char *destin = (char *)str;
  while (n--) {
    *destin++ = (char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *begin = dest;

  while (*begin != '\0') {
    begin++;
  }
  while (n-- > 0 && *src != '\0') {
    *begin++ = *src++;
  }
  *begin = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  while (*str != c && *str) str++;
  return *str == c ? (char *)str : s21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  if (str1 && str2) {
    s21_size_t i = 0;
    while (n > 0 && str1[i] && str1[i] == str2[i]) {
      i++;
      n--;
    }
    if (n > 0) {
      result = (char)str1[i] - (char)str2[i];
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (n > 9223372036854775807) {
    return s21_NULL;
  }
  s21_size_t src_len = s21_strlen(src);
  for (s21_size_t idx = 0; idx < n; idx++) {
    if (idx < src_len) {
      dest[idx] = src[idx];
    } else {
      dest[idx] = '\0';
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *first_occur = s21_strpbrk(str1, str2);
  return first_occur != NULL ? (s21_size_t)(first_occur - str1)
                             : s21_strlen(str1);
}

char *s21_strerror(int errnum) {
  char *result = s21_NULL;
  char *errors[] = ERR_LIST;
  static char buf[100];
  if (errnum >= 0 && errnum < N) {
    result = errors[errnum];
  } else {
    if (!OS) {
      char *prefix = "Unknown error ";
      s21_sprintf(buf, "%s%d", prefix, errnum);
    } else if (OS) {
      char *prefix = "Unknown error: ";
      s21_sprintf(buf, "%s%d", prefix, errnum);
    }
  }
  return result == s21_NULL ? buf : result;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  if (str != NULL) {
    for (length = 0; *str; str++) {
      length++;
    }

  } else {
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  int flag = 0;
  for (; *str1 && !flag; str1++) {
    for (const char *ptr2 = str2; *ptr2; ptr2++) {
      if (*str1 == *ptr2) {
        result = (char *)str1;
        flag = 1;
        break;
      }
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL) return s21_NULL;
  char *result = s21_NULL;
  for (; *str; str++) {
    if (*str == (char)c) result = (char *)str;
  }
  if (!c) result = (char *)str;
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == NULL || needle == NULL) return (char *)s21_NULL;
  char *result = s21_NULL, *needle_ptr = (char *)needle,
       *potential_result = s21_NULL;
  if (!(*needle)) {
    result = (char *)haystack;
  } else if (!(*haystack)) {
  } else {
    int flag = 0;
    for (; !flag;) {
      for (; (*haystack != *needle) && *haystack; haystack++)
        ;
      if (*haystack == *needle) potential_result = (char *)haystack;
      while (*haystack == *needle_ptr && (*haystack && *needle_ptr)) {
        haystack++;
        needle_ptr++;
      }
      if (!(*needle_ptr)) {
        result = potential_result;
        flag = 1;
      }
      if (!(*haystack)) flag = 1;
      needle_ptr = (char *)needle;
    }
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = s21_NULL;
  if (str == s21_NULL && last != s21_NULL) str = last + 1;
  if (str != s21_NULL) {
    char *delim_ptr = s21_NULL;
    for (; *str && (delim_ptr = s21_strpbrk(str, delim)) == str; str++)
      ;
    if (*str == '\0') {
      str = s21_NULL;
      last = s21_NULL;
    } else {
      last = delim_ptr;
      if (last != s21_NULL) *last = '\0';
    }
  }
  return str;
}

int s21_strcmp(const char *str1, const char *str2) {
  const unsigned char *c1 = (const unsigned char *)str1;
  const unsigned char *c2 = (const unsigned char *)str2;

  while (*c1 && *c1 == *c2) ++c1, ++c2;

  return *(const unsigned char *)c1 - *(const unsigned char *)c2;
}

char *s21_strcpy(char *destination, const char *source) {
  char *dest_ptr = destination;

  while ((*dest_ptr++ = *source++) != '\0')
    ;

  return destination;
}

char *s21_strcat(char *destination, const char *source) {
  while (*destination != '\0') {
    destination++;
  }

  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }

  *destination = '\0';

  return destination;
}