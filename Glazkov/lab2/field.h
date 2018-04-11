#pragma once
#include <fstream>
#include "object.h"
#include <vector>


using namespace std;

class Field {
private:
	int xSize; // ширина поля
	int ySize; // высота поля
	vector<Object*> armyA; // контейнер первой армии
	vector<Object*> armyB; // контейнер второй армии
	int countArmyA; // количество объектов первой армии
	int countArmyB; // количество объектов второй армии
public:
	//Field(int x, int y);
	Field(ifstream& file);
	~Field();

	void getSizeFromFile(ifstream& file); // получить размеры поля из файла
	void getArmyFromFile(ifstream& file); // получить объекты армий из файла
	bool checkArmyCoords(vector<Object*> army, int count, int i, int j); // проверить наличие объектов армии на координатах
	vector<Object*> getArmyA(); // получить контейнер первой армии
	vector<Object*> getArmyB(); // получить контейнер второй армии
	int getCountArmyA(); // получить количество объектов первой армии
	int getCountArmyB(); // получить количество объектов второй армии
	void printField(); // напечатать поле
	void getDamage(vector<Object*> army, int count, int i, int j, int damage); // получить дамаг
};
