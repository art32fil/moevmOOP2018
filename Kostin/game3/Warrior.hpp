#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include "Object.hpp"
#include <string>
#include <functional>

class Warrior : public Object { //explicit??????
private:
    size_t force;
public:
    explicit Warrior(const std::shared_ptr<Crown>& _crown) : Object(_crown){
        std::cout << "\tforce = " << force << std::endl
                  << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                  << std::endl << std::endl;
    }
    explicit Warrior(size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown,
         int hp = 100,  size_t frc = 0) : Object(arg_x, arg_y, _crown, hp), force(frc){
             std::cout << "\tforce = " << force << std::endl
                       << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
                       << std::endl << std::endl;
    }
    ~Warrior(){};
    size_t       &get_force()       {return force;}
    const size_t &get_force() const {return force;}

    char type() override{
        return 'w';
    }

    void move_to_(string s);
    void Attack();

    friend ostream  &operator<< (ostream &out, const Warrior &war);
    friend istream  &operator>> (istream &in, Warrior &war);
};

// ostream &operator<< (ostream &out, const Warrior &warr){  //write to console
//      out << warr.force;
//     return out;
// }

// istream &operator>> (istream &in, const Warrior &warr){  //write to console
//      in >> warr.force;
//     return in;
// } // make it is virtual function if parant class????

istream &operator>> (istream &in, Warrior &warr){  //read from console
    in >> warr.get_coords().axis_x >> warr.get_coords().axis_y
       >> warr.get_hp() >> warr.force;
    return in;
}


void Warrior::move_to_(string s){
    if(s == "up")
        get_coords().axis_y +=1;
    else if(s == "right")
        get_coords().axis_x +=1;
    else if(s == "down")
        get_coords().axis_y -=1;
    else if(s == "left")
        get_coords().axis_x -=1;
    else
        std::cout << "Incorrect data!" << '\n';
}

void Warrior::Attack(){
    
}

#endif
