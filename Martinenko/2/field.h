#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include "list.h"
#include "object.h"
using namespace std;

class Field {
public:
	List<Object> armyA;
	weak_ptr<Crown> clrA;
	List<Object> armyB;
	weak_ptr<Crown> clrB;
	int x_size, y_size;
	int size_A, size_B;

	Field(ifstream &f);
	~Field();
	//void getArmies(ifstream& f);
	void getA(ifstream&f, const shared_ptr<Crown>& color);
	void getB(ifstream&f, const shared_ptr<Crown>& color);
	void paint();
	bool isIt(int x1, int y1);
	void attack(int x,int y,int dmg);
	friend istream& operator >>(istream& s, Field& fld);
	friend ostream& operator <<(ostream& s, const Field& fld);
};
#endif
