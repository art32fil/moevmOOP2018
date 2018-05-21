#pragma once

#include "list.h"
#include "warrior.h"
#include "building.h"
#include "iter.h"
#include <map>
#include <vector>

#define info pair<char, char> 

class BF
{
	bool turn = true;
	int xs, ys, A1s, A2s;
	List<War*> A1war, A2war;
	List<Bld*> A1bld, A2bld;
	map<int, map<int, info > >mapBF;
	War *cur = NULL;
	int index;
public:
	BF(ifstream&);
	~BF();

	bool checkfield(int, int);
	void makemap();
	void showmap();
	void color(char);
	bool play();

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