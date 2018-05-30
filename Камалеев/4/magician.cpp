#include "magician.h"

Magician::Magician(ifstream& fl, const shared_ptr<Crown>& clr, int x, int y) :Warrior(fl, clr) {
	cout << "Magician:" << endl;
	cout << "Magician." << endl;
}

Magician::Magician(int x, int y, int hp, int strength, const shared_ptr<Crown> crown) :Warrior(x, y, hp, strength, crown){
	cout << "Magician:" << endl;
	cout << "Magician." << endl;
}

Magician::~Magician() {
	cout << "~Magician:" << endl;
	cout << "~Magician." << endl;
}

List<tuple<int, int, int>>* Magician::attack() {

	List<tuple<int, int, int>>* distance = new List<tuple<int, int, int>>;

	for (int i = 1; i <= range; i++) {
		if (Get_X() - i >= 0) distance->Supl_End(tuple<int, int, int>(Get_X() - i, Get_Y(), Get_Strength()));
	}


	for (int i = 1; i <= range; i++) {
		if (Get_Y() - i >= 0) distance->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() - i, Get_Strength()));
	}

	for (int i = 1; i <= range; i++) {
		distance->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() + i, Get_Strength()));
	}

	for (int i = 1; i <= range; i++) {
		distance->Supl_End(tuple<int, int, int>(Get_X() + i, Get_Y(), Get_Strength()));
	}

	return distance;
}

List<tuple<int, int, int>>* Magician:: up_distance() {
	List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
	for (int i = 1; i <= range; i++) {
		rnge->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() - i, Get_Strength()));
	}
	return rnge;
}

List<tuple<int, int, int>>* Magician::down_distance() {
	List<tuple<int, int, int>>* rnge = new List<tuple<int, int, int>>;
	for (int i = 1; i <= range; i++) {
		rnge->Supl_End(tuple<int, int, int>(Get_X(), Get_Y() + i, Get_Strength()));
	}
	return rnge;
}

List<tuple<int, int, int>>* Magician::right_distance() {
	List<tuple<int, int, int>>* distance = new List<tuple<int, int, int>>;
	for (int i = 1; i <= range; i++) {
		distance->Supl_End(tuple<int, int, int>(Get_X() + i, Get_Y(), Get_Strength()));
	}
	return distance;
}

List<tuple<int, int, int>>* Magician::left_distance() {
	List<tuple<int, int, int>>* distance = new List<tuple<int, int, int>>;
	for (int i = 1; i <= range; i++) {
		distance->Supl_End(tuple<int, int, int>(Get_X() - i, Get_Y(), Get_Strength()));
	}
	return distance;
}

int Magician::Is_Located(int x1, int y1) {
	if (Get_X() == x1 && Get_Y() == y1) return 4;
	return 0;
}