all: main.o main.cpp
	g++ main.o -o out -static -std=c++11
main.o: main.cpp list.h
	g++ main.cpp -c -o main.o -static -std=c++11