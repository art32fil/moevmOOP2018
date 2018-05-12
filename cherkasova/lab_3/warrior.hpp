#ifndef WARRIOR
#define WARRIOR

#include <iostream>
#include <fstream>
#include "object.hpp"

using namespace std;


//--------------------------------------WARRIOR-------------------------------------------
class Warrior : public Object{
    int power;

public:
    Warrior(shared_ptr<Crown> crown, istream &in);
    ~Warrior();

    int move_to(char action, int border_x, int border_y) override;
    int &getpower() override;
    // void print_ob_simple();
    
    char draw() override;

    friend istream &operator>>(istream &in, Warrior &wr);
    friend ostream &operator<<(ostream &out, Warrior &wr);
};
//-----------------------------------------------------------------------------------------


//---------------------------------WARRIOR-METHODS------------------------------------------
Warrior::Warrior(shared_ptr<Crown> crown, istream &in): Object(crown, in) {
    in >> *this;
    cout << "Warrior:"<< endl 
         << "    power = " << this->power << endl
         << "Warrior." <<endl; 
}

Warrior::~Warrior() {
    cout << "~Warrior:"<< endl 
         << "    power = " << this->power << endl
         << "~Warrior." <<endl; 
}

char Warrior::draw(){
    if(alive()) return 'w'; 
    else if(!alive()) return 'x';
} 

istream &operator>>(istream &in, Warrior &wr){
    in >> wr.power;
}

ostream &operator<<(ostream &out, Warrior &wr){
    if(wr.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(wr.getcrown()->getcolor() == "red") 
        out << "\033[31m";
    out << wr.draw() << "\033[0m";
    return out;
} 

int Warrior::move_to(char action, int border_x, int border_y){
    int try_act = 0;
    switch(action){
        case 'u':
            try_act = gety() - 1;
            if(try_act >= 0 && try_act <= border_y)
                gety() -= 1;
                else return -1;
            break;
        case 'd':
            try_act = gety() + 1;
            if(try_act >= 0 && try_act <= border_y)
                gety() += 1;
            else return -1;
            break;
        case 'r':
            try_act = getx() + 1;
            if(try_act >= 0 && try_act <= border_x)
                getx() += 1;
            else return -1;
            break;
        case 'l':
            try_act = getx() - 1;
            if(try_act >= 0 && try_act <= border_x)
                getx() -= 1;
            else return -1;
            break;
        default:
            return -1; //cout << "Incorrect data!" << '\n'; 
    }
    return getid();
}

// void Warrior::print_ob_simple(){ 
//     cout << "[ " << getmark() << " " << getid() << " " << getx() << " " << gety() << " " << gethp() << " " << power << " ]" << endl; 
// }

int &Warrior::getpower()
    {return this->power;}


//-----------------------------------------------------------------------------------------


#endif // WARRIOR