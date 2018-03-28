#ifndef UNIT_H
#define UNIT_H
#include <iostream>
class field;
enum color {
    red, green
};

struct point {
    int x;
    int y;
};

class unit
{
 point coordinates;
 int hp;
 color team;
public:
 friend field;
   // unit (string);
 unit(){

     coordinates.x = 0;
     coordinates.y = 0;
     hp = 100;
     team = red;
 }
 unit(const unit& obj) {
     coordinates= obj.coordinates;
     hp = obj.hp;
     team = obj.team;
 }

    unit(int X, int Y, int h, color t=red);
    ~unit();
    bool is_there(point coord);
    int get_damage(int d);
    bool is_alive() {
        if (hp > 0) {
            return true;
        }
        else {
            return false;
        }
    }


};

#endif // UNIT_H
