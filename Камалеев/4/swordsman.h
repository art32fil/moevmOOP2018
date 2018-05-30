#pragma once
#include "warrior.h"

class Swordsman :public Warrior {
public:
	Swordsman(ifstream& f, const shared_ptr<Crown>& clr);
	Swordsman(int x, int y, int hp, int force, const shared_ptr<Crown> crown);
	~Swordsman();
	List<tuple<int, int, int>>* attack();
	int Is_Located(int x1, int y1);
};