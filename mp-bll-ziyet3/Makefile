CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -gdwarf-4 -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/branched-linked-list.cc ./includes/branched-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) ./src/driver.cc ./src/branched-linked-list.cc -o $@

bin/tests: ./tests/tests.cc ./src/branched-linked-list.cc ./includes/branched-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./tests/tests.cc ./src/branched-linked-list.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
