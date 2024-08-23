CC=gcc
CFLAGS=-ftest-coverage -fprofile-arcs -lcheck -lm #-lsubunit
AFLAGS=-std=c11 -Wall -Werror -Wextra
TESTS=test_s21_string.c
NEW_TESTS=tests.c
T_OUT=tests
G_OUT=gcovreport

all: s21_string.a

test:
	$(CC) $(AFLAGS) *.c $(CFLAGS) -o tests
	./$(T_OUT)

s21_string.a: s21_string.c s21_sscanf.c s21_sprintf.c s21_bonus_string.c
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
	rm -rf *.o *.a tests s21_string *.gcda *.gcno *.info ./out
	rm -rf report test.dSYM


debug: clean_debud
	gcc -std=c11 -g -Wall -Werror -Wextra s21_string.c s21_sscanf.c s21_sprintf.c sprintf_test.c -o debug && ./debug

clean_debud:
	rm -rf debug

style:
	clang-format -n *.c *.h

stylecor:
	clang-format -i *.c *.h
