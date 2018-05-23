#pragma once
#include <iostream>
#include <string>
#include "list.h"
#include "object.h"
#include "warrior.h"
#include "building.h"

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
	bool Is_Target_Hit(string clr,int x1, int y1);
	void Movement_Menu();
	void Movement(string clr, int entr, int x, int y);
	bool Attack(string clr, int x1, int y1, int x2, int y2);
	void Arena();
};
