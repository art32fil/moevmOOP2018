#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include "Object.hpp"
#include <string>
#include <functional>

class Warrior : public Object {
private:
    size_t force;
public:
    Warrior(size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown, size_t frc,
         int hp = 100) : Object(arg_x, arg_y, _crown, hp), force(frc){
        // std::cout << "\tx = " << coords.axis_x << std::endl
        //           << "\ty = " << coords.axis_y << std::endl
        //           << "\thp = " << hit_points << std::endl
        //           << "\tcrown = " << crown->get_color() << std::endl
        //           << "\tID = " << ID << std::endl
        //           << "\tcount = " << count << std::endl
        //           << "\033[1;32m Warrior(size_t, size_t, int, int) \033[0m"
        //           << std::endl << std::endl;
    }
    ~Warrior();
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

ostream &operator<< (ostream &out, const Warrior &warr){  //write to console
     out << warr.force;
    return out;
}

istream &operator>> (istream &in, Warrior &warr){  //read from console
    in >> /*Warrior::Object >>*/ warr.force;
    return in;
}

// constexpr size_t operator ""_hash(string s){
//         std::hash<string> hash_;
//     return hash_(s);
// }

void Warrior::move_to_(string s){
    // std::hash<string> hash_;
    // //constexpr up = hash_("up"), down = hash_("down");
    // //size_t right = hash_("right"), left = hash_("left");
    // switch (hash_(s)) {
    //     case "up"_hash :
    //         get_coords().axis_y +=1;
    //     break;
    //     case down:
    //         get_coords().axis_y -=1;
    //     break;
    //     case right:
    //         get_coords().axis_x +=1;
    //     break;
    //     case left:
    //         get_coords().axis_x -=1;
    //     break;
    //     default:
    //         std::cout << "Incorrect data!" << '\n';
    //         break;
    // }
}

void Warrior::Attack(){

}

#endif
