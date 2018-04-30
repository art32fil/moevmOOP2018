#pragma once
#include <tuple>
#include "object.h"
#include "field.h"


using namespace std;

class Warrior : public Object {
	int power;
	int range;
public:
	Warrior(ifstream& file, const shared_ptr<Crown>);
	~Warrior();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	vector<tuple<int, int>> attack();
	int getPower();
};
