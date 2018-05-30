#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <string>
#include "list.h"
#include "object.h"
#include "warrior.h"
#include "building.h"

using namespace std;

class Field {
public:
	List<Object*> armyA;
	weak_ptr<Crown> clrA;
	List<Object*> armyB;
	weak_ptr<Crown> clrB;
	int x_size, y_size;
	int size_A, size_B;

	Field(ifstream &f);
	~Field();
	void getA(ifstream&f, const shared_ptr<Crown>& color);
	void getB(ifstream&f, const shared_ptr<Crown>& color);
	void paint();
	bool isIt(string clr,int x1, int y1);
	bool attack(string clr, int x1, int y1, int x2, int y2);
	void move(string clr,int x, int y,string dir);
	bool isArmyA();
	bool isArmyB();
	friend istream& operator >>(istream& s, Field& fld);
	friend ostream& operator <<(ostream& s, const Field& fld);
};
#endif
