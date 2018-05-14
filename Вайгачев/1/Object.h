#pragma once
#include <fstream>
#include <iostream>

using namespace std;
struct _2dim {
		int x;
		int y;
	};
class Object
{
	
	_2dim pos;
	int health;
	int team;	
public:
	
	Object() {};
	Object(_2dim, int ,int);
	Object(ifstream& ,int);
	~Object();
	Object(const Object & obj);
	int show_health();
	int show_team();
	void get_damage(int damage);
	Object* is_on_position(_2dim);
	

};

