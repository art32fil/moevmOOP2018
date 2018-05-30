#include "object.h"

int Object::count = 0;
int Object::amount = 0;

Object::Object(int x, int y, int hp, const shared_ptr<Crown> crown) :x(x), y(y), hp(hp),crown(crown),id(count){
	cout << "Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	crown = " << crown->get_color() << endl
		<< "	id = " << id << endl
		<< "Object."<<endl;
		amount++;
}

Object::Object(ifstream& f,const shared_ptr<Crown>& clr):id(count++),crown(clr) {
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
		<< "	crown = " << crown->get_color() << endl
		<< "	id = " << id << endl
		<< "Object." << endl;
	amount++;
}

Object::~Object() {
	cout << "~Object:" << endl
		<< "	x = " << x << endl
		<< "	y = " << y << endl
		<< "	hp = " << hp << endl
		<< "	crown = " << crown->get_color() << endl
		<< "	id = " << id << endl
		<< "~Object." << endl;
	amount--;
}
int Object:: damage(int dmg){
	hp -= dmg;
	return hp;
}

int Object::isObject(int x1, int y1) {
	if (x == x1 && y == y1) return 1;
	return 0;
}

bool Object::isDead() {
	if (hp<=0) return true;
	return false;
}

ostream& operator << (ostream& s, const Object& obj) {
	  s << "Object:" << endl
		<< "	x = " << obj.x << endl
		<< "	y = " << obj.y << endl
		<< "	hp = " << obj.hp << endl
		<< "	crown = " << obj.crown->get_color() << endl
		<< "	id = " << obj.id << endl
		<< "Object." << endl;
	return s;
}

istream& operator >> (istream &s, Object &obj){ 
    s >> obj.x >> obj.y >> obj.hp;
		return s;
}

bool Object::operator == (const Object& obj) {
	return(obj.x == x &&obj.y == y);
}