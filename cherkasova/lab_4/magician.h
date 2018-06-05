#pragma once

#include "warrior.h"


//--------------------------------------MAGNICIAN-------------------------------------------
class Magician : public Warrior
{
public:
    // Magician() {}
    Magician(shared_ptr<Crown> crown, istream &in);
    Magician(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range);
    
    ~Magician();

    char draw() override;
    // vector<pair<int, int>> aim_attack() override;
};


//---------------------------------MAGICIAN-METHODS-----------------------------------------
Magician::Magician(shared_ptr<Crown> crown, istream &in): Warrior(crown, in) {
    cout << "Magician."<< endl;         
}

Magician::Magician(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range): 
            Warrior(crown, mark, x, y, hp, power, range)  {
    cout << "Magician."<< endl; 
}

Magician::~Magician() {
    cout << "~Magician."<< endl;                 
}

char Magician::draw(){
    if(alive()) return 'm'; 
    else if(!alive()) return 'x';
} 

// vector<pair<int, int>> Magician::aim_attack(){
//     vector<pair<int, int>> aim;
//     aim.push_back(pair<int, int>(getx(), gety()));
//     for (int i = 0; i <= range; i++) {
//     	for (int j = 0; j <= range; j++) {
//     		if (i == 0 && j == 0) continue;
//     		aim.push_back(pair<int, int>(getx() + i, gety() + j));
//     		aim.push_back(pair<int, int>(getx() - i, gety() - j));
//     		aim.push_back(pair<int, int>(getx() - i, gety() + j));
//     		aim.push_back(pair<int, int>(getx() + i, gety() - j));
//     	}
//     }
//     return aim;
// }

ostream &operator<<(ostream &out, Magician &wr){
    if(wr.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(wr.getcrown()->getcolor() == "red") 
        out << "\033[31m";
    out << wr.draw() << "\033[0m";
    return out;
} 
//----------------------------------------------------------------------------------------
