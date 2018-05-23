#include "warrior.h"

Warrior::Warrior(ifstream& fl,const shared_ptr<Crown>& clr): Object(fl,clr) {
	fl >> strength;
	cout << "Warrior:" << endl;
	cout << "	strength = " << strength << endl;
    cout << "Warrior." << endl;
}

Warrior::~Warrior() {
	cout << "~Warrior:" << endl;
	cout << "	strength = " << strength << endl;
	cout << "~Warrior." << endl;
}

void Warrior::move_up() {
	Get_Y()--;
}

void Warrior::move_down() {
	Get_Y()++;
}

void Warrior::move_left() {
	Get_X()--;
}

void Warrior::move_right() {
	Get_X()++;
}

List<tuple<int, int, int>>* Warrior::attack() {
	List<tuple<int, int, int>>* range = new List<tuple<int, int, int>>;
	range->Supl_End(tuple<int, int, int>(Get_X(), Get_Y(), strength));
	return range;
}

int Warrior::Is_Located(int x1, int y1) {
	if (x1 == Get_X() && y1 == Get_Y()) return 2;
	return 0;
}
