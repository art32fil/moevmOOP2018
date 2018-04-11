PUTH = ../vector/

all: game2

game2 : main.o
	g++ main.o	-o game2

main.o : main.cpp Battlefield.hpp Object.hpp Crown.hpp  $(PUTH)iterator.hpp  $(PUTH)my_vector.hpp
	g++ -Wall -c 	main.cpp	-std=c++17

clean :
	rm -rf *.o	game3
