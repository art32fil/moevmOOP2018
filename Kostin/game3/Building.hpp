#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Object.hpp"


class Building : public Object {
private:
public:
    Building();
    ~Building();
    char type() override{
        return 'b';
    }
};


#endif
