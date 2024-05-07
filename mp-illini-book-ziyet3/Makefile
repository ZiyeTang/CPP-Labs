CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec

bin/exec: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec

clean:
	rm -fr bin/*
