#pragma once

#include "warrior.h"


//--------------------------------------SWORDSMAN-------------------------------------------
class Swordsman : public Warrior
{
public:
    // Swordsman() {}    
    Swordsman(shared_ptr<Crown> crown, istream &in);
    Swordsman(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range);
    ~Swordsman();

    vector<pair<int, int>> aim_attack(List<Object*>& objects) override;
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

vector<pair<int, int>> Swordsman::aim_attack(List<Object*>& objects){
    int max_hp = 0;
    pair<int,int> max_pair;


    vector<int> hps;
    vector<int> ids;    
    for(const auto& obj: objects){
        if( obj.get()->getx() == this->getx() + 1 && obj.get()->gety() == this->gety() ||
            obj.get()->getx() == this->getx() - 1 && obj.get()->gety() == this->gety() || 
            obj.get()->getx() == this->getx() + 1 && obj.get()->gety() == this->gety() - 1 ||
            obj.get()->getx() == this->getx() - 1 && obj.get()->gety() == this->gety() + 1) {
            max_hp = obj.get()->gethp();
            max_pair = make_pair(obj.get()->getx(), obj.get()->gety());
            break;
        }
    }
    cout <<"max = " << max_hp <<endl;
    vector<pair<int, int>> aim;
    
    if(max_hp==0) return aim;
    for(const auto& obj: objects){
        if( obj.get()->getx() == this->getx() + 1 && obj.get()->gety() == this->gety() ||
            obj.get()->getx() == this->getx() - 1 && obj.get()->gety() == this->gety() || 
            obj.get()->getx() == this->getx() + 1 && obj.get()->gety() == this->gety() - 1 ||
            obj.get()->getx() == this->getx() - 1 && obj.get()->gety() == this->gety() + 1) {
            if(obj.get()->gethp() < max_hp){
                max_hp = obj.get()->gethp();
                max_pair = make_pair(obj.get()->getx(), obj.get()->gety());
            }
        }
    }
    aim.push_back(max_pair);
    
    return aim;
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
