#pragma once
using namespace std;

#include <fstream>
#include <memory>
#include <typeinfo>
#include "crown.h"
#include "iter.h"


class Object {
private:
	int x;
	int y;
	int hp;
	char type;
	const shared_ptr<Crown> crown;

	const int id;
	static int count;
	static int amount;
public:

	Object(int x, int y, int hp);
	Object(ifstream& file, const shared_ptr<Crown>);
	Object(istream& in, const shared_ptr<Crown>);
	Object();
	virtual ~Object();

	void getDamage(int); // получить урон
	void getCoordsFromFile(ifstream& file); // считать координаты объекта из файла
	void getCoordsFromConsole(istream& in);
	bool checkObjCoords(int, int); // проверить наличие объекта на данных координатах
	void changeX(int);
	void changeY(int);
	int& getX(); // получить координату x
	int& getY(); // получить координату y
	int getHp(); // получить очки жизней
	int getId(); // получить идентификатор объекта
	char& getType();
	const shared_ptr<Crown>& getCrown(); // получить идентификатор объекта

	friend ostream &operator<<(ostream &ostr, Object &obj);
};
