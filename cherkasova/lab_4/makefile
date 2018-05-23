#all: iter list object warrior building field main 
#	g++ -o play main.cpp -std=c++17 -g
all: main.o field.hpp.gch warrior.hpp.gch building.hpp.gch object.hpp.gch iter.hpp.gch list.hpp.gch  
	g++ -o play main.o field.hpp.gch warrior.hpp.gch building.hpp.gch object.hpp.gch iter.hpp.gch list.hpp.gch -std=c++17 -g
clean:
	rm -rf play *.hpp.gch
	rm -rf play *.o	
	rm *out
main.o: main.cpp
	g++ -c -o main.o main.cpp -std=c++17
crown.hpp.gch: crown.hpp
	g++ -c -o crown.hpp.gch crown.hpp -std=c++17
field.hpp.gch: field.hpp
	g++ -c -o field.hpp.gch field.hpp -std=c++17
object.hpp.gch: object.hpp
	g++ -c -o object.hpp.gch object.hpp -std=c++17
building.hpp.gch: building.hpp
	g++ -c -o building.hpp.gch building.hpp -std=c++17
warrior.hpp.gch: warrior.hpp
	g++ -c -o warrior.hpp.gch warrior.hpp -std=c++17
list.hpp.gch: list.hpp 
	g++ -c -o list.hpp.gch list.hpp -std=c++17
iter.hpp.gch: iter.hpp
	g++ -c -o iter.hpp.gch iter.hpp -std=c++17
