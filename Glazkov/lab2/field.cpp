#include "field.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

using namespace std;

//Field::Field(int x, int y) : xSize(x), ySize(y) {}

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
	for (vector<Object*>::iterator it = armyA.begin(); it != armyA.end(); ++it){
		delete (*it);
	}
	armyA.clear();
	for (vector<Object*>::iterator it = armyB.begin(); it != armyB.end(); ++it) {
		delete (*it);
	}
	armyB.clear();
	//delete[]armyA;
	//delete[]armyB;
}

void Field::getSizeFromFile(ifstream& file) {
	file >> xSize >> ySize;
}

void Field::getArmyFromFile(ifstream& file) {
	file >> countArmyA;
	//armyA = new Object*[countArmyA];
	for (int i = 0; i < countArmyA; i++) {
		armyA.push_back(new Object(file));
	}
	file >> countArmyB;
	//armyB = new Object*[countArmyB];
	for (int i = 0; i < countArmyB; i++) {
		armyB.push_back(new Object(file));
	}
}

bool Field::checkArmyCoords(vector<Object*> army, int count, int i, int j){
	for (int armyI = 0; armyI < count; armyI++) {
		if (army[armyI]->checkObjCoords(i, j)) {
			return true;
		}
	}
	return false;
}

bool printArmy(vector<Object*> army, int color, int count, int i, int j) {
	for (int armyI = 0; armyI < count; armyI++) {
		if (army[armyI]->checkObjCoords(i, j)) {
			char symb = 'O';
			if (army[armyI]->getHp()<=0) {
				symb = 'X';
			}
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			if (color == 1) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			}
			cout << symb;
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			return true;
		}
	}
	return false;
}

void Field::printField() {
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			if (printArmy(armyA, 1, countArmyA, i, j) || printArmy(armyB, 2, countArmyB, i, j)) {
				continue;
			}
			cout << "+";
		}
		cout << endl;
	}
}

vector<Object*> Field::getArmyA() {
	return armyA;
}

vector<Object*> Field::getArmyB() {
	return armyB;
}

int Field::getCountArmyA() {
	return countArmyA;
}

int Field::getCountArmyB() {
	return countArmyB;
}

void Field::getDamage(vector<Object*> army, int count, int i, int j, int damage) {
	for (int armyI = 0; armyI < count; armyI++) {
		if (army[armyI]->checkObjCoords(i, j)) {
			army[armyI]->getDamage(damage);
		}
	}
}