#pragma once
#include <iostream>
#include <fstream>
#include "crown.h"

using namespace std;

class Object { // класс объект
	int x;
	int y;
	int hp;
	int id;
	shared_ptr<Crown> crown;
	static int count;
	static int amount;
public:
	Object(int x, int y, int hp, const shared_ptr<Crown> crown);
	Object(ifstream& fl, const shared_ptr<Crown>& clr);
	~Object();

	bool operator == (const Object& obj) {
		return(obj.x == x && obj.y == y);
	}

	void Delete_Crown() {
		crown.reset();
	}

	int& Get_X() { return x; }
	const int& Get_X() const { return x; }
	int& Get_Y() { return y; }
	const int& Get_Y() const { return y; }
	int& Get_HP() { return hp; }
	const int& Get_HP()const { return hp; }
	int Damage(int damage);
	bool Is_Located(int x1, int y1);
	bool Is_Dead();
	friend ostream& operator << (ostream& str, const Object& obj);
	friend istream &operator >> (istream &str, Object &obj);
};
