#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Object.hpp"


class Building : public Object {
private:
    std::vector<Coordinates> v;
public:
    Building() : Object();
    ~Building(){};
    char type() override{
        return 'b';
    }
};


#endif
