#ifndef WARRIOR_H
#define WARRIOR_H

#include "Object.h"
#include <string.h>
#include <stdio.h>

<<<<<<< HEAD
class Warior : public Object
=======
class Warior :public Object
>>>>>>> 12cbd71f862c9caf9069973ad3fa3da2e569ec44
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
<<<<<<< HEAD

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

=======
>>>>>>> 12cbd71f862c9caf9069973ad3fa3da2e569ec44
#endif // WARRIOR_H
