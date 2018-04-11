#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include "Object.hpp"
#include <string>

class Warrior : public Object {
private:
    size_t force;
public:
    Warrior(size_t frc, const shared_ptr<Crown> crown_) : Object(crown_), force(frc){}
    ~Warrior();
    move_to_(string s){
        switch (s) {
            case "up":
                get_coords().axis_y +=1;
            break;
            case "down":
                get_coords().axis_y -=1;
            break;
            case "right":
                get_coords().axis_x +=1;
            break;
            case "left":
                get_coords().axis_x -=1;
            break;
            default:
                std::cout << "Incorrect data!" << '\n';
                break;
        }
    }
    Attack(){
        
    }
};

#endif
