hello: main.o list.o link_all
main.o: main.cpp list.h
	g++ -c main.cpp
list.o: list.cpp list.h
	g++ -c list.cpp
link_all: main.o list.o
	g++ main.o list.o -o out