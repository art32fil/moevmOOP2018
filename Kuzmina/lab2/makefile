hello: main.o list.o Field.o Obj.o link_all
main.o: main.cpp Field.hpp Obj.hpp
	g++ -c main.cpp
list.o: list.cpp list.hpp
	g++ -c list.cpp
Field.o: Field.cpp Field.hpp Crown.hpp
	g++ -c Field.cpp
Obj.o: Obj.cpp Obj.hpp Crown.hpp
	g++ -c Obj.cpp
link_all: main.o list.o Obj.o Field.o
	g++ main.o list.o Obj.o Field.o -o out