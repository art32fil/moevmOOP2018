#include <iostream>
#include <Windows.h>

using namespace std;

#include "object.h"
#include "building.h"

int Object::count = 0;
int Object::amount = 0;

ostream& operator<<(ostream& ostr, Object &obj) {
	char symb = obj.getType();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (obj.getCrown()->getArmy() == 'A') {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	}
	else if (obj.getCrown()->getArmy() == 'B') {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	}
	ostr << symb;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return ostr;
}

Object::Object(int x, int y, int hp) : x(x), y(y), hp(hp), id(count++){
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	id = " << id << endl;
	amount++;
}

Object::Object(ifstream& file, const shared_ptr<Crown> crown) : id(count++), crown(crown){
	getCoordsFromFile(file);
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	crown = " << this->crown->getArmy() << endl
		<< "	id = " << id << endl;
	amount++;
}

Object::Object(istream& in, const shared_ptr<Crown> crown) : id(count++), crown(crown) {
	getCoordsFromConsole(in);
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	crown = " << this->crown->getArmy() << endl
		<< "	id = " << id << endl;
	amount++;
}

Object::Object() : id(count++){
	x = y = hp = 0;
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl;
}

Object::~Object(){
	cout << "Destroy Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	crown = " << this->crown->getArmy() << endl
		<< "	id = " << id << endl;
	amount--;
}

void Object::getCoordsFromFile(ifstream& file) {
	file >> x >> y >> hp;
}

void Object::getCoordsFromConsole(istream& in) {
	in >> x >> y >> hp;
}

void Object::getDamage(int damage) {
	hp -= damage;
}

// передается сначала y потом x, соответственно i и j
bool Object::checkObjCoords(int yCoord, int xCoord) {
	if (xCoord == x && yCoord == y) return true;
	return false;
}

int& Object::getX() {
	return x;
}

int& Object::getY() {
	return y;
}

void Object::changeX(int i) {
	x = x + i;
}

void Object::changeY(int i) {
	y = y + i;
}

int Object::getHp() {
	return hp;
}

int Object::getId() {
	return id;
}

char& Object::getType() {
	return type;
}

const shared_ptr<Crown>& Object::getCrown() {
	return crown;
}