#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <fstream>
#include <tuple>
#include "list.h"
#include "crown.h"

using namespace std;

class Object {
private:
	int x, y, hp;
	int id;
 	shared_ptr<Crown> crown;
	static int count;
	static int amount;
public:
	Object(int x, int y, int hp, const shared_ptr<Crown> crown);
	Object(ifstream& f, const shared_ptr<Crown>& clr);
	Object() {}
	virtual ~Object();

	int damage(int dmg);
	virtual int isObject(int x1, int y1);
	bool isDead();

	virtual void move_up() {}
	virtual void move_down(){}
	virtual void move_right(){}
	virtual void move_left(){}
	

	virtual List<tuple<int, int, int>>* ld_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* rd_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* ru_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* lu_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* right_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* left_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* up_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* down_range() { exit(EXIT_FAILURE); }
	virtual List<tuple<int, int, int>>* attack() { exit(EXIT_FAILURE); }
	virtual int get_x1(int x) { return -1; }
	virtual int get_y1(int y) { return -1; }
	
	
	virtual Object* create(int x, int y, int hp, int force, const shared_ptr<Crown> crown) {	exit(EXIT_FAILURE);}
	int& get_x(){return x;}
	const int& get_x() const{return x;}
	int& get_y(){return y;}
	const int& get_y() const{return y;}
	int& get_hp(){return hp;}
	const int& get_hp()const{return hp;}
	shared_ptr<Crown>& get_crown() { return crown; }
	const shared_ptr<Crown>& get_crown()const { return crown; }

	
	friend istream& operator >> (istream &s, Object &obj);
	friend ostream& operator << (ostream& s, const Object& obj);
	bool operator == (const Object& obj);
};

#endif