#pragma once

#include <iostream>
#include <memory>

using namespace std;

int flag = 0;
//--------------------------------------CROWN----------------------------------------------
class Crown{
    const string color;

public:
    Crown(string color);
    Crown();
    ~Crown();

    const string &get_color() const;
   
};
//------------------------------------CROWN-METHODS----------------------------------------
Crown::Crown(const string color): color(color){
    cout << "Crown:\n";
    cout << "   color = " << color << endl;
    cout << "Crown.\n";
}

Crown::Crown(){
    cout << "Crown:\n";
    cout << "   color = " << color << endl;
    cout << "Crown.\n";
}

Crown::~Crown(){
    cout << "~Crown:\n";
    cout << "   color = " << color << endl;
    cout << "~Crown.\n";
    if(flag) cout << "~Field.\n"; 
    flag = 1;
}

const string &Crown::get_color() const{ 
    return color;
}

//-----------------------------------------------------------------------------------------



