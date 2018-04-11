#include "object.h"

int Object::count = 0;
int Object::amount = 0;

Object::Object(int x, int y, int hp, const shared_ptr<Crown> crown) : x(x), y(y), hp(hp), crown(crown), id(count) {
	cout << "Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "	crown = " << crown->Get_Color() << endl;
	cout << "	id = " << id << endl;
	cout << "Object." << endl;
	amount++;
}

Object::Object(ifstream& fl, const shared_ptr<Crown>& clr) : id(count++), crown(clr) {
	if (!fl.is_open()) {
		cout << "File can't be opened!" << endl;
		exit(EXIT_FAILURE);
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

Object::~Object() { // говор€щий деструктор
	cout << "~Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "	crown = " << crown->Get_Color() << endl;
	cout << "	id = " << id << endl;
	cout << "~Object." << endl;
	amount--;
}

ostream& operator << (ostream& str, const Object& obj) {
	str << obj.x << obj.y << obj.hp;
	return str;
}

istream& operator >> (istream &str, Object &obj) {
	str >> obj.x >> obj.y >> obj.hp;
	return str;
}

bool Object::Is_Located(int x1, int y1) { // функци€, определ€юща€, находитс€ ли объект в заданных координатах
	if (x == x1 && y == y1) return true;
	return false;
}

int Object::Damage(int damage){ // функци€, отвечающая за получение урона объектом
	hp -= damage;
	return hp;
}

bool Object::Is_Dead() { // функци€, определ€юща€, убит ли объект
	if (hp <= 0) return true;
	return false;
}
