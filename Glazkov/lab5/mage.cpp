#include <iostream>

using namespace std;

#include "mage.h"

Mage::Mage(ifstream& file, const shared_ptr<Crown> crown) : Warrior(file, crown) {
	getType() = 'm';
	cout << "Mage:" << endl;
}

Mage::Mage(int x, int y, int hp, int power, int range) : Warrior(x, y, hp, power, range) {
	getType() = 'm';
	cout << "Mage:" << endl;
}

Mage::~Mage() {
	cout << "Destroy Mage:" << endl;
}

vector<tuple<int, int>> Mage::attack(){
	vector<tuple<int, int>> attackRange;
	attackRange.push_back(tuple<int, int>(getX(), getY()));
	for (int i = 1; i <= 3; i++) {
		attackRange.push_back(tuple<int, int>(getX() + i, getY()));
		attackRange.push_back(tuple<int, int>(getX() - i, getY()));
		attackRange.push_back(tuple<int, int>(getX(), getY() + i));
		attackRange.push_back(tuple<int, int>(getX(), getY() - i));
	}
	return attackRange;
}