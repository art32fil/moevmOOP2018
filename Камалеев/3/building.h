#pragma once
#include "object.h"
#include "list.h"
#include <vector>

class Building : public Object {
	vector<pair<int, int>> coords;
public:
	Building(ifstream& fl, const shared_ptr<Crown>& clr);
	~Building();
	int Is_Located(int x1, int y1);
};