#pragma once
#ifndef building_hpp
#include "Obj.hpp"
#include <tuple>
#include <vector>

using namespace std;

class Building : public Object {
    vector<tuple<int, int>> location;
public:
    Building(ifstream& file, const shared_ptr<Crown>);
    ~Building();
    
    vector<tuple<int, int>> getLocation();
    bool Is_Build_Located(int y1, int x1);
};
#endif
