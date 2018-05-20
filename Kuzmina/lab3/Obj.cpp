#include "Obj.hpp"
#include <iostream>

using namespace std;

int Object::amount = 0;
int Object::count = 0;

Object::Object(ifstream& file,const std::shared_ptr<Crown> _crown):crown(_crown), id(count++){
    file >> x >> y >> hp;
    cout << "Object:" << endl
    << "    x = " << x << endl
    << "    y = " << y << endl
    << "    hp = " << hp << endl
    << "    crown = " << crown->get_color()<<endl
    << "    id = " << id << endl
    << "Object." << endl;
    amount++; 
}

Object::~Object(){
    cout << "~Object:" << endl
    << "    x = " << x << endl
    << "    y = " << y << endl
    << "    hp = " << hp << endl
    << "    crown = " << crown->get_color()<<endl
    << "    id = " << id << endl
    << "~Object." << endl;
    amount--;
}

void Object::getDamage(int damage) {
    hp -= damage;
    if(amount==0)
        exit(EXIT_SUCCESS);
}
bool Object::checkObjCoords(int yCoord, int xCoord) {
    if (xCoord == x && yCoord == y) return true;
    return false;
}
int& Object::getX() {
    return x;
}
int& Object::getY() {
    return y;
}
int Object::getHp() {
    return hp;
}
char& Object::getType() {
    return type;
}
