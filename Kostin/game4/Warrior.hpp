#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <iostream>
#include "Object.hpp"
#include "Building.hpp"
#include "../vector/my_vector.hpp"
#include "../vector/iterator.hpp"
#include <string>
#include <functional>

class Warrior : public Object {
private:
    size_t force;
public:
    Warrior(const std::shared_ptr<Crown>& _crown) : Object(_crown){
        std::cout << "\tforce = " << force << std::endl
                  << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                  << std::endl << std::endl;
    }
    Warrior(size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown,
         int hp = 100,  size_t frc = 0) : Object(arg_x, arg_y, _crown, hp), force(frc){
             std::cout << "\tforce = " << force << std::endl
                       << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                       << std::endl << std::endl;
    }
    ~Warrior(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tforce = " << force << std::endl
                  << "\033[1;31m ~Warrior() \033[0m" << std::endl << std::endl;
    };
    size_t       &get_force()       {return force;}
    const size_t &get_force() const {return force;}

    char type() override{
        return 'w';
    }

    void move_to_(string s);
    virtual void Attack(Object*&, std::tuple<List<Warrior*>&, List<Warrior*>&,
    List<Building*>&, List<Building*>& > &arm);

    friend ostream  &operator<< (ostream &out, const Warrior &war);
    friend istream  &operator>> (istream &in, Warrior &war);
};

ostream &operator<< (ostream &out, const Warrior &warr){  //write to console
     out << dynamic_cast<const Object&>(warr) << warr.force;
    return out;
}

istream &operator>> (istream &in, Warrior &warr){  //read from console
    in >> dynamic_cast<Object&>(warr) >> warr.force;
    return in;
}

void Warrior::move_to_(string s){
    if(s == "up")
        get_coords().axis_y -=1;
    else if(s == "right")
        get_coords().axis_x +=1;
    else if(s == "down")
        get_coords().axis_y +=1;
    else if(s == "left")
        get_coords().axis_x -=1;
    else
        std::cout << "Incorrect data!" << '\n';
}

void erase_elem(Object*& tmp, List<Warrior*> &wrr, List<Building*> &bld) {
	int cnt = 0;
	if(tmp->type()=='w')
		for (auto &el : wrr) {
			if(tmp->get_ID() == el.get_Info()->get_ID())
				wrr.Delete_elem(cnt);
			cnt++;
		}
	else if(tmp->type()=='b')
		for (auto &el : bld) {
			if(tmp->get_ID() == el.get_Info()->get_ID())
				bld.Delete_elem(cnt);
			cnt++;
		}
}

void Warrior::Attack(Object*& tmp, std::tuple<List<Warrior*>&,
	List<Warrior*>&,List<Building*>&, List<Building*>& > &arm){

	tmp->get_Damage(force);

	if(tmp->get_hp() <= 0){
		if(tmp->get_crown()->get_color() == "red")
			erase_elem(tmp, std::get<1>(arm), get<3>(arm));
		if(tmp->get_crown()->get_color() == "green")
	        erase_elem(tmp, std::get<0>(arm), get<2>(arm));
	}
}

#endif
