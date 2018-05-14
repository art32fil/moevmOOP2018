#pragma once
#include <iostream>
#include "list.h"
#include "object.h"
using namespace std;

class Field { // Класс поле боя
	List<Object> red_army;
	List<Object> green_army;
	int x_size, y_size;
	int red_army_size, green_army_size;
public:
	Field(ifstream &fl);
	~Field();
	void Get_Armies(ifstream& fl);
	void Arena();
	bool Is_Target_Hit(int x1, int y1);
	void Attack(int x,int y,int damage);
};
