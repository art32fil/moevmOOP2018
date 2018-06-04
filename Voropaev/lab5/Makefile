ink_all: lab

lab: main.o
	g++ main.o -o lab
main.o: main.cpp battlefield.h object.h crown.h list.h iter.h warrior.h building.h swordsman.h magician.h
		g++ -Wall -c main.cpp -std=c++11
clean:
	rm -rf *.o lab
