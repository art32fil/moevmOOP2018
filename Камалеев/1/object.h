#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Object { // Класс объект
	int x;
	int y;
	int hp;
public:
	Object(ifstream& fl);
	Object();
	~Object();
	int Damage(int damage);
	bool Is_Located(int x1, int y1);
	bool Is_Dead();
};
