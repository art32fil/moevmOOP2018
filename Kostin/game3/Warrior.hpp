#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include "Object.hpp"
#include "Battlefield.hpp"
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
    virtual void Attack(Object*&);

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

void Warrior::Attack(Object*& tmp){
    if(this->get_crown()->get_color() == "red"){
        tmp->get_Damage(force);
    }else if(this->crown->get_color() == "green"){
        tmp->get_Damage(force);
    }
}

#endif
