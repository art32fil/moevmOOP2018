#pragma once
#include "object.h"
#include <tuple>
#include <vector>

using namespace std;

class Building : public Object {
	vector<tuple<int, int>> coords;
public:
	Building(ifstream& file, const shared_ptr<Crown>);
	~Building();

	vector<tuple<int, int>> getCoords();
	bool checkBuildingCoords(int yCoord, int xCoord);
};