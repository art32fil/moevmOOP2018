#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "warrior.h"

class Swordsman :public Warrior {
	int range;
public:

	Swordsman() {}

	Swordsman(ifstream& f, const shared_ptr<Crown>& clr) :Warrior(f,clr) {
		range = 1;
		cout << "Swordsman:" << endl
			 << "	range = " << range << endl
			 << "Swordsman." << endl;
	}
	
	Swordsman(int x, int y, int hp, int force, const shared_ptr<Crown> crown) :Warrior(x, y, hp, force, crown), range(1) {
		cout << "Swordsman:" << endl
			<< "	range = " << range << endl
			<< "Swordsman." << endl;
	}

	~Swordsman() {
		cout << "~Swordsman:" << endl
			 << "	range = " << range << endl
			 << "~Swordsman." << endl;
	}

	List<tuple<int, int, int>>* attack() {
		List<tuple<int, int, int>>* range = new List<tuple<int, int, int>>;
		range->pushBack(tuple<int, int, int>(get_x(), get_y() - 1, get_force()));
		range->pushBack(tuple<int, int, int>(get_x(), get_y() + 1, get_force()));
		range->pushBack(tuple<int, int, int>(get_x() - 1, get_y(), get_force()));
		range->pushBack(tuple<int, int, int>(get_x() + 1, get_y(), get_force()));
		range->pushBack(tuple<int, int, int>(get_x() + 1, get_y() + 1, get_force()));
		range->pushBack(tuple<int, int, int>(get_x() + 1, get_y() - 1, get_force()));
		range->pushBack(tuple<int, int, int>(get_x() - 1, get_y() + 1, get_force()));
		range->pushBack(tuple<int, int, int>(get_x() - 1, get_y() - 1, get_force()));
		return range;
	}

	int isObject(int x1, int y1) {
		if (get_x() == x1 && get_y() == y1) return 5;
		return 0;
	}
};
#endif