#include "object.h"


Object::Object(int x, int y, int hp) :x(x), y(y), hp(hp) {
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "Object."<<endl;
}

Object::Object(ifstream& f) {
	if (!f.is_open()) {
		cout << "File can't be opened!" << endl;
		exit(EXIT_FAILURE);
		system("pause");
	}
	f >> x >> y >> hp;
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "Object." << endl;
}

Object::Object() {
	x = y = hp = 0;
}

Object::~Object() {
	cout << "~Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "~Object." << endl;

}
int Object:: damage(int dmg){
	hp -= dmg;
	return hp;
}

bool Object::isObject(int x1, int y1) {
	if (x == x1 && y == y1) return true;
	return false;
}

bool Object::isDead() {
	if (hp<=0) return true;
	return false;
}
