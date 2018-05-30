#ifndef WARRIOR_H
#define WARRIOR_H
#include "object.h"
#include "list.h"
#include <tuple>

class Warrior : public Object
{
    private:
    int force;
    public:
    Warrior(ifstream& f,const shared_ptr<Crown>& clr);
	Warrior(int x, int y, int hp, int force, const shared_ptr<Crown> crown);
	Warrior(){}
	~Warrior();
	void move_up();
	void move_down();
	void move_right();
	void move_left();

	int& get_force() { return force; }
	const int& get_force()  const { return force; }

	int isObject(int x1, int y1);
	virtual List<tuple<int, int, int>>* attack();
};

#endif