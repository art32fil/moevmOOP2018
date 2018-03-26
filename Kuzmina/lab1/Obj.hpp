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
    Object(int x, int y, int hp);
    Object(ifstream& file);
    Object();
    ~Object();
    
    void getDamage(int);
    bool checkObjCoords(int, int);
    int getHp();
};
#endif
