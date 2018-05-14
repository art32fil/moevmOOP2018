#pragma once
#include <fstream>

using namespace std;

class Object {
private:
	int x;
	int y;
	int hp;
public:
	Object(int x, int y, int hp);
	Object(ifstream& file);
	Object();
	~Object();

	void getDamage(int); // получить урок
	void getCoordsFromFile(ifstream& file); // считать координаты объекта из файла
	bool checkObjCoords(int, int); // проверить наличие объекта на данных координатах
	int getX(); // получить координату x
	int getY(); // получить координату y
	int getHp(); // получить очки жизней
};
