#pragma once
#ifndef Obj_hpp
#include <fstream>
#include "Crown.hpp"

using namespace std;

class Object {
private:
    int x;
    int y;
    int hp;
    char type;
    const int id;
    static int count;
    static int amount;
    const std::shared_ptr<Crown> crown;
public:
    Object(ifstream& file, const std::shared_ptr<Crown> _crown);
    ~Object();
    void getDamage(int);
    bool checkObjCoords(int, int);
    int& getX(); 
    int& getY();
    int getHp();
    char& getType();
    friend ostream  &operator<< (ostream &out, const Object &o){  //перегрузка оператора
        out << o.x << o.y << o.hp << o.id << o.crown;
        return out;
    }
    /*friend istream  &operator>> (istream &in, const Object &o){  //write to console
        in >> o.x >> o.y >> o.hp;
        return in;
    }*/
    Object() : id(count++){
        amount++;
    }
};
#endif
