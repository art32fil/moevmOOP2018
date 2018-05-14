#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <fstream>
#include "crown.h"

using namespace std;

class Object {
	int x, y, hp;
	int id;
 shared_ptr<Crown> crown;
	static int count;
	static int amount;
public:
	Object(int x, int y, int hp, const shared_ptr<Crown> crown);
	Object(ifstream& f, const shared_ptr<Crown>& clr);
//	Object();
	~Object();
	bool operator == (const Object& obj) {
		return(obj.x == x &&obj.y == y);
	}

	void delete_crown() {
		crown.reset();
	}
	int damage(int dmg);
	bool isObject(int x1, int y1);
	bool isDead();
	int& get_x(){return x;}
	const int& get_x() const{return x;}
	int& get_y(){return y;}
	const int& get_y() const{return y;}
	int& get_hp(){return hp;}
	const int& get_hp()const{return hp;}
	
	friend istream& operator >> (istream &s, Object &obj);
	friend ostream& operator << (ostream& s, const Object& obj);
};

#endif