#pragma once
#include "object.h"
// #include "swordsman.hpp"
// #include "magician.hpp"


using namespace std;


//--------------------------------------WARRIOR-------------------------------------------
class Warrior : public Object
{
    int power;
    int range;

public:
    Warrior(shared_ptr<Crown> crown, istream &in);
    ~Warrior();

    int move_to(char action, int border_x, int border_y) override;
    vector<pair<int, int>> aim_attack(List<Object*>& objects) override;
    int &getpower() override;
    int &getrange() override;
    
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
         << "    range = " << this->range << endl         
         << "Warrior." <<endl; 
}

Warrior::~Warrior() {
    cout << "~Warrior:"<< endl 
         << "    power = " << this->power << endl
         << "    range = " << this->range << endl                  
         << "~Warrior." <<endl; 
}

char Warrior::draw(){
    if(alive()) return 'w'; 
    else if(!alive()) return 'x';
} 

istream &operator>>(istream &in, Warrior &wr){
    in >> wr.power >> wr.range;
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

vector<pair<int, int>> Warrior::aim_attack(List<Object*>& objects) {
    vector<pair<int, int>> aim;
    for (int i = 0; i <= range; i++) {
        aim.push_back(pair<int, int>(getx(), gety()));
    	for (int j = 0; j <= range; j++) {
    		if (i == 0 && j == 0) continue;
    		aim.push_back(pair<int, int>(getx() + i, gety() + j));
    		aim.push_back(pair<int, int>(getx() - i, gety() - j));
    		aim.push_back(pair<int, int>(getx() - i, gety() + j));
    		aim.push_back(pair<int, int>(getx() + i, gety() - j));
    	}
    }
    return aim;
}

// void Warrior::print_ob_simple(){ 
//     cout << "[ " << getmark() << " " << getid() << " " << getx() << " " << gety() << " " << gethp() << " " << power << " ]" << endl; 
// }

int &Warrior::getpower()
    {return this->power;}

int &Warrior::getrange()
    {return this->range;}


//-----------------------------------------------------------------------------------------



//--------------------------------------SWORDSMAN-------------------------------------------
class Swordsman : public Warrior
{
public:
    Swordsman(shared_ptr<Crown> crown, istream &in);
    ~Swordsman();

    vector<pair<int, int>> aim_attack(List<Object*>& objects) override;
    char draw() override;
    // vector<pair<int, int>> aim_attack() override;
};

//---------------------------------SWORDSMAN METHODS-----------------------------------------
Swordsman::Swordsman(shared_ptr<Crown> crown, istream &in): Warrior(crown, in)  {
    cout << "Swordsman."<< endl;         
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



//--------------------------------------MAGNICIAN-------------------------------------------
class Magician : public Warrior
{
public:
     Magician(shared_ptr<Crown> crown, istream &in);
    ~Magician();

    char draw() override;
    // vector<pair<int, int>> aim_attack() override;
};
//---------------------------------MAGICIAN-METHODS-----------------------------------------
Magician::Magician(shared_ptr<Crown> crown, istream &in): Warrior(crown, in) {
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
