#include "Building.h"



Building::Building(ifstream& fin, const shared_ptr<Crown > t) : Object(fin, t)
{
	fin >> range.x >> range.y;
	cout << "Building : START:" << endl;
	cout << "	range.x = " << range.x << endl;
	cout << "	range.y = " << range.y << endl;
	cout << "Building : END." << endl << endl;

}


Building::~Building()
{
	cout << "~Building : START:" << endl;
	cout << "	range.x = " << range.x << endl;
	cout << "	range.y = " << range.y << endl;
	cout << "~Building : END." << endl << endl;
}

Object* Building::is_on_position(_2dim delt) {
	bool up, right; // sectors

	up = pos.y >= range.y;
	right = pos.x <= range.x;

	//maybe bags me dunno
	if (up && right) {
		if ((pos.x <= delt.x) && (range.x >= delt.x) && (pos.y >= delt.y) && (range.y <= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (!up && right) {
		if ((pos.x <= delt.x) && (range.x >= delt.x) && (pos.y <= delt.y) && (range.y >= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (up && !right) {
		if ((pos.x >= delt.x) && (range.x <= delt.x) && (pos.y >= delt.y) && (range.y <= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (!up && !right) {
		if ((pos.x >= delt.x) && (range.x <= delt.x) && (pos.y <= delt.y) && (range.y >= delt.y)) {
			return this;
		}
		else return NULL;
	}
	//complete withoout bugs
}

ostream &operator<<(ostream &out, Building &ob) {
	if (ob.show_team() == 1) // 1
		out << "\033[32m";
	if (ob.show_team() == 2) // 0
		out << "\033[31m";
	out << " B " << "\033[0m";
	return out;

}