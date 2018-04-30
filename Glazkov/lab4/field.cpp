#include <iostream>
#include <Windows.h>

using namespace std;

#include <fstream>
#include "field.h"
#include "warrior.h"
#include "building.h"

ostream &operator<<(ostream &ostr, Field &fd) {
	fd.printField(ostr);
	return ostr;
}

Field::Field(int x, int y) : xSize(x), ySize(y) {}

Field::Field(ifstream& file) {
	getSizeFromFile(file);
	cout << "Field:" << endl
		<< "	xSize = " << xSize << endl
		<< "	ySize = " << ySize << endl;
	getArmyFromFile(file);
}

Field::~Field() {
	cout << "Destroy Field:" << endl
		<< "	xSize = " << xSize << endl
		<< "	ySize = " << ySize << endl;
	/*for (auto armyI : armyA) {
		switch (armyI->getType()) {
		case 'w':
			delete ((Warrior*)armyI);
			break;
		case 'b':
			delete ((Building*)armyI);
			break;
		}
		armyA.del(0);
	}
	for (auto armyI : armyB) {
		switch (armyI->getType()) {
		case 'w':
			delete ((Warrior*)armyI);
			break;
		case 'b':
			delete ((Building*)armyI);
			break;
		}
		armyB.del(0);
	}*/
	delete &armyA;
	delete &armyB;
}

void Field::getSizeFromFile(ifstream& file) {
	file >> xSize >> ySize;
}

void fillArmy(List<Object*>& army, shared_ptr<Crown>& temp, ifstream& file) {
	char objectType;
	file >> objectType;
	switch (objectType) {
	case 'w':
		army.append(new Warrior(file, temp));
		break;
	case 'b':
		army.append(new Building(file, temp));
		break;
	}
}

void Field::getArmyFromFile(ifstream& file) {
	file >> countArmyA;
	shared_ptr<Crown> temp1(new Crown('A'));
	crownA = temp1;
	for (int i = 0; i < countArmyA; i++) {
		fillArmy(armyA, temp1, file);
	}
	file >> countArmyB;
	shared_ptr<Crown> temp2(new Crown('B'));
	crownB = temp2;
	for (int i = 0; i < countArmyB; i++) {
		fillArmy(armyB, temp2, file);
	}
}

Object* Field::checkArmyCoords(List<Object*> &army, int count, int i, int j){
	for (auto armyI: army) {
		if (armyI->checkObjCoords(i, j)) {
			return armyI;
		}
		if (armyI->getType() == 'b') {
			if (((Building*)armyI)->checkBuildingCoords(i, j)) {
				return armyI;
			}
		}
	}
	return nullptr;
}

bool printArmy(List<Object*> &army, int color, int count, int i, int j) {
	for (auto armyI: army) {
		if (armyI->checkObjCoords(i, j)) {
			cout << *armyI;
			return true;
		}
		else if (armyI->getType() == 'b') {
			if (((Building*)armyI)->checkBuildingCoords(i, j)) {
				cout << *armyI;
				return true;
			}
		}
	}
	return false;
}

void Field::printField(ostream& out) {
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			if (printArmy(armyA, 1, countArmyA, i, j) || printArmy(armyB, 2, countArmyB, i, j)) {
				continue;
			}
			out << "+";
		}
		out << endl;
	}
}

void deleteObjectFromList(Object* object, List<Object*> &army, int& count) {
	for (int i = 0; i < count; i++) {
		if (army[i]->checkObjCoords(object->getY(), object->getX())) {
			army.del(i);
			count--;
		}
	}
}

void attackAim(vector<tuple<int, int>> attackRange, List<Object*> &army, int count, int power) {
	for (int i = 0; i < attackRange.size(); i++) {
		for (auto armyI : army) {
			if (armyI->checkObjCoords(get<1>(attackRange[i]), get<0>(attackRange[i]))) {
				armyI->getDamage(power);
				if (armyI->getHp() <= 0) {
					deleteObjectFromList(armyI, army, count);
				}
				return;
			}
			else if (armyI->getType() == 'b') {
				if (((Building*)armyI)->checkBuildingCoords(get<1>(attackRange[i]), get<0>(attackRange[i]))) {
					armyI->getDamage(power);
					if (armyI->getHp() <= 0) {
						deleteObjectFromList(armyI, army, count);
					}
					return;
				}
			}
		}
	}
}

List<Object*>& Field::getArmyA() {
	return armyA;
}

List<Object*>& Field::getArmyB() {
	return armyB;
}

int& Field::getCountArmyA() {
	return countArmyA;
}

int& Field::getCountArmyB() {
	return countArmyB;
}

weak_ptr<Crown> Field::getCrownA() {
	return crownA;
}

weak_ptr<Crown> Field::getCrownB() {
	return crownB;
}

int Field::getXSize() {
	return xSize;
}

int Field::getYSize() {
	return ySize;
}