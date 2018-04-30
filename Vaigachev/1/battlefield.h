#pragma once
#include "list.h"
#include "Object.h"
//#include "list.cpp" // ?-----?

class battlefield
{
	int x_size;
	int y_size;
	List <Object*> *team1 = new List<Object*>;
	List <Object*> *team2 = new List<Object*>;
public:
	battlefield();
    ~battlefield();
	void new_team(List<Object*> *new_team, ifstream& fin,int);
	void print();
	Object* check_position(_2dim);
};

