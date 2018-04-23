#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class Obj
{
	int X, Y, HP;
public:
	Obj(ifstream&);
	~Obj();

	void damage(int);
	bool checkobj(int, int);
	bool alive();

	int &get_x() { return X; };
	int &get_y() { return Y; };
};