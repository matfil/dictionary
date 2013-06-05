CC=g++-4.7
FLAGS=-std=c++11 -ggdb

all:test

program:main.o preprocess.o
	$(CC) $(FLAGS) -o program main.o preprocess.o

main.o:main.cpp RBtree.hpp compare.hpp preprocess.h
	$(CC) $(FLAGS) -c main.cpp

preprocess.o: preprocess.cpp RBtree.hpp compare.hpp preprocess.h
	$(CC) $(FLAGS) -c preprocess.cpp

clean:
	rm -f program *.o
