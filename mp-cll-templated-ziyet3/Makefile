CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/circular-linked-list.cc ./includes/circular-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/circular-linked-list.cc -o $@

bin/tests: ./tests/tests.cc ./src/circular-linked-list.cc ./includes/circular-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/circular-linked-list.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 
