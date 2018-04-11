#include <iostream>
#include <Windows.h>

using namespace std;

#include <fstream>
#include "field.h"

ostream &operator<<(ostream &ostr, Object &obj);

ostream &operator<<(ostream &ostr, Field &fd) {
	fd.printField(ostr);
	return ostr;
}

Field::Field(istream& in) {
	getSizeFromConsole(in);
	cout << "Field:" << endl
		<< "	xSize = " << xSize << endl
		<< "	ySize = " << ySize << endl;
	getArmyFromConsole(in);
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
	delete &armyA;
	delete &armyB;
}

void Field::getSizeFromFile(ifstream& file) {
	file >> xSize >> ySize;
}

void Field::getArmyFromFile(ifstream& file) {
	file >> countArmyA;
	shared_ptr<Crown> temp1(new Crown('A'));
	crownA = temp1;
	for (int i = 0; i < countArmyA; i++) {
		armyA.append(new Object(file, temp1));
	}
	file >> countArmyB;
	shared_ptr<Crown> temp2(new Crown('B'));
	crownB = temp2;
	for (int i = 0; i < countArmyB; i++) {
		armyB.append(new Object(file, temp2));
	}
}

void Field::getSizeFromConsole(istream& in) {
	in >> xSize >> ySize;
}

void Field::getArmyFromConsole(istream& in) {
	in >> countArmyA;
	shared_ptr<Crown> temp1(new Crown('A'));
	crownA = temp1;
	for (int i = 0; i < countArmyA; i++) {
		armyA.append(new Object(in, temp1));
	}
	in >> countArmyB;
	shared_ptr<Crown> temp2(new Crown('B'));
	crownB = temp2;
	for (int i = 0; i < countArmyB; i++) {
		armyB.append(new Object(in, temp2));
	}
}

Object* Field::checkArmyCoords(List<Object*> &army, int count, int i, int j){
	for (auto armyI: army) {
		if (armyI->checkObjCoords(i, j)) {
			return armyI;
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