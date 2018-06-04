#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include "object.h"
#include "features.h"

class Warrior: public Object {
private:
  int force;

public:
  Warrior(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, int force): Object(coords, hp, crown_ptr), force(force) {
    std::cout << "Warrior:" << std::endl;
    print_info();
    std::cout << "Warrior." << std::endl << std::endl;
  }

  //--------------------------------------

  ~Warrior() {
    std::cout << "~Warrior:" << std::endl;
    print_info();
    std::cout << "~Warrior." << std::endl;
  }

  //--------------------------------------

  virtual void print_info() override {
    std::cout << "  force = " << force << std::endl;
  }

  //--------------------------------------

  virtual const char get_type() override {
    return 'w';
  }

  //--------------------------------------

  void move(std::string direction) override {
    if (direction == "up") --coord.y;
    else if (direction == "down") ++coord.y;
    else if (direction == "right") ++coord.x;
    else if (direction == "left") --coord.x;
    else {
      std::cout << "wrong direction: " << direction << std::endl;
    }
  }

  //--------------------------------------

  virtual std::vector<Coordinates> attack() override {
    //атака координат
    std::vector<Coordinates> attacked_coords;
    Coordinates coords_to_attack = this->get_coord(); //воин атакует только совпадающих по координатам
    attacked_coords.push_back(coords_to_attack);
    return attacked_coords;
  }

  //--------------------------------------

  int get_force() override {
    return force;
  }

  //--------------------------------------

  //переопределение чисто виртуальных методов класса Object
  std::vector<Coordinates> attack(char direction) override {
    std::vector<Coordinates> nullvec;
    return nullvec;
  }
  std::vector<Coordinates> get_extra_coords() override {
    std::vector<Coordinates> nullvec;
    return nullvec;
  }
  Object* spawn() override {
    return nullptr;
  }

};

#endif
