    #include "unit.h"
#include <iostream>
using namespace std;
unit::unit(int X, int Y, int h, color t)
{
coordinates.x = X;
coordinates.y = Y;
hp = h;
team = t;
cout<< "created a unit on "  << X << " " << Y << " with " << h << " health points" << endl ;
}
/*unit::unit(string info) {

}*/


bool unit::is_there(point coord) {
        if (coord.x == coordinates.x && coordinates.y == coord.y) {
            return true;
        }
        else {
            return false;
        }
}

unit::~unit() {
    const char* R = "RED";
    const char* G ="GREEN";
    /*if (this->team == red) {
       cout << "unit of " << R << " team" << " on " << this->coordinates.x << " " << this->coordinates.y << " " << "was destroyed " << endl;
    }
    else {
         cout << "unit of " << G << " team" << " on " << this->coordinates.x << " " << this->coordinates.y << " " << "was destroyed " << endl;
    }*/
}
int unit::get_damage(int d) {
    hp-=d;
    return hp;
}



