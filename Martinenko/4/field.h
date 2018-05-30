#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <string>
#include "list.h"
#include "object.h"
#include "warrior.h"
#include "swordsman.h"
#include "magician.h"
#include "building.h"

using namespace std;

class Field {
	List<Object*> armyA;
	weak_ptr<Crown> clrA;
	List<Object*> armyB;
	weak_ptr<Crown> clrB;
	int x_size, y_size;
	int size_A, size_B;
public:
	Field(ifstream &f);
	~Field();
	int get_hp(string clr, int x, int y);
	tuple<int, int> min_range(string clr, List<tuple<int, int, int>>* range);
	void getA(ifstream&f, const shared_ptr<Crown>& color);
	void getB(ifstream&f, const shared_ptr<Crown>& color);
	void paint();
	void move(string clr,int x, int y,string dir);
	void add_warrior(string clr, int x, int y) {
		if(clr == "red"){
			for (auto it : armyA) {
				if (it->isObject(x, y) == 3) { 
					int x1, y1, hp, force;
					cout << "Input the data of object (x, y, hp , force):";
					cin >> x1 >> y1 >> hp >> force;
					armyA.pushBack(it->create(x1, y1, hp, force, it->get_crown()));
					break;
				}
			}

		}
		else if(clr == "green"){
			for (auto it : armyB) {
				if (it->isObject(x, y) == 3) {
					int x1, y1, hp, force;
					cout << "Input the data of object (x, y, hp , force):" << endl;
					cin >> x1 >> y1 >> hp >> force;
					armyB.pushBack(it->create(x1, y1, hp, force, it->get_crown()));
					break;
				}
			}
		}

	}
	
	bool isArmyA();
	bool isArmyB();
	bool isIt(string clr, string kind, int x1, int y1);
	bool attack(string clr, string kind, int x1, int y1);
	
	friend istream& operator >>(istream& s, Field& fld);
	friend ostream& operator <<(ostream& s, const Field& fld);
};
#endif
