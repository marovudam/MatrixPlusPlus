CXX=g++
STD=-std=c++17
TEST_FLAGS=-lgtest -lgtest_main
COVERAGE=--coverage
SRC=matrix_oop.cc
OBJS=matrix_oop.o
TESTS=matrix_oop_tests.cc

all: matrix_oop.a

style:
	clang-format -style=Google -i *.cc *.h

matrix_oop.a:
	$(CXX) -c $(SRC) -o $(OBJS) $(STD)
	ar rcs matrix_oop.a $(OBJS)
	ranlib matrix_oop.a

clean:
	-rm matrix_oop.a *.o *.out test *.gch *.gcda *.gcno *.info
	-rm -r res

test: clean
	$(CXX) $(STD) $(SRC) $(TESTS) -o test $(TEST_FLAGS)
	- ./test

leak: test
	leaks -atExit -- ./test

coverage:
	$(CXX) $(TESTS) $(TEST_FLAGS) -c
	g++ -c $(SRC) -o $(OBJS) $(STD) $(COVERAGE)
	ar rcs matrix_oop.a $(OBJS)
	ranlib matrix_oop.a
	$(CXX) $(STD) matrix_oop.a matrix_oop_tests.o $(COVERAGE) $(TEST_FLAGS) -o test
	- ./test
	lcov -c --directory . -o ./coverage.info --no-external
	genhtml coverage.info --output-directory=res
