#pragma once

#include "list.h"
#include "object.h"
#include "iter.h"
#include <map>

#define info pair<char, char> 
#define cur pair<int, int>

class BF
{
	int xs, ys, A1s, A2s;
	List<Obj*> A1, A2;
	map<int, map<int, info > >mapBF;
	cur path;
public:
	BF(ifstream&);
	~BF();

	bool checkfield(int, int);
	int damagefield(int);
	void makemap();
	void showmap();
	void color(char);

	friend ostream& operator << (ostream &out, BF &game)
	{
		game.showmap();
		return out;
	}

	friend ifstream& operator >> (ifstream &fin, BF &game)
	{
		fin >> game.xs >> game.ys;
		return fin;
	}
};