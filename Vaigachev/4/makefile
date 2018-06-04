all: game

game: main.o  list.o Object.o Crown.o battlefield.o Warior.o Building.o Swordsman.o Magikan.o
	g++ main.o Crown.o list.o Object.o  battlefield.o Warior.o Building.o Swordsman.o Magikan.o -o game -std=c++17

main.o: main.cpp
	g++ -c main.cpp -std=c++17

battlefield.o: battlefield.cpp battlefield.h
	g++ -c battlefield.cpp -std=c++17

list.o: list.cpp list.h
	g++ -c list.cpp -std=c++17

Object.o: Object.cpp Object.h
	g++ -c Object.cpp -std=c++17

Crown.o: Crown.cpp Crown.h
	g++ -c Crown.cpp -std=c++17

Warior.o: Warior.cpp Warior.h
	g++ -c Warior.cpp -std=c++17

Building.o: Building.cpp Building.h
	g++ -c Building.cpp -std=c++17

Swordsman.o: Swordsman.cpp Swordsman.h
	g++ -c Swordsman.cpp -std=c++17

Magikan.o: Magikan.cpp Magikan.h
	g++ -c Magikan.cpp -std=c++17

clean:
	rm -rf *.o hello
	rm -rf game
	rm -rf *.vcxp*
