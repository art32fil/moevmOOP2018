#pragma once

#include "list.h"
#include "object.h"
#include "Iter.h"
#include <map>

#define info pair<char, char> 

class BF
{
	public:
		int xs, ys, A1s, A2s;
		List<Obj*> A1, A2;
		Obj *it;
		map<int, map<int, info > >mapBF;

		BF(ifstream&);
		~BF();

		bool checkfield(int,int);
		void damagefield(int);
		void makemap();
		void showmap();
		void color(char);
};