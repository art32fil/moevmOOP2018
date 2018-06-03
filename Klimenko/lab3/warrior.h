#ifndef WARRIOR_H
#define WARRIOR_H

#include "Object.h"
#include <string.h>
#include <stdio.h>

class Warior : public Object
{
	int force;
public:
	Warior(ifstream& fin, const shared_ptr<Crown> t);
	~Warior();
	Warior* move(char option);
	int give_force();
	// thinkaboutittoo friend istream &operator>>(istream &in, Warior &ob);
	friend ostream &operator<<(ostream &out, Warior &ob);
};

class Archer : public Warior {
	int range;
public:
	Archer(ifstream& fin, const shared_ptr<Crown> t) : Warior(fin, t) {
		range = 3;
	}
	~Archer() {}
	
	int get_range() {
		return range;
	}
};

class Kamikaze : public Warior {
public:
	Kamikaze(ifstream& fin, const shared_ptr<Crown> t) : Warior(fin, t) {}
	~Kamikaze() {}

};

#endif // WARRIOR_H
