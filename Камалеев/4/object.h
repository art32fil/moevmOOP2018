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
	Object(int x, int y, int hp, const shared_ptr<Crown> crown);
	Object(ifstream& fl, const shared_ptr<Crown>& clr);
	virtual ~Object();

	int Damage(int damage);
	virtual int Is_Located(int x1, int y1);
	bool Is_Dead();

	int& Get_X();
	int& Get_Y();
	int& Get_HP();
	shared_ptr<Crown>& Get_Crown() { return crown; }
	
	//чисто виртуальные функции
	virtual Object* create(int x, int y, int hp, int force, const shared_ptr<Crown> crown) { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* up_distance(){ exit(1); }
	virtual List<tuple<int, int, int>>* down_distance(){ exit(1); }
	virtual List<tuple<int, int, int>>* right_distance(){ exit(1); }
	virtual List<tuple<int, int, int>>* left_distance(){ exit(1); }
	virtual void move_up() {}
	virtual void move_down(){}
	virtual void move_right(){}
	virtual void move_left(){}
	virtual List<tuple<int, int, int>>* attack() {exit(1);}
	virtual char Get_C() { return 'w'; }
	virtual int Get_X1(int x) { return -1; }
	virtual int Get_Y1(int y) { return -1; }

	friend ostream& operator << (ostream& ostr, const Object& obj);
	friend istream &operator >> (istream &istr, Object &obj);
	bool operator == (const Object& obj);
};
