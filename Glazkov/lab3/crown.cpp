#include <iostream>

using namespace std;

#include "crown.h"

Crown::Crown(char army) : army(army){
	cout << "Crown" << endl
		<< "	army = " << army << endl;
}

Crown::~Crown() {
	cout << "Destroy Crown" << endl
		<< "	army = " << army << endl;
}

char Crown::getArmy() {
	return army;
}