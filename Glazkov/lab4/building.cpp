#include <iostream>

using namespace std;

#include "building.h"

Building::Building(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
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

Building::~Building() {
	cout << "Destroy Buildingt:" << endl;
	for (int i = 0; i < coords.size(); i++) {
		cout << "	x: " << get<0>(coords[i]) << endl
			<< "	y: " << get<1>(coords[i]) << endl;
	}
}

vector<tuple<int, int>> Building::getCoords() {
	return coords;
}

bool Building::checkBuildingCoords(int yCoord, int xCoord) {
	for (int i=0; i<coords.size(); i++){
		if (xCoord == get<0>(coords[i]) && yCoord == get<1>(coords[i])) return true;
	}
	return false;
}