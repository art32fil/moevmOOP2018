all: game

game: main.o  list.o Object.o Crown.o field.o Warrior.o Building.o
	g++ main.o Crown.o list.o Object.o  field.o Warrior.o Building.o -o game -std=c++17

main.o: main.cpp
	g++ -c main.cpp -std=c++17

battlefield.o: field.cpp
	g++ -c field.cpp -std=c++17

list.o: list.cpp
	g++ -c list.cpp -std=c++17

Object.o: Object.cpp
	g++ -c Object.cpp -std=c++17

Crown.o: Crown.cpp
	g++ -c Crown.cpp -std=c++17

Warior.o: Warrior.cpp
	g++ -c Warrior.cpp -std=c++17

Building.o: Building.cpp
	g++ -c Building.cpp -std=c++17

clean:
	rm -rf *.o hello
	rm -rf game
	rm -rf *.vcxp*