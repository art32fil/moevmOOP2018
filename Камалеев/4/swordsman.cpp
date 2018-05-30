#include "swordsman.h"

Swordsman::Swordsman(ifstream& f, const shared_ptr<Crown>& clr) : Warrior(f, clr) {
	cout << "Swordsman:" << endl;
	cout << "Swordsman." << endl;
}

Swordsman::Swordsman(int x, int y, int hp, int strength, const shared_ptr<Crown> crown) : Warrior(x, y, hp, strength, crown) {
	cout << "Swordsman:" << endl;
	cout << "Swordsman." << endl;
}

Swordsman::~Swordsman() {
	cout << "~Swordsman:" << endl;
	cout << "~Swordsman." << endl;
}

List<tuple<int, int, int>>* Swordsman::attack() {
	List<tuple<int, int, int>>* distance = new List<tuple<int, int, int>>;
	distance->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() - 1, Get_Strength()));
	distance->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() + 1, Get_Strength()));
	distance->Supl_End(tuple<int, int, int>(Get_X() - 1, Get_Y(), Get_Strength()));
	distance->Supl_End(tuple<int, int, int>(Get_X() + 1, Get_Y(), Get_Strength()));
	return distance;
}

int Swordsman::Is_Located(int x1, int y1) {
	if (Get_X() == x1 && Get_Y() == y1) return 5;
	return 0;
}