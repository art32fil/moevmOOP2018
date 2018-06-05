 #pragma once
#include "object.h"
#include "swordsman.h"
#include "magician.h"
#include "warrior.h"

using namespace std;

//--------------------------------------WARRIOR-------------------------------------------
template <typename T>
class Building : public Object
{
    vector<pair<int, int>> location;

public:
    Building(shared_ptr<Crown> crown, char mark, int &x, int &y, int &hp, vector<pair<int, int>> &location);
    ~Building();

    // void print_ob_simple();
    char draw() override;    
    vector<pair<int, int>> &getlocation() override;
    T* production(int x, int y);

    friend ostream &operator<<(ostream &out, Building &bd);
};
//-----------------------------------------------------------------------------------------


//---------------------------------WARRIOR-METHODS------------------------------------------
template <typename T>
Building<T>::Building(shared_ptr<Crown> crown, char mark, int &x, int &y, int &hp, vector<pair<int, int>> &location): 
            Object(crown, mark, x, y, hp), location(location){
    cout << "Building:"<< endl;
    int count = 0; 
    for(const auto &coord: location){
        cout <<"    x" << count << " = " << get<0>(coord) << endl;
        cout <<"    y" << count++ << " = " << get<1>(coord) << endl;
    }
    cout << "Building." <<endl; 
}

template <typename T>
Building<T>::~Building() {
    cout << "~Building:"<< endl;
    int count = 0; 
    for(const auto &coord: location){
        cout <<"    x" << count << " = " << get<0>(coord) << endl;
        cout <<"    y" << count << " = " << get<1>(coord) << endl;
    }
    cout << "~Building." <<endl; 
}

template <typename T>
char Building<T>::draw() {
    if(alive()) return 'b'; 
    else if(!alive()) return 'x';
} 

template <typename T>
ostream &operator<<(ostream &out, Building<T> &bd){
    if(bd.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(bd.getcrown()->getcolor() == "red")
        out << "\033[31m";
    out << bd.draw() << "\033[0m";
    return out;
}

template <typename T>
T* Building<T>::production(int x, int y){ //порождение объектов
    T* obj = new T(getcrown()->getcolor());
    return obj;
}

template <>
Warrior* Building<Warrior>::production(int x, int y) { 
    shared_ptr<Crown> cr = shared_ptr<Crown>(new Crown(getcrown()->getcolor()));
    Warrior* wr = new Warrior(cr, 'w', x, y, 80, 100, 0);
    return wr;
}

template <>
Swordsman* Building<Swordsman>::production(int x, int y) { 
    shared_ptr<Crown> cr = shared_ptr<Crown>(new Crown(getcrown()->getcolor()));
    Swordsman* wr = new Swordsman(cr, 's', x, y, 100, 50, 1);
    return wr;
}

template <>
Magician* Building<Magician>::production(int x, int y) { 
    shared_ptr<Crown> cr = shared_ptr<Crown>(new Crown(getcrown()->getcolor()));
    Magician* wr = new Magician(cr, 'm', x, y, 50, 50, 4);
    return wr;
}
// void Building<T>::print_ob_simple() { 
//     cout << "[ " << getmark() << " " << getid() << " " << getx() << " " << gety() << " " << gethp() << " " ;
//     int count = 0; 
//     for(const auto &coord: location){
//         cout << get<0>(coord) << " " << endl;
//         cout << get<1>(coord) << " " << endl;
//     }
//     cout << " ]" << endl; 
// }

template <typename T>
vector<pair<int, int>> &Building<T>::getlocation() {
    return location;
} 

//-----------------------------------------------------------------------------------------