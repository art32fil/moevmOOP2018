all: game

game: main.o  list.o Object.o Crown.o battlefield.o Warior.o Building.o Swordsman.o Magikan.o
	g++ main.o Crown.o list.o Object.o  battlefield.o Warior.o Building.o Swordsman.o Magikan.o -o game -std=c++17

main.o: main.cpp
	g++ -c main.cpp -std=c++17

battlefield.o: battlefield.cpp
	g++ -c battlefield.cpp -std=c++17

list.o: list.cpp
	g++ -c list.cpp -std=c++17

Object.o: Object.cpp
	g++ -c Object.cpp -std=c++17

Crown.o: Crown.cpp
	g++ -c Crown.cpp -std=c++17

Warior.o: Warior.cpp
	g++ -c Warior.cpp -std=c++17

Building.o: Building.cpp
	g++ -c Building.cpp -std=c++17

Swordsman.o: Swordsman.cpp
	g++ -c Swordsman.cpp -std=c++17

Magikan.o: Magikan.cpp
	g++ -c Magikan.cpp -std=c++17

clean:
	rm -rf *.o hello
	rm -rf game
	rm -rf *.vcxp*
