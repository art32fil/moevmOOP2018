#pragma once
#include "Object.hpp"
#include "Battlefield.hpp"
#include <string>
#include <functional>
using namespace std;
class Warrior : public Object {
private:
    size_t force;
public:
    Warrior(const shared_ptr<Crown>& _crown) : Object(_crown){
        cout << "\tforce = " << force << endl
                  << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                  << endl << endl;
    }
    Warrior(size_t arg_x, size_t arg_y, const shared_ptr<Crown> _crown,
         int hp = 100,  size_t frc = 0) : Object(arg_x, arg_y, _crown, hp), force(frc){
             cout << "\tforce = " << force << endl
                       << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                       << endl <<endl;
    }
    ~Warrior(){
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                  << "\tforce = " << force << endl
                  << "\033[1;31m ~Warrior() \033[0m" << endl << endl;
    };
    size_t       &get_force()       {return force;}
    const size_t &get_force() const {return force;}

    char type() override{
        return 'w';
    }

    void move_to_(char s);
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

void Warrior::move_to_(char s){
    if(s == 'u')
        get_coords().y -=1;
    else if(s == 'r')
        get_coords().x +=1;
    else if(s == 'd')
        get_coords().y +=1;
    else if(s == 'l')
        get_coords().x -=1;
    else
        cout << "Incorrect data!" << '\n';
}

void Warrior::Attack(Object*& tmp){
    if(this->get_crown()->get_color() == "red"){
        tmp->get_Damage(force);
    }else if(this->crown->get_color() == "green"){
        tmp->get_Damage(force);
    }
}


