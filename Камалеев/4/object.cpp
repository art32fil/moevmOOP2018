#include "object.h"

int Object::count = 0;
int Object::amount = 0;

Object::Object(int x, int y, int hp, const shared_ptr<Crown> crown) :x(x), y(y), hp(hp),crown(crown),id(count){ // говорящий конструктор
	cout << "Object:" << endl;
	cout << "	x = " << x << endl;
	cout << "	y = " << y << endl;
	cout << "	hp = " << hp << endl;
	cout << "	crown = " << crown->Get_Color() << endl;
	cout << "	id = " << id << endl;
	cout << "Object." << endl;
	amount++;
}

Object::Object(ifstream& fl,const shared_ptr<Crown>& clr):id(count++),crown(clr) { // инициализация объекта из файла
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

ostream& operator << (ostream& ostr, const Object& obj) { // оператор <<
	ostr << "Object:" << endl;
	ostr << "	x = " << obj.x << endl;
	ostr << "	y = " << obj.y << endl;
	ostr << "	hp = " << obj.hp << endl;
	ostr << "	crown = " << obj.crown->Get_Color() << endl;
	ostr << "	id = " << obj.id << endl;
	ostr << "Object." << endl;
	return ostr;
}

istream& operator >> (istream &istr, Object &obj) {
	istr >> obj.x >> obj.y >> obj.hp;
	return istr;
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

int& Object::Get_HP() {
	return hp;
}

bool Object::operator == (const Object& obj) {
	return(obj.x == x &&obj.y == y);
}
