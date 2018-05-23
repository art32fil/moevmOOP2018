#ifndef SWORDSMAN_HPP
#define SWORDSMAN_HPP

#include "Warrior.hpp"

class Swordsman : public Warrior {
private:

public:
	Swordsman (const std::shared_ptr<Crown>& _crown) : Warrior(_crown){

	}
	Swordsman (size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown,
         int hp = 100,  size_t frc = 0) : Warrior(arg_x, arg_y, _crown, hp, frc){

	}
	~Swordsman ();
	void Attack() override; //attacked the object with minimal hit points at adjoining cell
	char type() override{
        return 's';
    }
	using Warrior::operator<<;
};

void Swordsman::Attack(){

}
#endif
