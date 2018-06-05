#pragma once
#include "object.h"
// #include "swordsman.h"
// #include "magician.h"


using namespace std;


//--------------------------------------WARRIOR-------------------------------------------
class Warrior : public Object
{
    int power;
    int range;

public:
    // Warrior () {}
    Warrior(shared_ptr<Crown> crown, istream &in);
    Warrior(shared_ptr<Crown> crown, char mark = 'w', int x = 0, int y = 0, int hp = 10, int power = 10, int range = 0);
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

Warrior::Warrior(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range): 
                Object(crown, mark, x, y, hp), power(power), range(range)  {
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