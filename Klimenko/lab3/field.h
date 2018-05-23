#ifndef FIELD_H
#define FIELD_H

#include "list.h"
#include "Object.h" //delete later

#include "Warrior.h"
#include "Building.h"
#include "Crown.h"
#include <memory>
#include <vector>


class battlefield
{
	int x_size;
	int y_size;
	List <Object*> *team1 = new List<Object*>;
	List <Object*> *team2 = new List<Object*>;
public:
	battlefield();
	~battlefield();
	void new_team(List<Object*> *new_team, ifstream& fin, const shared_ptr<Crown>);
	void print();

	//reconstruction
	int hit(_2dim, int);
	void del_by_id(int);


	Object* check_position(_2dim);
	void del_from_position(_2dim);
	Warior *relocate(string da_way, Warior *unit);
	Object* select_by_id(int);
	vector <Object *>* select_by_coords(_2dim);
	char define_type(Object *);
	friend battlefield *const operator<<(battlefield *const bf, Object &obj);
};

#endif FIELD_H