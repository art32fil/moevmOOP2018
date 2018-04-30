#include "Object.h"
#include "list.h"
#include <iostream>
#include <fstream>

int Object::amount = 0;
int Object::count = 0;


//ToDo : first goes health
Object::Object(_2dim posit,int hp,int t): id(amount+1)
{
	pos = posit;
	health = hp;
	//team = t;
	amount++;
	count++;
	cout << "Object: START" << endl;
	cout << "	x  = " << pos.x << endl;
	cout << "	y  = " << pos.y << endl;
	cout << "	hp = " << health << endl;
	cout << "	team = " << team << endl;
	cout << "Object. END" << endl;
}

Object::Object(ifstream& fin, const shared_ptr<Crown> t) : id(amount+1), team(t)
{
	fin >> health >> pos.x >> pos.y ;
	//team = t;
	amount++;
	count++;
	cout << "Object: START" << endl;
	cout << "	x    = " << pos.x << endl;
	cout << "	y    = " << pos.y << endl;
	cout << "	hp   = " << health << endl;
	cout << "	team = " << show_team() << endl;
	cout << "	id   = " << id << endl;
	cout << "Object. END" << endl;
}

int Object::get_damage(int damage) {
	health -= damage;
	if (health <= 0) return get_id();
	else return NULL;
}

Object* Object::is_on_position(_2dim cor) {
	if ((pos.x == cor.x) && (pos.y == cor.y)) return this;
	else return NULL;
}


Object::~Object()
{
	count--;
	cout << "~Object: START" << endl;
	cout << "	x    = " << pos.x << endl;
	cout << "	y    = " << pos.y << endl;
	cout << "	hp   = " << health << endl;
	cout << "	team = " << show_team() << endl;
	cout << "	id   = " << id << endl;
	cout << "~Object. END" << endl;
}

Object::Object(const Object & obj) : id(amount)
{
	pos.x= obj.pos.x;
	pos.y = obj.pos.y;
	health = obj.health;
}
int Object::show_health()
{
	return health;
}

int Object::show_team()
{
	return (team.get())->get_colour();
}

int Object::get_id() {
	return id;
}

bool Object::last_representive() {
	return team.unique();
}

long Object::use_count() {
	return team.use_count();
};

istream& operator>>(istream &in, Object &ob) {
	in >> ob.pos.x >> ob.pos.y >> ob.health;
	return in;
}

ostream& operator<<(ostream &out, Object &ob) {
	if (ob.show_team() == 1) // 1
		out << "\033[32m";
	if (ob.show_team() == 2) // 0
		out << "\033[31m";
	out << " O " << "\033[0m";
	return out;
}

const _2dim Object::get_coords() {
	return pos;
}
