#pragma once
#include <fstream>
#include <vector>
#include "object.h"
#include "iter.h"



using namespace std;

class Field {
private:
	int xSize; // ширина поля
	int ySize; // высота поля
	List<Object*> armyA; // контейнер первой армии
	List<Object*> armyB; // контейнер второй армии
	int countArmyA; // количество объектов первой армии
	int countArmyB; // количество объектов второй армии
public:
	//Field(int x, int y);
	Field(ifstream& file);
	~Field();

	void getSizeFromFile(ifstream& file); // получить размеры поля из файла
	void getArmyFromFile(ifstream& file); // получить объекты армий из файла
	Object* checkArmyCoords(List<Object*> &army, int count, int i, int j); // проверить наличие объектов армии на координатах
	List<Object*>& getArmyA(); // получить контейнер первой армии
	List<Object*>& getArmyB(); // получить контейнер второй армии
	int getCountArmyA(); // получить количество объектов первой армии
	int getCountArmyB(); // получить количество объектов второй армии
	void printField(); // напечатать поле
	//void getDamage(vector<Object*> army, int count, int i, int j, int damage); // получить дамаг
};
