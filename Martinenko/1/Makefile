link_all: main.o field.o list.o object.o 
	g++ -std=c++11 main.o field.o list.o object.o -o out
main.o: main.cpp field.h list.h object.h
	g++ -std=c++11 -c main.cpp 
field.o: field.cpp list.h field.h
	g++ -std=c++11 -c field.cpp
list.o: list.cpp list.h
	g++ -std=c++11 -c list.cpp
object.o: object.cpp object.h
	g++ -std=c++11 -c object.cpp

