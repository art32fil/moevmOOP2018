#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include "crown.h"


struct Coordinates {
  int x;
  int y;
};

//--------------------------------------

class Object {
private:
  Coordinates coord;
  int health;
  const std::shared_ptr<Crown> crown;

  const int id;
  static int count; //создано объектов
  static int amount; //существовало за всё время

public:

  const int get_id() {
    return id;
  }
  //--------------------------------------

  void print_object() {
    std::cout << "id = " << id << std::endl;
    std::cout << "x = " << coord.x << std::endl;
    std::cout << "y = " << coord.y << std::endl;
    std::cout << "hp = " << health << std::endl;
    std::cout << "crown = " << crown->get_color() << std::endl;
  }

  //--------------------------------------

  Object(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr): health(hp), crown(crown_ptr), id(count++) {
    coord.x = coords.x;
    coord.y = coords.y;
    std::cout << "Object:" << std::endl;
    print_object();
    std::cout << "Object." << std::endl;
    amount++;
  }
  //--------------------------------------

  Object(const std::shared_ptr<Crown> crown_ptr, std::ifstream& fin): crown(crown_ptr), id(count++){
    amount++;
  }
  //--------------------------------------

  ~Object() {
    std::cout << "~Object:" << std::endl;
    print_object();
    std::cout << "~Object." << std::endl;
  }
  //--------------------------------------

  void damage(int points) {
    health -= points;
  }

  Coordinates& get_coord() {
    return coord;
  }

  int& get_hp() {
     return health;
   }

  //--------------------------------------

  Object* check_position(Coordinates coords) {
    if ((coord.x == coords.x) && (coord.y == coords.y))
      return this;
    else return nullptr;
  }

};


//---------------перегрузка операторов-----------------------

std::ifstream& operator>>(std::ifstream& fin, Coordinates &coord) {
  fin >> coord.x >> coord.y;
  return fin;
}
//--------------------------------------

std::ifstream& operator>>(std::ifstream& fin, Object& obj) {
  fin >> obj.get_coord().x >> obj.get_coord().y >> obj.get_hp();
  return fin;
}

//--------------------------------------

std::ostream& operator<<(std::ostream& out, Object& obj) {
  obj.print_object();
  return out;
}

#endif
