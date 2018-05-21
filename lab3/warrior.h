#pragma once

#include "object.h"

class War : public Obj
{
	int DMG;
public:
	War(ifstream& F, const shared_ptr<Crown>& C) : Obj(F, C) 
	{
		F >> DMG;
		cout << " warrior.\n";
	} 

	~War()
	{
		cout << " Warrior was killed.\n";
	}

	void move(char cmd)
	{
		if (cmd == 'u')
			Y -= 1;
		if (cmd == 'd')
			Y += 1;
		if (cmd == 'l')
			X -= 1;
		if (cmd == 'r')
			X += 1;
	}

	bool damg(War *it)
	{
		if (it->damage(DMG))
			return true;
		else
			return false;
	}
};