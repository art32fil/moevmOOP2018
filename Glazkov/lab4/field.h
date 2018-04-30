#pragma once
using namespace std;
#include <fstream>
#include <vector>
#include <memory>
#include "object.h"

class Field {
private:
	int xSize; // ширина поля
	int ySize; // высота поля
	List<Object*> armyA; // контейнер первой армии
	List<Object*> armyB; // контейнер второй армии
	int countArmyA; // количество объектов первой армии
	int countArmyB; // количество объектов второй армии
	weak_ptr<Crown> crownA;
	weak_ptr<Crown> crownB;
public:
	Field(int x, int y);
	Field(ifstream& file);
	~Field();

	void getSizeFromFile(ifstream& file); // получить размеры поля из файла
	void getArmyFromFile(ifstream& file); // получить объекты армий из файла
	Object* checkArmyCoords(List<Object*> &army, int count, int i, int j); // проверить наличие объектов армии на координатах
	List<Object*>& getArmyA(); // получить контейнер первой армии
	List<Object*>& getArmyB(); // получить контейнер второй армии
	int& getCountArmyA(); // получить количество объектов первой армии
	int& getCountArmyB(); // получить количество объектов второй армии
	void printField(ostream& out); // напечатать поле
	weak_ptr<Crown> getCrownA();
	weak_ptr<Crown> getCrownB();
	int getXSize();
	int getYSize();
	//void getDamage(vector<Object*> army, int count, int i, int j, int damage); // получить дамаг
};