#include <iostream>
#include <Windows.h>

using namespace std;

#include "warrior.h"

void deleteObjectFromList(Object* object, List<Object*> &army, int& count);

Warrior::Warrior(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
	getType() = 'w';
	file >> power; 
	cout << "Warrior:" << endl
		<< "	power: " << power << endl;
		//<< "	range: " << range << endl;
}

Warrior::Warrior(int x, int y, int hp, int power, int range) : power(power), Object(x,y,hp) {
	getType() = 'w';
	cout << "Warrior:" << endl
		<< "	power: " << power << endl;
		//<< "	range: " << range << endl;
}

Warrior::Warrior(){
	getType() = 'w';
	cout << "Warrior:" << endl;
}

Warrior::~Warrior() {
	cout << "Destroy Warrior:" << endl
		<< "	power: " << power << endl;
		//<< "	range: " << range << endl;
}

vector<tuple<int, int>> Warrior::attack() {
	vector<tuple<int, int>> attackRange;
	attackRange.push_back(tuple<int, int>(getX(), getY()));
	/*for (int i = 0; i <= range; i++) {
		for (int j = 0; j <= range; j++) {
			if (i == 0 && j == 0) continue;
			attackRange.push_back(tuple<int, int>(getX() + i, getY() + j));
			attackRange.push_back(tuple<int, int>(getX() - i, getY() - j));
			attackRange.push_back(tuple<int, int>(getX() - i, getY() + j));
			attackRange.push_back(tuple<int, int>(getX() + i, getY() - j));
		}
	}*/
	return attackRange;
}

void Warrior::moveUp() {
	getY() -= 1;
}

void Warrior::moveRight() {
	getX() += 1;
}

void Warrior::moveDown() {
	getY() += 1;
}

void Warrior::moveLeft() {
	getX() -= 1;
}

int Warrior::getPower() {
	return power;
}

/*int Warrior::getRange() {
	return range;
}*/