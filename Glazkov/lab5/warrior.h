#pragma once
#include <tuple>
#include "object.h"
#include "field.h"


using namespace std;

class Warrior : public Object {
	int power;
	//int range;
public:
	Warrior(ifstream& file, const shared_ptr<Crown>);
	Warrior(int, int, int, int, int);
	Warrior();
	virtual ~Warrior();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	virtual vector<tuple<int, int>> attack();
	int getPower();
	//int getRange();
};
