#pragma once
#ifndef Obj_hpp
#include <fstream>

using namespace std;

class Object {
private:
    int x;
    int y;
    int hp;
public:
    Object(ifstream& file);
    ~Object();
    
    void getDamage(int);
    bool checkObjCoords(int, int);
    int getHp();
};
#endif
