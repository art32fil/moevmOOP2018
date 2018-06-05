#pragma once

#include "warrior.h"


//--------------------------------------MAGNICIAN-------------------------------------------
class Magician : public Warrior
{
public:
    Magician(shared_ptr<Crown> crown, istream &in);
    Magician(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range);
    
    ~Magician();

    char draw() override;
    // vector<pair<int, int>> aim_attack() 
    vector<pair<int, int>> aim_attack(int direction) override;
};


//---------------------------------MAGICIAN-METHODS-----------------------------------------
Magician::Magician(shared_ptr<Crown> crown, istream &in): Warrior(crown, in) {
    cout << "Magician."<< endl;         
}

Magician::Magician(shared_ptr<Crown> crown, char mark, int x, int y, int hp, int power, int range):
            Warrior(crown, mark, x, y, hp, power, range) {
    cout << "Magician."<< endl; 
}

Magician::~Magician() {
    cout << "~Magician."<< endl;                 
}

char Magician::draw(){
    if(alive()) return 'm'; 
    else if(!alive()) return 'x';
} 

vector<pair<int, int>> Magician::aim_attack(int direction){
    vector<pair<int, int>> aim;
    pair<int,int> point = make_pair(this->getx(),this->gety());
    switch (direction) {
      case 0: { //горизоталь вправо
        for (int i = 0; i < this->getrange(); i++) {
          point.first++;
          aim.push_back(point);
        }
        break; 
      }
      case 45: { //диагональ вправо вверх
        for (int i = 0; i < this->getrange(); i++) {
          point.first++; point.second--;
          aim.push_back(point);
        }
        break;
      }
      case 90: { //вертикаль вверх
        for (int i = 0; i < this->getrange(); i++) {
          point.second--;
          aim.push_back(point);
        std::cout << "add (" << point.first << ", " << point.second << ")" << std::endl;

        }
        break;
      }
      case 135: { //диагональ влево вверх
        for (int i = 0; i < this->getrange(); i++) {
          point.first--; point.second--;
          aim.push_back(point);
        }
        break;
      }
      case 180: { //горизоталь влево
        for (int i = 0; i < this->getrange(); i++) {
          point.first--;
          aim.push_back(point);
        }
        break;
      }
      case -45: { //диагональ вправо вниз
        for (int i = 0; i < this->getrange(); i++) {
          point.first++; point.second++;
          aim.push_back(point);
        }
        break;
      }
      case -90: { //вертикаль вниз
        for (int i = 0; i < this->getrange(); i++) {
          point.second++;
          aim.push_back(point);
        }
        break;
      }
      case -135: { //диагональ влево вниз
        for (int i = 0; i < this->getrange(); i++) {
          point.first--; point.second++;
          aim.push_back(point);
        }
        break;
      }
      default: {
        std::cout << "wrong degree value :^( "  << std::endl;
        break;
      }
    }
    return aim;
}


ostream &operator<<(ostream &out, Magician &wr){
    if(wr.getcrown()->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(wr.getcrown()->getcolor() == "red") 
        out << "\033[31m";
    out << wr.draw() << "\033[0m";
    return out;
} 
//----------------------------------------------------------------------------------------
