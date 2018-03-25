#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Object {
	int x, y, hp;
public:
	Object(int x, int y, int hp);
	Object(ifstream& f);
	Object();
	~Object();
	int damage(int dmg);
	bool isObject(int x1, int y1);
	bool isDead();
};
