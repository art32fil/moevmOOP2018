#pragma once
#include "object.h"
#include "list.h"
#include <tuple>
#include <vector>

class Warrior : public Object
{
	int strength;
 public:
    Warrior(ifstream& fl,const shared_ptr<Crown>& clr);
	~Warrior();

	void move_up();
	void move_down();
	void move_left();
	void move_right();
	List<tuple<int, int, int>>* attack();
	int Is_Located(int x1, int y1);
};