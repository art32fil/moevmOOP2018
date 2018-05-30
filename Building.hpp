#pragma once
#include "Object.hpp"
#include <vector>
using namespace std;
ostream &operator<< (ostream &out, vector<Position> const &v){
    for(auto &el : v){
        cout << el << ' ';
    }
    if(v.empty())
        cout << "empty" << '\n';
    return out;
}

class Building : public Object {
private:
    vector<Position> building;
public:
    Building(const shared_ptr<Crown>& _crown) : Object(_crown){
        cout << "\tBuilding = " << building <<  endl  //buildint trow error like lvalue
                  << "\033[1;32m Building(size_t, size_t, ...) \033[0m"
                  << endl << endl;
    };
    Building(size_t arg_x, size_t arg_y, const shared_ptr<Crown> _crown, vector<Position> v,
         int hp = 100) : Object(arg_x, arg_y, _crown, hp), building(v){};

    ~Building(){
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                  << "\tforce = " << building << endl
                  << "\033[1;31m ~Building() \033[0m" << endl << endl;
    };

    vector<Position>       &get_building()       {return building;}
    const vector<Position> &get_building() const {return building;}

    char type() override{
        return 'b';
    }

    friend istream &operator>> (istream &in, Building &bild);
    friend istream &operator>> (istream &in, vector<Position> v);
    friend ostream &operator<< (ostream &out, vector<Position> v);
};

istream &operator>> (istream &in, vector<Position> &v){
    size_t i = 0, x, y;
    in >> i;
    for(size_t k = 0; k < i; k++){
        in >> x >> y;
        v.push_back({x,y});
    }
    return in;
}

istream &operator>> (istream &in, Building &bild){
    in >> static_cast<Object &>(bild) >> bild.building;
    return in;
}


