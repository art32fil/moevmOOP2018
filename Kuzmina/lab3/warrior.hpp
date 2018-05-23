#pragma once
#ifndef warrior_hpp
#include <tuple>
#include "Obj.hpp"
#include "Field.hpp"
using namespace std;

class Warrior : public Object {
    int force;
    int range;
public:
    Warrior(ifstream& file, const shared_ptr<Crown>);
    ~Warrior();
    
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    
    vector<tuple<int, int>> attack();
    int get_force();
};
#endif
