#pragma once
#include "object.h"
#include "list.h"
#include <tuple>
#include <vector>

class Warrior : public Object
{
	int strength;
	int range;
 public:
    Warrior(ifstream& fl,const shared_ptr<Crown>& clr);
	Warrior(int x, int y, int hp, int strength, const shared_ptr<Crown> crown);
	~Warrior();
	
	int& Get_Strength() { return strength; }
	void move_up();
	void move_down();
	void move_left();
	void move_right();

	int Is_Located(int x1, int y1);
	List<tuple<int,int,int>>* attack();
};