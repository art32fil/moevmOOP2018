#ifndef WARRIOR_H
#define WARRIOR_H
#include "object.h"
#include "list.h"
#include <tuple>

class Warrior : public Object
{
    private:
    int force;
	//List<tuple<int, int, int>> range;
    public:
    Warrior(ifstream& f,const shared_ptr<Crown>& clr);
	Warrior(int x, int y, int hp, int force, const shared_ptr<Crown> crown);
	~Warrior();

	void move_up();
	void move_down();
	void move_right();
	void move_left();

//	List<tuple<int, int, int>> get_range() { return range; }
	//const List<tuple<int, int, int>> get_range() const { return range; }

	int isObject(int x1, int y1);
	List<tuple<int,int,int>>* attack();
	//void attack();
};

#endif