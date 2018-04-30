#pragma once
#include "list.h"
#include "Object.h"
#include "Crown.h"
#include <memory>


class battlefield
{
	int x_size;
	int y_size;
	List <Object*> *team1 = new List<Object*>;
	List <Object*> *team2 = new List<Object*>;
public:
	battlefield();
    ~battlefield();
	void new_team(List<Object*> *new_team, ifstream& fin,const shared_ptr<Crown>);
	void print();
	int hit(_2dim, int);
	Object* check_position(_2dim);
	void del_from_position(_2dim);
};
