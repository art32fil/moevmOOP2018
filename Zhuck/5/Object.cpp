#include "Object.h"
#include "list.h"
#include <iostream>
#include <fstream>

int Object::amount = 0;
int Object::count = 0;

using namespace std;
//ToDo : first goes health
Object::Object(_2dim posit,int hp, const shared_ptr<Crown> t,char type): id(amount+1), team(t), type(type)
{
	pos = posit;
	health = hp;
	amount++;
	count++;
	cout << "Object: START" << endl;
	cout << "	x  = " << pos.x << endl;
	cout << "	y  = " << pos.y << endl;
	cout << "	hp = " << health << endl;
	cout << "	team = " << team << endl;
	cout << "Object. END" << endl;
}

Object::Object(ifstream& fin, const shared_ptr<Crown> t,char type) : id(amount+1), team(t),type(type)
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
	else return -1;
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

//copeing doesnt have copy of crown: dunno what to do
Object::Object(const Object & obj) : team(obj.team),id(obj.amount+1),type(obj.type)
{
	amount++;
	count++;
	pos.x= obj.pos.x;
	pos.y = obj.pos.y;
	health = obj.health;
	//cout << "Creating copy of Object:" << endl;
	cout << "$Object: START" << endl;
	cout << "	id		= " << id << endl;
	cout << "	type	= " << type << endl;
	cout << "	pos.x	= " << pos.x << endl;
	cout << "	pos.y	= " << pos.y << endl;
	cout << "	health	= " << health << endl;
	cout << "$Object: END " << pos.x << endl;
	//return *this;
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
}
void Object::show_stats()
{
	cout << " type: = " << type << "; id = " << id << "; team = " << show_team();
}


istream& operator>>(istream &in, Object &ob) {
	in >> ob.pos.x >> ob.pos.y >> ob.health;
	return in;
}

ostream& operator<<(ostream &out, Object &ob) {
	ob.print(out);
	return out;
}

const _2dim Object::get_coords() {
	return pos;
}

bool operator==(const _2dim a, const _2dim b) {
	return (a.x == b.x) && (a.y == b.y);
}

char Object::get_type() {
	return type;
}

