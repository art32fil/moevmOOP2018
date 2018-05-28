#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include <vector>
#include "crown.h"


struct Coordinates {
  int x;
  int y;
  Coordinates(int i = 0, int j = 0): x(i), y(j) {}
  ~Coordinates() {}
};

//--------------------------------------

class Object {
protected:
  Coordinates coord;
  int health;
  const std::shared_ptr<Crown> crown;

  const int id;
  static int count; //создано объектов
  static int amount; //существовало за всё время

public:

  Object(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr): health(hp), crown(crown_ptr), id(count++) {
    coord.x = coords.x;
    coord.y = coords.y;
    std::cout << "Object:" << std::endl;
    print_info();
    std::cout << "Object." << std::endl << std::endl;
    amount++;
  }

  //--------------------------------------

  Object(const std::shared_ptr<Crown> crown_ptr, std::ifstream& fin): crown(crown_ptr), id(count++){
    amount++;
    std::cout << "Object:" << std::endl;
    print_info();
    std::cout << "Object." << std::endl << std::endl;
  }

//----------------------------------------

  Object(const Object& obj) : crown(obj.crown), id(count++) {
    coord = obj.coord;
    health = obj.health;
    amount++;
    std::cout << "Object:" << std::endl;
    print_info();
    std::cout << "Object." << std::endl;
  }

  //--------------------------------------

  virtual ~Object() {
    std::cout << "~Object:" << std::endl;
    print_info();
    std::cout << "~Object." << std::endl;
  }

  //--------------------------------------

    virtual void print_info() {
      std::cout << "  id = " << id << std::endl;
      std::cout << "  x = " << coord.x << std::endl;
      std::cout << "  y = " << coord.y << std::endl;
      std::cout << "  hp = " << health << std::endl;
      std::cout << "  crown = " << crown->get_color() << std::endl;
    }

  //--------------------------------------

  void damage(int points) { //принятие урона
    health -= points;
  }

  //--------------------------------------

  Coordinates& get_coord() { //возвращает координаты
    return coord;
  }

  //--------------------------------------

  int& get_hp() { //возвращает hp
     return health;
  }
  //--------------------------------------

  const int get_id() { //возвращает id
    return id;
  }

  //--------------------------------------

  virtual Object* check_position(Coordinates coords) {
  //для проверки, есть ли объект на данных координатах
    if ((coord.x == coords.x) && (coord.y == coords.y))
      return this;
    else return nullptr;
  }

  //--------------------------------------

  //чисто виртуальные методы
  virtual int get_force() = 0;
  virtual const char get_type() = 0;
  virtual void move(std::string direction) = 0;
  virtual std::vector<Coordinates> attack() = 0;
  virtual std::vector<Coordinates> attack(int degrees) = 0;
  virtual std::vector<Coordinates> get_extra_coords() = 0;
  virtual Object* spawn() = 0;
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
  obj.print_info();
  return out;
}

//--------------------------------------

const bool operator==(const Coordinates& first, const Coordinates& second) {
  return (first.x == second.x) && (first.y == second.y);
}

//--------------------------------------

const bool operator!=(const Coordinates& first, const Coordinates& second) {
  return !(first == second);
}

#endif
