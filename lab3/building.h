#pragma once

#include "object.h"

class Bld : public Obj
{
public:
	Bld(ifstream &F, const shared_ptr <Crown> &G) : Obj(F, G)
	{
		cout << " building.\n";
	}

	~Bld()
	{
		cout << " Building was destroyed.\n";
	}
};