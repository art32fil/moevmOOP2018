#pragma once

#include "warrior.h"

class Mage : public Warrior {

public:
	Mage(ifstream& file, const shared_ptr<Crown> crown);
	Mage(int, int, int, int, int);
	~Mage();

	vector<tuple<int, int>> attack() override;
};