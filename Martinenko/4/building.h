#ifndef BUILDING_H
#define BUILDING_H
#include "object.h"
#include "warrior.h"
#include "list.h"
#include <tuple>

template<class T>
class Building : public Object {
private:
	List<tuple<int, int>>* location;
public:
	Building(ifstream& f, const shared_ptr<Crown>& clr) : Object(f, clr) {
		int size;
		f >> size;
		_location();
		cout << "Building." << endl;
		cout << "	x0 = " << get_x() << endl;
		cout << "	y0 = " << get_y() << endl;
		for (int i = 1; i <= size; i++) {
			tuple<int, int> crd;
			f >> get<0>(crd) >> get<1>(crd);
			location->pushBack(crd);
			cout << "	x" << i << " = " << get<0>(crd) << endl;
			cout << "	y" << i << " = " << get<1>(crd) << endl;
		}
		cout << "Building." << endl;
	}

	Building(int x, int y, int hp, List<tuple<int, int>>* location, const shared_ptr<Crown> crown) :Object(x, y, hp, crown), location(location) {
		auto it = location->begin();
		cout << "Building." << endl;
		cout << "	x0 = " << x << endl;
		cout << "	y0 = " << y << endl;
		for (int i = 1; i <= location->get_size(); i++) {
			cout << "	x" << i << " = " << get<0>(*(it)) << endl;
			cout << "	y" << i << " = " << get<1>(*(it)) << endl;
			++it;
		}
		cout << "Building." << endl;

	}

	int isObject(int x1, int y1) {
		if (get_x() == x1 && get_y() == y1) return 3;
		for (auto it : *location) {
			if ((get<0>(it) == x1) && (get<1>(it) == y1)) return 3;
		}
		return 0;
	}
	
	int get_x1(int x) {
		for (auto i : *location) {
			if (x == get<0>(i)) return get<0>(i);
	}
		return -1;
	}
	
	int get_y1(int y) {
		for (auto i : *location) {
			if (y == get<1>(i)) return get<1>(i);
		}
		return -1;
	}

	void _location() {
		location = new List<tuple<int, int>>;
	}
	
	T* create(int x, int y, int hp, int force, const shared_ptr<Crown> crown) {
		T* army = new T(x, y, hp, force, crown);
		return army;
	}
	
	~Building() {
		auto it = location->begin();
		cout << "~Building." << endl;
		cout << "	x0 = " << get_x() << endl;
		cout << "	y0 = " << get_y() << endl;
		for (int i = 1; i <= location->get_size(); i++) {
			cout << "	x" << i << " = " << get<0>(*(it)) << endl;
			cout << "	y" << i << " = " << get<1>(*(it)) << endl;
			++it;
		}
		cout << "~Building." << endl;
	}
};

#endif