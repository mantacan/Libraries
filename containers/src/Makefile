CC=gcc
CXX_FLAGS= -Wall -Werror -Wextra -O2 -ftree-vectorize -std=c++17 
COMP_FLAG=-c 
CXX_FLAGS_MEMORY_TEST= -fsanitize=leak -fsanitize=address -fsanitize=undefined \
	-fsanitize=unreachable -fno-sanitize-recover \
	-fstack-protector
TEST_FLAGS=-g --coverage

OS=$(shell uname -s)
TEST_LIBS=-lgcov -lgtest -lgtest_main -lpthread -lstdc++ 
#-lboost_stacktrace_backtrace -ldl -lboost_stacktrace_backtrace
OPEN=open

VALGRIND_FLAGS = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes \
	 --leak-check=full --leak-resolution=med --track-fds=yes --tool=memcheck \
	 --show-leak-kinds=all -s


COMPILE_TARGET_TEST= $(wildcard tests/*test*.cpp)
#LINKING_TARGET_TEST=s21_array_test.o s21_multiset_test.o

NAME_TEST_EXE=test


ifeq ($(OS), Linux)
	detected_Linux:=$(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')

	ifeq ($(detected_Linux), Arch)
	TEST_LIBS+= -lm
	OPEN=xdg-open
	endif

	ifeq ($(detected_Linux), Ubuntu)
	TEST_LIBS+=-pthread -lm -lpthread
	OPEN=xdg-open
	endif

endif

.PHONY: test

all: clean gcov_report s21_clang

test: 
	$(CC) $(CXX_FLAGS)  $(CXX_FLAGS_MEMORY_TEST)  \
	 	$(COMPILE_TARGET_TEST) $(TEST_FLAGS) -o $(NAME_TEST_EXE) $(TEST_LIBS)
	./$(NAME_TEST_EXE)

gcov_report: test
	lcov -t "test" -o test.info -c -d . --rc geninfo_unexecuted_blocks=1 --ignore-errors 'mismatch,unused' \
		--exclude c++/13/ --exclude gtest/ --exclude string_fortified.h 
	genhtml -o report test.info
	$(open) report/index.html

# all: s21_clang-format s21_list s21_queue clean
# 
# s21_list:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/list_tests.cpp -o list_tests
# 	./list_tests
# 	rm list_tests
# 
# s21_queue:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/queue_tests.cpp -o queue_tests
# 	./queue_tests
# 	rm queue_tests
# 
# s21_map:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/map_tests.cpp -o map_tests
# 	./map_tests
# 	rm map_tests
# 
# s21_set:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/set_tests.cpp -o set_tests
# 	./set_tests
# 	rm set_tests
# 
# s21_stack:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/stack_tests.cpp -o stack_tests
# 	./stack_tests
# 	rm stack_tests
# 
s21_map:
	$(CC) $(CXX_FLAGS)  $(CXX_FLAGS_MEMORY_TEST)  \
	 	tests/s21_map_tests.cpp $(TEST_FLAGS) -o $(NAME_TEST_EXE) $(TEST_LIBS)
	./$(NAME_TEST_EXE)

# 
# s21_array:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/s21_array_tests.cpp -o array_tests
# 	./array_tests
# 	rm array_tests
# 
# s21_multiset:
# 	$(CC) $(AFLAGS) $(BFLAGS) $(GCOV) ./tests/s21_multiset_tests.cpp -o multiset_tests
# 	./multiset_tests
# 	rm multiset_tests
# 
# 
# rep_list: s21_list
# 	lcov -t "tests" -o test.info -c -d . --rc geninfo_unexecuted_blocks=1 --ignore-errors 'mismatch,unused' \
# 		--exclude c++/13/ --exclude gtest/ --exclude string_fortified.h --exclude *tests*.cpp
# 	genhtml -o report test.info
# 	#open report/index.html || xdg-open report/index.html || sensible-browser report/index.html || x-www-browser report/index.html || gnome-open report/index.html
# 
# 

valgrind: 
	$(CC) $(CXX_FLAGS) $(TEST_FLAGS) $(COMPILE_TARGET_TEST) \
		 -o $(NAME_TEST_EXE) $(TEST_LIBS)
		 
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./$(NAME_TEST_EXE)

s21_clang:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i list/*.h list/*.hpp queue/*.h queue/*.hpp array/*.* multiset/*.*
	clang-format -i tests/*.cpp
	clang-format -i s21_containers.h
	rm .clang-format

clean:
	rm -f $(NAME_TEST_EXE)
	rm -f *.o
	rm -f *.a
	rm -rf report/
	rm -f *.gcda *.gcno *.info valgrind.txt

