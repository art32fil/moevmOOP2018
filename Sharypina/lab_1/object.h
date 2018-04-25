#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>

struct Coordinates
{
  int x;
  int y;
};

//--------------------------------------

class Object
{
//friend class Battlefield;
private:
  Coordinates coord;
  int health;

public:
  Object(Coordinates coords, int hp)
  {
    coord.x=coords.x;
    coord.y=coords.y;
    health=hp;
    std::cout<<"Object:"<<std::endl;
    std::cout<<"x = "<<coord.x<<std::endl;
    std::cout<<"y = "<<coord.y<<std::endl;
    std::cout<<"hp = "<<health<<std::endl;
    std::cout<<"Object."<<std::endl;
  }

  Object() {}
  //--------------------------------------

  ~Object()
  {
    std::cout<<"~Object:"<<std::endl;
    std::cout<<"x = "<<coord.x<<std::endl;
    std::cout<<"y = "<<coord.y<<std::endl;
    std::cout<<"hp = "<<health<<std::endl;
    std::cout<<"~Object."<<std::endl;
  }
  //--------------------------------------

  void damage(int points) { health-=points; }
  Coordinates& get_coord() { return coord; }
  int& get_hp() { return health; }
  //--------------------------------------

  Object* check_position(Coordinates coords)
  {
    if((coord.x==coords.x)&&(coord.y==coords.y))
      return this;
    else return nullptr;
  }

};


//--------------------------------------

std::ifstream& operator>>(std::ifstream& fin, Coordinates &coord)
{
  fin>>coord.x>>coord.y;
  return fin;
}
std::ifstream& operator>>(std::ifstream& fin, Object &obj)
{
  fin>>obj.get_coord().x>>obj.get_coord().y>>obj.get_hp();
  return fin;
}

#endif
