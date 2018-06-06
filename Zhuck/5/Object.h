#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include "Crown.h"

using namespace std;
struct _2dim {
		int x;
		int y;

		friend bool operator==(const _2dim a,const _2dim b);

	};

class Object
{

private:
	int health;
	const shared_ptr<Crown> team;
	const int id;
	

protected:
	const char type;
	_2dim pos;

public:

	static int amount;
	static int count;
	Object()  ;
	Object(_2dim, int , const shared_ptr<Crown> , char );
	Object(ifstream&, const shared_ptr<Crown > ,char) ;
	virtual ~Object();
	Object(const Object & obj);

	int get_id();
	int show_health();

	int show_team();
	int get_damage(int damage);
	virtual Object* is_on_position(_2dim);
	bool last_representive();

	const _2dim get_coords();
	virtual void print(ostream &out) {};

	long use_count();

	friend istream &operator>>(istream &in, Object &ob);
	friend ostream &operator<<(ostream &out, Object &ob);

	virtual void show_stats();
	virtual bool is_a_building() { return  false; };
	char get_type();

	virtual Object* spawn() { return NULL; };


	

};



