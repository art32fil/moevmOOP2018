#pragma once
#include <iostream>
#include "list.h"
#include "object.h"
using namespace std;

class Field { // Класс поле боя
public:
	List<Object> red_army;
	weak_ptr<Crown> clr_red_army;
	List<Object> green_army;
	weak_ptr<Crown> clr_green_army;
	int x_size, y_size;
	int red_army_size, green_army_size;

	Field(ifstream &fl);
	~Field();
	void Get_Red_Army(ifstream& fl, const shared_ptr<Crown>& color);
	void Get_Green_Army(ifstream& fl, const shared_ptr<Crown>& color);
	void Arena();
	bool Is_Target_Hit(int x1, int y1);
	void Attack(int x,int y,int damage);
	friend istream& operator >>(istream& str, Field& fld);
	friend ostream& operator <<(ostream& str, const Field& fld);
};
