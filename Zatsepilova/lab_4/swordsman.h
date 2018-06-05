#pragma once

#include "warrior.h"


//--------------------------------------SWORDSMAN-------------------------------------------
class Swordsman : public Warrior
{
public:
    Swordsman(shared_ptr<Crown> crown, istream &in);
    Swordsman(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range);
    ~Swordsman();

    // vector<pair<int, int>> aim_attack(List<Object*>& objects) override;
    char draw() override;
    // vector<pair<int, int>> aim_attack() override;
};

//---------------------------------SWORDSMAN METHODS-----------------------------------------
Swordsman::Swordsman(shared_ptr<Crown> crown, istream &in): Warrior(crown, in)  {
    cout << "Swordsman."<< endl;         
}

Swordsman::Swordsman(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range): 
            Warrior(crown, mark, x, y, hp, power, range)  {
    cout << "Magician."<< endl; 
}

Swordsman::~Swordsman() {
    cout << "~Swordsman."<< endl;                
}

char Swordsman::draw(){
    if(alive()) return 's'; 
    else if(!alive()) return 'x';
} 


ostream &operator<<(ostream &out, Swordsman &wr){
    if(wr.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(wr.getcrown()->getcolor() == "red") 
        out << "\033[31m";
    out << wr.draw() << "\033[0m";
    return out;
} 
//----------------------------------------------------------------------------------------
