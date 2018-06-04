all: play

play : main.o
	g++ main.o -o play

main.o : main.cpp Battlefield.hpp Object.hpp  iterator.hpp  list.hpp Crown.hpp Warrior.hpp Building.hpp
	g++ -c main.cpp	-std=c++17


