CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -pedantic -std=c11

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	LIBS=-lcheck -lm -l
else
	LIBS=-lcheck
endif

all: custom_math.a

custom_math.a: custom_math.c custom_math.h
	$(CC) $(CFLAGS) custom_math.c -o custom_math.o
	ar rc custom_math.a custom_math.o
	ranlib custom_math.a

test: tests/main.c custom_math.a
	$(CC) $(CFLAGS) tests/main.c -o main.o
	$(CC) --coverage main.o custom_math.c -o custom_math_tests $(LIBS)
	./custom_math_tests

gcov_report: test
	gcov ./custom_math_tests
	lcov -c -d . -o gcov.info
	genhtml gcov.info -o gcov_report
	open gcov_report/index.html

clean:
	rm -rf *.o *.a *.gcno *.gcda *.html *.css *.info gcov_report/ custom_math custom_math_tests

rebuild: clean all
