#pragma once

#include "crown.h"

class Obj
{
protected:
	int X, Y, HP, ID;
	static int COUNT;
	shared_ptr <Crown> CLR;
public:
	Obj(ifstream&, const shared_ptr<Crown>&);
	~Obj();

	bool damage(int);
	bool checkobj(int, int);
	bool alive();

	int &Get_C() { return COUNT; };
	int &Get_X() { return X; }
	int &Get_Y() { return Y; }

	void print();

	friend ostream& operator<< (ostream& out, Obj &A)
	{
		A.print();
		return out;
	}

	friend ifstream& operator>> (ifstream& fin, Obj &A)
	{
		fin >> A.X >> A.Y >> A.HP;
		return fin;
	}
};