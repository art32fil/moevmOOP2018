#ifndef MAGICIAN_HPP
#define MAGICIAN_HPP

#include "Warrior.hpp"

class Magician: public Warrior {
private:

public:
	Magician (const std::shared_ptr<Crown>& _crown) : Warrior(_crown){

	}
	Magician (size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown,
         int hp = 100,  size_t frc = 0) : Warrior(arg_x, arg_y, _crown, hp, frc){

	}

	~Magician ();
	void Attack() override; //attacked the object with minimal hit points and all different Object
	// on the line attack (луч атаки имеет ограниченную дальность)
	char type() override{
        return 'm';
    }
	using Warrior::operator<<;
};

void Magician::Attack(){

}

/**/

#endif
