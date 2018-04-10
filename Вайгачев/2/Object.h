#pragma once
#include <fstream>
#include <iostream>
#include <memory>

using namespace std;
struct _2dim {
		int x;
		int y;

	};
class Object
{
	
	_2dim pos;
	int health;
	const shared_ptr<int> team;
	const int id;

public:

	static int amount;
	static int count;
	Object()  ;
	Object(_2dim, int ,int);
	Object(ifstream&, const shared_ptr<int> ) ;
	~Object();
	Object(const Object & obj);
	
	int get_id();
	int show_health();

	int show_team();
	int get_damage(int damage);
	Object* is_on_position(_2dim);
	bool last_representive();

	long use_count();

	friend istream &operator>>(istream &in, Object &ob);
	friend ostream &operator<<(ostream &out, Object &ob);

	
};

