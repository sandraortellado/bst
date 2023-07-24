#
# Makefile for Binary Search Tree
#
# Homework 3
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 

hw3: hw3.o BinarySearchTree.o
	${CXX} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf hw3 *.o *.dSYM