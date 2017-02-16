
all: test

test: test.cpp bst.hpp
	g++ -std=c++11 -Wall -I /usr/include/gtest -pthread -o test $< /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a
