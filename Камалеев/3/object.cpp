#include "object.h"

int Object::count = 0;
int Object::amount = 0;

Object::Object(ifstream& fl,const shared_ptr<Crown>& clr):id(count++),crown(clr) { // инициализация объекта из файла
	if (!fl.is_open()) {
		cout << "There are no file in directory!" << endl;
		exit(1);
		system("pause");
	}
	fl >> x >> y >> hp;
	cout << "Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "	crown = " << crown->Get_Color() << endl;
	cout << "	id = " << id << endl;
	cout << "Object." << endl;
	amount++;
}

Object::~Object() { // говорящий деструктор
	cout << "~Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "	crown = " << crown->Get_Color() << endl;
	cout << "	id = " << id << endl;
	cout << "~Object." << endl;
	amount--;
}

int Object::Damage(int damage){
	hp -= damage;
	return hp;
}

int Object::Is_Located(int x1, int y1) {
	if (x1 == x && y1 == y) return 1;
	return 0;
}

bool Object::Is_Dead() {
	if (hp <= 0) return true;
	return false;
}

int& Object::Get_X() {
	return x;
}

int& Object::Get_Y() {
	return y;
}
