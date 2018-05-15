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
    std::cout << "Warrior." << std::endl;
  }

  //--------------------------------------

  ~Warrior() {
    std::cout << "~Warrior:" << std::endl;
    print_info();
    std::cout << "~Warrior." << std::endl;
  }

  //--------------------------------------

  void print_info() override {
    std::cout << "force = " << force << std::endl;
  }

  //--------------------------------------

  const char get_type() override {
    return 'w';
  }

  //--------------------------------------

  void move(std::string direction, Size field_size) {
    if (direction == "up") {
      if (--coord.y < 0) ++coord.y;
    }
    else if (direction == "down") {
      if (++coord.y >= field_size.size_y) --coord.y;
    }
    else if (direction == "right") {
      if (++coord.x >= field_size.size_x) --coord.x;
    }
    else if (direction == "left") {
      if (--coord.x < 0) ++coord.x;
    }
    else {
      std::cout << "there is no direction: " << direction << std::endl;
    }
  }

  //--------------------------------------

  void attack(Object* object_to_attack) {
    //атака объекта
    object_to_attack->damage(force);
  }
};

#endif
