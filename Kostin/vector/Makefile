all: my_vector

my_vector : main.o
	g++ main.o	-o my_vector

main.o : main.cpp iterator.hpp my_vector.hpp
	g++ -Wall -c 	main.cpp	-std=c++17

clean :
	rm -rf *.o	my_vector
