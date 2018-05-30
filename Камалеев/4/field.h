#pragma once
#include <iostream>
#include <string>
#include "list.h"
#include "object.h"
#include "warrior.h"
#include "building.h"
#include "magician.h"
#include "swordsman.h"

using namespace std;

class Field {
public:
	List<Object*> red_army;
	weak_ptr<Crown> clr_red_army;
	List<Object*> green_army;
	weak_ptr<Crown> clr_green_army;
	int x_size, y_size;
	int red_army_size, green_army_size;

	Field(ifstream &fl);
	~Field();
	void Get_Red_Army(ifstream& fl, const shared_ptr<Crown>& color);
	void Get_Green_Army(ifstream& fl, const shared_ptr<Crown>& color);
	void Arena();
	int Get_Min_Enemy_HP(string clr, int x, int y);
	tuple<int, int> Min_Ray(string clr, List<tuple<int, int, int>>* range);
	bool Is_Target_Hit(string clr, string warrior, int x1, int y1);
	bool Attack(string clr, string kind, int x1, int y1);
	void Movement_Menu();
	void Movement(string clr, int entr, int x, int y);
	void Create_Object(string clr, int x, int y);
	friend istream& operator >>(istream& istr, Field& fld);
	friend ostream& operator <<(ostream& ostr, const Field& fld);
};
