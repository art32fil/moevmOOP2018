#pragma once
#include "Object.h"
#include <stdio.h>

class Warior :public Object
{
	int force;
public:
	Warior(ifstream& fin, const shared_ptr<Crown> t);
	~Warior();
	
	// thinkaboutittoo friend istream &operator>>(istream &in, Warior &ob);
	friend ostream &operator<<(ostream &out, Warior &ob);
};

