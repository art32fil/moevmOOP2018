all: game

game: main.o field.o list.o Object.o
	g++ main.o field.o list.o Object.o -o game -std=c++17

main.o: main.cpp
	g++ -c main.cpp -std=c++17

battlefield.o: field.cpp
	g++ -c field.cpp -std=c++17

list.o: list.cpp
	g++ -c list.cpp -std=c++17

Object.o: Object.cpp
	g++ -c Object.cpp -std=c++17
clean:
	rm -rf *.o hello
	rm -rf game