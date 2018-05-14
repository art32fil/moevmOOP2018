#include <iostream>
#include "object.h"

using namespace std;

Object::Object(int x, int y, int hp) : x(x), y(y), hp(hp){
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl;
}

Object::Object(ifstream& file){
	getCoordsFromFile(file);
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl;
}

Object::Object() {
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
		<< "	hp = " << hp << endl;
}

void Object::getCoordsFromFile(ifstream& file) {
	file >> x >> y >> hp;
}

void Object::getDamage(int damage) {
	hp -= damage;
}


// передается сначала y потом x, соответственно i и j
bool Object::checkObjCoords(int yCoord, int xCoord) {
	if (xCoord == x && yCoord == y) return true;
	return false;
}

int Object::getX() {
	return x;
}

int Object::getY() {
	return y;
}

int Object::getHp() {
	return hp;
}