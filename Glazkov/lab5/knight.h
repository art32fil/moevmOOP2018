#pragma once

#include "warrior.h"

class Knight : public Warrior {
	
public:
	Knight(ifstream& file, const shared_ptr<Crown> crown);
	Knight(int x, int y, int hp, int power, int range);
	~Knight();

	vector<tuple<int, int>> attack() override;
};