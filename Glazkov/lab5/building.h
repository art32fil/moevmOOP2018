#pragma once
#include "object.h"
#include <tuple>
#include <vector>

using namespace std;

template <typename BTYPE = Object>
class Building : public Object {
	vector<tuple<int, int>> coords;
	char buildingType;
public:
	Building(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
		getType() = 'b';
		int size;
		file >> size;
		for (int i = 0; i < size; i++) {
			int x, y;
			file >> x >> y;
			coords.push_back(tuple<int, int>(x, y));
		}
		file >> getBuildingType();
		cout << "Building:" << endl;
		for (int i = 0; i < coords.size(); i++) {
			cout << "	x: " << get<0>(coords[i]) << endl
				<< "	y: " << get<1>(coords[i]) << endl;
		}
		cout << "	spawn-type: " << getBuildingType() << endl;
	}

	virtual ~Building() {
		cout << "Destroy Building:" << endl;
		for (int i = 0; i < coords.size(); i++) {
			cout << "	x: " << get<0>(coords[i]) << endl
				<< "	y: " << get<1>(coords[i]) << endl;
		}
		cout << "	spawn-type: " << getBuildingType() << endl;
	}

	vector<tuple<int, int>> getCoords() {
		return coords;
	}

	bool checkBuildingCoords(int yCoord, int xCoord) {
		for (int i = 0; i<coords.size(); i++) {
			if (xCoord == get<0>(coords[i]) && yCoord == get<1>(coords[i])) return true;
		}
		return false;
	}

	char& getBuildingType() {
		return buildingType;
	}

	BTYPE* spawn();
};