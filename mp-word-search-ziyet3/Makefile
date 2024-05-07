CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/driver.cc src/CharPositions.cc src/WordLocation.cc src/WordSearchSolver.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: tests/tests.cc src/CharPositions.cc src/WordLocation.cc src/WordSearchSolver.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean tests

clean:
	rm -rf bin/*
