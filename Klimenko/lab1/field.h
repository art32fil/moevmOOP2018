#ifndef FIELD_H
#define FIELD_H
#include "container.h"
#include "unit.h"
#include <fstream>
//#include "unit.cpp"


class field
{
    int Xsize;
    int Ysize;
public:
    container<unit> red_army;
    container<unit> green_army;

    void create_unit(int x, int y, int h, color c);
	void enter(ifstream &fin);
    field() { Xsize = Ysize = 0;}
    field(int x, int y);
    void drow_field();



};

#endif // FIELD_H
