#ifndef CROWN
#define CROWN

#include <iostream>
#include <memory>

using namespace std;

int flag = 0;
class Crown{
    const string color;

public:
    Crown(string color);
    Crown();
    ~Crown();

    const string &getcolor() const;
   
};
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

const string &Crown::getcolor() const{ 
    return color;
}


#endif // CROWN
