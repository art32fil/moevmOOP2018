#include "building.h"

Building::Building(ifstream& f, const shared_ptr<Crown>& clr): Object(f,clr) {
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

Building::Building(int x, int y, int hp, List<tuple<int, int>>* location, const shared_ptr<Crown> crown):Object(x,y,hp,crown),location(location) {
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

int Building::isObject(int x1, int y1) {
	if (get_x() == x1 && get_y() == y1) return 3;
	for (auto it : *location) {
		if ((get<0>(it) == x1) && (get<1>(it) == y1)) return 3;
	}
	return 0;
}

Building::~Building() {
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

