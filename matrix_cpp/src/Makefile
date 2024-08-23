CC=gcc
AFLAGS= -std=c++17 -Wall -Werror -Wextra -lm -lstdc++ -lgtest #-fsanitize=address
TESTS=test_matrix.c
NEW_TESTS=tests.c
T_OUT=tests
G_OUT=gcovreport

all: s21_matrix_oop.a

test:
	$(CC) $(AFLAGS) *.cpp -o tests
	./$(T_OUT)

s21_matrix_oop.a: s21_matrix.cpp s21_oop_function.cpp
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
	rm -rf *.o *.a tests s21_matrix_oop *.gcda *.gcno *.info ./out
	rm -rf report test.dSYM

