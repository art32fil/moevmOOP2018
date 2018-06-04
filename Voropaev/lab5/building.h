#ifndef BUILDING_H
#define BUILDING_H

#include "object.h"
#include "warrior.h"
#include "magician.h"
#include "swordsman.h"

template <typename WTYPE>
class Building: public Object {
private:
  std::vector<Coordinates> extra_coords;
public:

  Building(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, std::vector<Coordinates> extra_coord): Object(coords, hp, crown_ptr) {
    extra_coords = extra_coord;
    std::cout << "Building:" << std::endl;
    print_info();
    std::cout << "Building." << std::endl << std::endl;
  }

  //--------------------------------------

  ~Building() {
    std::cout << "~Building:" << std::endl;
    print_info();
    std::cout << "~Building." << std::endl;

  }

  //--------------------------------------

  WTYPE* spawn() { //порождение объектов
    WTYPE* obj = new WTYPE;
    return obj;
  }

  //--------------------------------------

  const char get_type() override {
    return 'b';
  }

  //--------------------------------------

  void print_info() override {
    int i = 0;
    for (auto const& elem: extra_coords) {
      std::cout << "  x" << i << " = " << elem.x << std::endl;
      std::cout << "  y" << i << " = " << elem.y << std::endl;
      ++i;
    }
  }

  //--------------------------------------

  std::vector<Coordinates> get_extra_coords() override {
    return extra_coords;
  }

  //--------------------------------------

  virtual Object* check_position(Coordinates coords) override {
    for (auto &elem_coords: extra_coords) {
      if (elem_coords == coords) return this;
    }
    return nullptr;
  }

  //--------------------------------------

  //переопределение чисто виртуальных функций класса объект
   void move(std::string direction) override {}

   std::vector<Coordinates> attack() override {
     std::vector<Coordinates> nullvec;
     return nullvec;
   }

   std::vector<Coordinates> attack(char direction) override {
     std::vector<Coordinates> nullvec;
     return nullvec;
   }

   int get_force() override {
     return 0;
   }


};

template<> Warrior* Building<Warrior>::spawn() { 
  Coordinates coords(0, 0);
  Warrior* war = new Warrior(coords, 100, crown, 50);
  return war;
}

template<> Swordsman* Building<Swordsman>::spawn() {
  Coordinates coords(0, 0);
  Swordsman* swr = new Swordsman(coords, 100, crown, 50);
  return swr;
}

template<> Magician* Building<Magician>::spawn() {
  Coordinates coords(0,0);
  Magician* mag = new Magician(coords, 100, crown, 50, 2);
  return mag;
}

#endif
