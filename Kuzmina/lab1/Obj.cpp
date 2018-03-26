#include "Obj.hpp"
#include <iostream>

using namespace std;

Object::Object(int x, int y, int hp) : x(x), y(y), hp(hp){
    cout << "Object:" << endl
    << "    x = " << x << endl
    << "    y = " << y << endl
    << "    hp = " << hp << endl;
    cout << "Object." << endl;
}

Object::Object(ifstream& file){
    file >> x >> y >> hp;
    cout << "Object:" << endl
    << "    x = " << x << endl
    << "    y = " << y << endl
    << "    hp = " << hp << endl;
}

Object::Object() {
    x = y = hp = 0;
}

Object::~Object(){
    cout << "~Object:" << endl
    << "    x = " << x << endl
    << "    y = " << y << endl
    << "    hp = " << hp << endl;
    cout << "~Object." << endl;
}

void Object::getDamage(int damage) {
    hp -= damage;
}

bool Object::checkObjCoords(int yCoord, int xCoord) {
    if (xCoord == x && yCoord == y) return true;
    return false;
}

int Object::getHp() {
    return hp;
}

