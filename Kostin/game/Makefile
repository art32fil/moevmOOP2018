PUTH = ../vector/

all: game

game : main.o
	g++ main.o	-o game

main.o : main.cpp Battlefield.hpp Object.hpp  $(PUTH)iterator.hpp  $(PUTH)my_vector.hpp
	g++ -Wall -c 	main.cpp	-std=c++17

clean :
	rm -rf *.o	game
