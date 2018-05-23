#pragma once
#include <iostream>
#include <fstream>
#include <tuple>
#include "crown.h"
#include "list.h"
using namespace std;

class Object {
private:
	int x;
	int y;
	int hp;
 	shared_ptr<Crown> crown;

	const int id;
	static int count;
	static int amount;
public:
	Object(ifstream& fl, const shared_ptr<Crown>& clr);
	virtual ~Object();

	int Damage(int damage);
	virtual int Is_Located(int x1, int y1);
	bool Is_Dead();
	int& Get_X();
	int& Get_Y();

	virtual List<tuple<int, int, int>>* attack() { exit(1); }
	virtual void move_up() {}
	virtual void move_down(){}
	virtual void move_right(){}
	virtual void move_left(){}
};
