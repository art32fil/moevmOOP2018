#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Object.hpp"
#include <vector>


class Building : public Object {
private:
    std::vector<Coordinates> building;
public:
    Building() : Object(){};
    ~Building(){};
    char type() override{
        return 'b';
    }

    friend istream &operator>> (istream &in, Building &bild);
};

istream &operator>> (istream &in, std::vector<Coordinates> v){
    return in;
}

istream &operator>> (istream &in, Building &bild){
    in >> bild.get_coords().axis_x >> bild.get_coords().axis_y
       >> bild.get_hp() >> bild.building;
    return in;
}




#endif
