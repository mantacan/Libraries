CC=gcc
CFLAGS=-ftest-coverage -fprofile-arcs -lcheck -lm
AFLAGS=-std=c11 -Wall -Werror -Wextra
TESTS=test_matrix.c
NEW_TESTS=tests.c
T_OUT=tests
G_OUT=gcovreport

all: custom_matrix.a

test:
	$(CC) $(AFLAGS) *.c $(CFLAGS) -o tests
	./$(T_OUT)

custom_matrix.a: custom_matrix.c
	$(CC) $(AFLAGS) -c $^
	ar rc $@ *.o
	rm *.o
	ranlib $@

gcov_report: test
	./tests
	lcov -t "$(G_OUT)" -o $(G_OUT).info -c -d .
	genhtml -o report $(G_OUT).info
	open report/index.html || xdg-open report/index.html || sensible-browser report/index.html || x-www-browser report/index.html || gnome-open report/index.html

clean:
	rm -rf *.o *.a tests custom_matrix *.gcda *.gcno *.info ./out
	rm -rf report test.dSYM test

