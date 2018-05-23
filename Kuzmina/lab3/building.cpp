#include <iostream>
#include "building.hpp"
using namespace std;




Building::Building(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
    getType() = 'b';
    int size;
    file >> size;
    for (int i = 0; i < size; i++) {
        int x, y;
        file >> x >> y;
        location.push_back(tuple<int, int>(x, y));
    }
    cout << "Building:" << endl;
    for (int i = 0; i < location.size(); i++) {
        cout << "    x" << i <<" = " << get<0>(location[i]) << endl;
        cout << "    y" << i <<" = " << get<1>(location[i]) << endl;
    }
    cout << "Building." << endl;
}

Building::~Building() {
    cout << "~Building:" << endl;
    for (int i = 0; i < location.size(); i++) {
        cout << "    x" << i << " = " << get<0>(location[i]) << endl;
        cout << "    y" << i << " = " << get<1>(location[i]) << endl;
    }
    cout << "Building." << endl;
}

vector<tuple<int, int>> Building::getLocation() {
    return location;
}

bool Building::Is_Build_Located(int y1, int x1) {
    for (int i=0; i<location.size(); i++){
        if (x1 == get<0>(location[i]) && y1 == get<1>(location[i])) return true;
    }
    return false;
}
