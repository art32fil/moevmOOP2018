#include "building.h"

Building::Building(ifstream& fl, const shared_ptr<Crown>& clr): Object(fl,clr) {
	int size;
	fl >> size;
	cout << "Building:" << endl;
	cout << "	x0 = " << Get_X() << endl;
	cout << "	y0 = " << Get_Y() << endl;
	for (int i = 1; i < size; i++) {
		int x, y;
		fl >> x >> y;
		coords.push_back(pair<int, int>(x, y));
	}
	for (int i = 0; i < coords.size(); i++) {
		cout << "	x" << i+1 << " = " << get<0>(coords[i]) << endl;
		cout << "	y" << i+1 << " = " << get<1>(coords[i]) << endl;
	}
	cout << "Building." << endl;
}

Building::~Building() {
	cout << "~Building:" << endl;
	cout << "	x0 = " << Get_X() << endl;
	cout << "	y0 = " << Get_Y() << endl;
	for (int i = 0; i < coords.size(); i++) {
		cout << "	x" << i+1 << " = " << get<0>(coords[i]) << endl;
		cout << "	y" << i+1 << " = " << get<1>(coords[i]) << endl;
	}
	cout << "Building." << endl;
}

int Building::Is_Located(int x1, int y1) {
	if (x1 == Get_X() && y1 == Get_Y()) return 3;
	for (int i = 0; i < coords.size(); i++) {
		if (x1 == get<0>(coords[i]) && y1 == get<1>(coords[i])) return 3;
	}
	return 0;
}

