link_all: main.o field.o object.o 
	g++ -std=c++11 main.o field.o object.o -o out
main.o: main.cpp field.h list.h object.h crown.h
	g++ -std=c++11 -c main.cpp 
field.o: field.cpp list.h field.h object.h
	g++ -std=c++11 -c field.cpp
object.o: object.cpp object.h crown.h
	g++ -std=c++11 -c object.cpp

