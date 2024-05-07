CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug 
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null

exec: bin/exec
tests: bin/tests

bin/exec : ./includes/db.hpp ./src/db.cc ./includes/db_table.hpp ./src/db_table.cc ./src/driver.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/db.cc ./src/db_table.cc ./src/driver.cc -o ./bin/exec

bin/tests : ./includes/db.hpp ./src/db.cc ./includes/db_table.hpp ./src/db_table.cc ./tests/tests.cc
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(EXTRA_CXX_FLAGS) ./src/db.cc ./src/db_table.cc ./tests/tests.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
