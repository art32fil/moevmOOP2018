#include "Object.h"
#include "list.h"
//#include <iostream>
#include <fstream>




Object::Object(_2dim posit,int hp,int t)
{
	pos = posit;
	health = hp;
	team = t;
	cout << "Object: START" << endl;
	cout << "	x  = " << pos.x << endl;
	cout << "	y  = " << pos.y << endl;
	cout << "	hp = " << health << endl;
	cout << "	team = " << team << endl;
	cout << "Object. END" << endl;
}

Object::Object(ifstream& fin,int t)
{
	fin >> pos.x >> pos.y >> health;
	team = t;
	cout << "Object: START" << endl;
	cout << "	x    = " << pos.x << endl;
	cout << "	y    = " << pos.y << endl;
	cout << "	hp   = " << health << endl;
	cout << "	team = " << team << endl;
	cout << "Object. END" << endl;
}

void Object::get_damage(int damage) {
	health -= damage;
}

Object* Object::is_on_position(_2dim cor) {
	if ((pos.x == cor.x) && (pos.y == cor.y)) return this;
	else return NULL;
}





Object::~Object()
{
	cout << "~Object: START" << endl;
	cout << "	x    = " << pos.x << endl;
	cout << "	y    = " << pos.y << endl;
	cout << "	hp   = " << health << endl;
	cout << "	team = " << team << endl;
	cout << "~Object. END" << endl;
}

Object::Object(const Object & obj) 
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
	return team;
}

