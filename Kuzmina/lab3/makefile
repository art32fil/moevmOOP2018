hello: main.o list.o Field.o Obj.o warrior.o building.o link_all
main.o: main.cpp Field.hpp Obj.hpp warrior.hpp
	g++ -c main.cpp -std=c++11
list.o: list.cpp list.hpp
	g++ -c list.cpp -std=c++11
Field.o: Field.cpp Field.hpp warrior.hpp building.hpp
	g++ -c Field.cpp -std=c++11
Obj.o: Obj.cpp Obj.hpp
	g++ -c Obj.cpp -std=c++11
warrior.o: warrior.cpp warrior.hpp
	g++ -c warrior.cpp -std=c++11
building.o: building.cpp building.hpp
	g++ -c building.cpp -std=c++11
link_all: main.o list.o Obj.o warrior.o building.o Field.o
	g++ main.o list.o Obj.o warrior.o building.o Field.o -o out -std=c++11