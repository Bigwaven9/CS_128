CXX=clang++
CXX_FLAGS=-std=c++20 -g -Iincludes -fstandalone-debug -O0 -Wall -Wextra -Werror

main: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := main
.PHONY: clean

clean:
	rm -f bin/*