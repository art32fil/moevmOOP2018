#include "object.h"

int Obj::COUNT = 0;

Obj::Obj(ifstream &fin, const shared_ptr<Crown> &color): ID(++COUNT), CLR(color)
{
	fin >> X >> Y >> HP;
	cout << " Object:\n";
	cout << "\t id = " << ID << endl;
	cout << "\t x = " << X << endl;
	cout << "\t y = " << Y << endl;
	cout << "\t hp = " << HP << endl;
	cout << " Object.\n";
}


Obj::~Obj()
{
	COUNT--;
	cout << " ~Object:\n";
	cout << "\t id = " << ID << endl;
	cout << "\t x = " << X << endl;
	cout << "\t y = " << Y << endl;
	cout << "\t hp = " << HP << endl;
	cout << " ~Object.\n";
}


bool Obj::damage(int D)
{
	HP -= D;
	if (alive())
		return false;
	else
		return true;
}


bool Obj::checkobj(int x, int y)
{
	if (X == x && Y == y)
		return true;
	else
		return false;
}


bool Obj::alive()
{
	if (HP > 0)
		return true;
	else
		return false;
}

void Obj::print()
{
	cout << X << " " << Y << " " << HP << endl;
}