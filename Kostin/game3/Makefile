PUTH = ../vector/

all: game3

game3 : main.o
	g++ main.o	-o game3

main.o : main.cpp Battlefield.hpp Object.hpp Crown.hpp Warrior.hpp Building.hpp  $(PUTH)iterator.hpp  $(PUTH)my_vector.hpp
	g++ -Wall -c 	main.cpp	-std=c++17

clean :
	rm -rf *.o	game3
