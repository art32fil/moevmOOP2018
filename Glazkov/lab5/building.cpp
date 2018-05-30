#include <iostream>

using namespace std;

#include "building.h"
#include "warrior.h"
#include "knight.h"
#include "mage.h"

/*template <typename BTYPE>
<BTYPE>::Building(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
	getType() = 'b';
	int size;
	file >> size;
	for (int i = 0; i < size; i++) {
		int x, y;
		file >> x >> y;
		coords.push_back(tuple<int, int>(x, y));
	}
	cout << "Building:" << endl;
	for (int i = 0; i < coords.size(); i++) {
		cout << "	x: " << get<0>(coords[i]) << endl
			<< "	y: " << get<1>(coords[i]) << endl;
	}
}

template <typename BTYPE>
Building<BTYPE>::~Building() {
	cout << "Destroy Buildingt:" << endl;
	for (int i = 0; i < coords.size(); i++) {
		cout << "	x: " << get<0>(coords[i]) << endl
			<< "	y: " << get<1>(coords[i]) << endl;
	}
}

template <typename BTYPE>
vector<tuple<int, int>> Building<BTYPE>::getCoords() {
	return coords;
}*/

template <>
Warrior* Building<Warrior>::spawn() {
	Warrior* obj = new Warrior(0, 0, 100, 100, 1);
	return obj;
}

template <>
Knight* Building<Knight>::spawn() {
	Knight* obj = new Knight(0, 0, 100, 100, 1);
	return obj;
}

template <>
Mage* Building<Mage>::spawn() {
	Mage* obj = new Mage(0, 0, 100, 100, 1);
	return obj;
}

