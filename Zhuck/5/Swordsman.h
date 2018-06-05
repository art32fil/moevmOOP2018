#pragma once
#include "Warior.h"
#include <iostream>

class Swordsman :
	public Warior
{
public:
	Swordsman(ifstream& fin, const shared_ptr<Crown> t, char type);
	Swordsman(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type);
	Swordsman(const Swordsman & S);
	~Swordsman();
	void print(std::ostream &out);
	int attack(std::vector <Object*>*);
	Object* available_rivals(Object*);
};

