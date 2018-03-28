#pragma once
#include <iostream>
//#include <windows.h>
#include "list.h"
#include "object.h"
using namespace std;

class Field {
	List<Object> armyA;
	List<Object> armyB;
	int x_size, y_size;
	int size_A, size_B;
public:
	Field(ifstream &f);
	~Field();
	void getArmies(ifstream& f);
	void paint();
	bool isIt(int x1, int y1);
	void attack(int x,int y,int dmg);
};
