all: game

game: main.o  list.o Object.o Crown.o battlefield.o
	g++ main.o Crown.o list.o Object.o  battlefield.o -o game -std=c++17

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


clean:
	rm -rf *.o hello
	rm -rf game
