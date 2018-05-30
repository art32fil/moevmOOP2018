#pragma once
#include "warrior.h"

class Magician : public Warrior {
	int range = 4;
public:
	Magician(ifstream& fl, const shared_ptr<Crown>& clr, int x, int y);
	Magician(int x, int y, int hp, int force, const shared_ptr<Crown> crown);
	~Magician();
	int Is_Located(int x1, int y1);
	List<tuple<int, int, int>>* attack();
	List<tuple<int, int, int>>* up_distance();
	List<tuple<int, int, int>>* down_distance();
	List<tuple<int, int, int>>* right_distance();
	List<tuple<int, int, int>>* left_distance();
};
