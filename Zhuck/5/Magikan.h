#pragma once
#include "Warior.h"
#include <map>
class Magikan :
	public Warior
{
	int range;
	std::map<int, vector<Object*>> info_directions;
	int last_dir;
public:
	Magikan(std::ifstream& fin, const shared_ptr<Crown> t, char type);
	Magikan(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type, int range);
	Magikan(const Magikan & M);

	~Magikan();
	void print(std::ostream &out);
	int attack(std::vector <Object*>*);
	Object* available_rivals(Object*);
};

