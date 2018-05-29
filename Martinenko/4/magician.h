#ifndef MAGICIAN_H
#define MAGICIAN_H
#include "warrior.h"

class Magician : public Warrior {
	int range_x;
	int range_y;
	int range;
public:
	Magician(ifstream& f, const shared_ptr<Crown>& clr,int x, int y) :Warrior(f, clr) {
		range_x = (x - 1 - get_x() > get_x()) ? x - 1 - get_x() : get_x();
		range_y = (y - 1 - get_y() > get_y()) ? y - 1 - get_y() : get_y();
		range = (range_x > range_y) ? range_x : range_y;
		range_x = x - 1;
		range_y = y - 1;
		cout << "Magician:" << endl
			 << "	range = " << range << endl
			 << "Magician." << endl;
	}
	
	Magician(int x, int y, int hp, int force, const shared_ptr<Crown> crown) :Warrior(x, y, hp, force, crown) {
		range_x = (x - 1 - get_x() > get_x()) ? x - 1 - get_x() : get_x();
		range_y = (y - 1 - get_y() > get_y()) ? y - 1 - get_y() : get_y();
		range = (range_x > range_y) ? range_x : range_y;
		range_x = x - 1;
		range_y = y - 1;
		cout << "Magician:" << endl
			<< "	range = " << range << endl
			<< "Magician." << endl;
	}
	
	~Magician() {
		cout << "~Magician:" << endl
			 << "	range = " << range << endl
			 << "~Magician." << endl;
	}
	int isObject(int x1, int y1) {
		if (get_x() == x1 && get_y() == y1) return 4;
		return 0;
	}

	List<tuple<int, int, int>>* attack() {
		
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;

		for (int i = 1; i <= get_x(); i++) {
			 rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y(), get_force()));
		}

		for (int i = 1; i <= get_x() && get_y() + 1 < range_y; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y() + i, get_force()));
		}
		for (int i = 1; i <= get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x(), get_y() - i, get_force()));
		}
		for (int i = 1; i <= get_y()&& get_x() + i <= range_x; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y() - i, get_force()));
		}
		for (int i = 1; i <= range_y - get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x(), get_y() + i, get_force()));
		}
		for (int i = 1; i <= range_x - get_x(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y(), get_force()));
		}
		for (int i = 1; i <= get_x() && i <= get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y() - i, get_force()));
		}
		for (int i = 1; i <= range_x - get_x() && get_y() + i < range_y; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y() + i, get_force()));
		}
		return rnge;
	}
	List<tuple<int, int, int>>* up_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x(), get_y() - i, get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* down_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= range_y - get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x(), get_y() + i, get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* right_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= range_x - get_x(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y(), get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* left_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= get_x(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y(), get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* ru_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= get_y() && get_x() + i <= range_x; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y() - i, get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* lu_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= get_x() && i <= get_y(); i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y() - i, get_force()));
		}
		return rnge;
	}
	
	List<tuple<int, int, int>>* rd_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= range_x - get_x() && get_y() + i < range_y; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() + i, get_y() + i, get_force()));
		}
		return rnge;
	}

	List<tuple<int, int, int>>* ld_range() {
		List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
		for (int i = 1; i <= get_x() && get_y() + 1 < range_y; i++) {
			rnge->pushBack(tuple<int, int, int>(get_x() - i, get_y() + i, get_force()));
		}
		return rnge;
	}


};
#endif
