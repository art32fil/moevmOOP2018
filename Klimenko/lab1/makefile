hello: main.o field.o unit.o link_all
main.o main.cpp container.h field.h unit.h
	g++ -c -std=c++11 main.cpp
field.o: field.cpp field.h container.h
	g++ -c -std=c++11 field.cpp
unit.o: unit.cpp unit.h
	g++ -c -std=c++11 unit.cpp
link_all: main.o field.o unit.o
	g++ -std=c++11 main.o field.o unit.o -o out