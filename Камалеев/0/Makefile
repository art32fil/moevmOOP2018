root: main.o list.o link_all
main.o: main.cpp list.h
	g++ -c main.cpp -std=c++17
list.o: list.cpp list.h
	g++ -c list.cpp -std=c++17
link_all: main.o list.o
	g++ main.o list.o -o out
