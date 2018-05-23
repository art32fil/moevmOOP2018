DIRECTORY = ../vector/

#wildcard for automaticaly include new headers file
HEADER = $(wildcard *.hpp) #$(DYRECTORy)iterator.hpp  $(DYRECTORy)my_vector.hpp

all : game4

game4 : main.o
	g++ main.o -o game4 		-std=c++17
#precompiled header
HEADER_GCH : $(HEADER)
	g++ $(HEADER)	-std=c++17

main.o : main.cpp HEADER_GCH
	@echo "$(HEADER)"
	g++ -Wall -c main.cpp		-std=c++17

clean :
	rm -rf *.o *.gch game4
