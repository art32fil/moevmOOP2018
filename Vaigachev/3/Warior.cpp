#include "Warior.h"

using namespace std;


Warior::Warior(ifstream& fin, const shared_ptr<Crown> t): Object(fin,t)
{
	fin >> force;
	cout << "Warior : START:" << endl;
	cout << "	force = " << force << endl;
	cout << "Warior: END." << endl << endl;
}




Warior::~Warior()
{
	cout << endl;
	cout << "~Warior : START:" << endl;
	cout << "	force = " << force << endl;
	cout << "~Warior: END." << endl ;
}
/*
istream &operator>>(istream &in, Warior &ob) {
	in >> (Object&) ob >> ob.force;
	return in;
}*/

ostream &operator<<(ostream &out, Warior &ob) {
	if (ob.show_team() == 1) // 1
		out << "\033[32m";
	if (ob.show_team() == 2) // 0
		out << "\033[31m";
	out << " W " << "\033[0m";
	return out;
}

Warior* Warior::move(char option) {
	switch (option)
	{
	case('w'):
		pos.y--;
		break;
	case('d'):
		pos.x++;
		break;
	case('s'):
		pos.y++;
		break;
	case('a'):
		pos.x--;
		break;
	default:
		cerr << "wrong command! " << option << endl;
		break;
	}
	return this;
}

int Warior::give_force()
{
	return force;
}
