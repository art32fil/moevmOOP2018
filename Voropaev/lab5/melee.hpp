#pragma once
#include "Warrior.hpp"
using namespace std;
class Melee: public Warrior
{
  public:
	Melee(size_t arg_x, size_t arg_y, const shared_ptr<Crown> _crown, 
		int hp = 100, int force) : Warrior(arg_x, arg_y, _crown, hp,force)
		{
			cout << "Melee Warrior: "<<endl;
			cout << "Melee Warrior created."<<endl;
		}

	~Melee()
	{
		cout << "~Melee:"<<endl;
		cout << "~Melee destroyed."<<endl;
	}

	const char get_type() override
	{
		return 'm';
	}

	void Attack(Object*&)
	{
		
	}
}
