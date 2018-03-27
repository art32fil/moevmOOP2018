#include "object.h"

Object::Object(ifstream& fl) { // функция инициализации полей объекта из файла
	if (!fl.is_open()) {
		cout << "There are no file in directory!" << endl;
		exit(EXIT_FAILURE);
		system("pause");
	}
	fl >> x >> y >> hp;
	cout << "Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "Object." << endl;
}

Object::Object() {
	x = y = hp = 0;
}

Object::~Object() { // говорящий деструктор
	cout << "~Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "~Object." << endl;

}

bool Object::Is_Located(int x1, int y1) { // функция, определяющая, находится ли объект в заданных координатах
	if (x == x1 && y == y1) return true;
	return false;
}

int Object::Damage(int damage){ // функция, отвечающая за получение урона объектом
	hp -= damage;
	return hp;
}

bool Object::Is_Dead() { // функция, определяющая, убит ли объект
	if (hp <= 0) return true;
	return false;
}
