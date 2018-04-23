#include "object.h"

Obj::Obj(ifstream &fin)
{
	fin >> X >> Y >> HP;
	cout << " Object:\n";
	cout << "\t x = " << X << endl;
	cout << "\t y = " << Y << endl;
	cout << "\t hp = " << HP << endl;
	cout << " Object.\n";
}


Obj::~Obj()
{
	cout << " ~Object:\n";
	cout << "\t x = " << X << endl;
	cout << "\t y = " << Y << endl;
	cout << "\t hp = " << HP << endl;
	cout << " ~Object.\n";
}


void Obj::damage(int D)
{
	HP -= D;
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