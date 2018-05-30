#include <iostream>

using namespace std;

#include "knight.h"

Knight::Knight(ifstream& file, const shared_ptr<Crown> crown) : Warrior(file, crown) {
	getType() = 'k';
	cout << "Knight:" << endl;
}

Knight::Knight(int x, int y, int hp, int power, int range) : Warrior(x, y, hp, power, range) {
	getType() = 'k';
	cout << "Knight:" << endl;
}

Knight::~Knight() {
	cout << "Destroy Knight:" << endl;
}

vector<tuple<int, int>> Knight::attack() {
	vector<tuple<int, int>> attackRange;
	attackRange.push_back(tuple<int, int>(getX(), getY()));
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			attackRange.push_back(tuple<int, int>(getX() + i, getY() + j));
			attackRange.push_back(tuple<int, int>(getX() - i, getY() - j));
			attackRange.push_back(tuple<int, int>(getX() - i, getY() + j));
			attackRange.push_back(tuple<int, int>(getX() + i, getY() - j));
		}
	}
	// надо сортировать объекты в контйнере по здоровью, но мы не можем получить объект по координатам
	// т.к. мы не можем передать сюда поле
	return attackRange;
}