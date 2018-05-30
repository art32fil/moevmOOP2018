#pragma once
#include "list.h"
#include "Object.h" //delete later

#include "Warior.h"
#include "Swordsman.h"
#include "Building.h"
#include "Magikan.h"
#include "Crown.h"
#include <memory>
#include <vector>


class battlefield
{
	int x_size;
	int y_size;
	std::vector <Object*> *team1 = new std::vector<Object*>;
	std::vector <Object*> *team2 = new std::vector<Object*>;
	std::vector <Object* > temp ;

public:
	battlefield();
    ~battlefield();
	void new_team(std::vector <Object*> *new_team, ifstream& fin,const shared_ptr<Crown>);
	void print();

	//reconstruction
	int command_to_attack(int);
	void del_by_id(int);
	
	vector <Object* > return_temp();


	Object* check_position(_2dim);
	//void del_from_position(_2dim);
	Warior *relocate(string da_way, Warior *unit);
	Object* select_by_id(int);
	void select_by_coords(_2dim);
	char define_type(Object *);
	friend battlefield *const operator<<(battlefield *const bf, Object &obj);
	std::vector<Object*>* list_of_enemies(Object *);
	std::vector<Object*>* list_of_friends(Object *);
	void add_unit(int);
};
