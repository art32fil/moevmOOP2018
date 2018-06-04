#pragma once
#include "Object.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <vector>

class Warior :public Object
{
	int force;
public:
	Warior(ifstream& fin, const shared_ptr<Crown> t,char type);
	Warior(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type);
	Warior(const Warior & W);
	~Warior();
	Warior* move(char option);
	int give_force();
	virtual int attack(std::vector <Object*>*);
	virtual void show_stats();
	void print(ostream &out);
	// thinkaboutittoo friend istream &operator>>(istream &in, Warior &ob);
	friend ostream &operator<<(ostream &out, Warior &ob);

	void del_by_id(int id, std::vector <Object*>* enem);
	virtual Object* available_rivals(Object*);
};

