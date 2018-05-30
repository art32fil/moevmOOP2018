#pragma once
#include "object.h"
#include "list.h"
#include <tuple>
#include <vector>

template<class T>
class Building : public Object {
	char c;
	vector<tuple<int, int>> coords;
public:
	Building(ifstream& fl, const shared_ptr<Crown>& clr,char c) : Object(fl, clr), c(c) {
		int size;
		fl >> size;
		cout << "Building:" << endl;
		cout << "	x0 = " << Get_X() << endl;
		cout << "	y0 = " << Get_Y() << endl;

		for (int i = 1; i <= size; i++) {
			int x, y;
			fl >> x >> y;
			coords.push_back(tuple<int, int>(x, y));
		}
		for (int i = 0; i < coords.size() - 1; i++) {
			cout << "	x" << i + 1 << " = " << get<0>(coords[i]) << endl;
			cout << "	y" << i + 1 << " = " << get<1>(coords[i]) << endl;
		}
		cout << "Building." << endl;
	}

	~Building() {
		cout << "~Building:" << endl;
		cout << "	x0 = " << Get_X() << endl;
		cout << "	y0 = " << Get_Y() << endl;
		for (int i = 0; i < coords.size(); i++) {
			cout << "	x" << i + 1 << " = " << get<0>(coords[i]) << endl;
			cout << "	y" << i + 1 << " = " << get<1>(coords[i]) << endl;
		}
		cout << "Building." << endl;
	}

	int Is_Located(int x1, int y1) {
		if (x1 == Get_X() && y1 == Get_Y()) return 3;
		for (int i = 0; i < coords.size(); i++) {
			if (x1 == get<0>(coords[i]) && y1 == get<1>(coords[i])) return 3;
		}
		return 0;
	}

	int Get_X1(int x) {
		for (int i = 0; i < coords.size(); i++) {
			if (x == get<0>(coords[i])) return get<0>(coords[i]);
		}
		return -1;
	}

	int Get_Y1(int y) {
		for (int i = 0; i < coords.size(); i++) {
			if (y == get<1>(coords[i])) return get<1>(coords[i]);
		}
		return -1;
	}

	T* create(int x, int y, int hp, int force, const shared_ptr<Crown> crown) {
		T* army = new T(x, y, hp, force, crown);
		return army;
	}
	char Get_C() { return c; }

};