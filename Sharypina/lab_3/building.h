#ifndef BUILDING_H
#define BUILDING_H

#include "object.h"
class Building: public Object {
private:
  std::vector<Coordinates> extra_coords;
public:

  Building(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, std::vector<Coordinates> extra_coord): Object(coords, hp, crown_ptr) {
    extra_coords = extra_coord;
    std::cout << "Building:" << std::endl;
    print_info();
    std::cout << "Building." << std::endl;
  }

  ~Building() {
    std::cout << "~Building:" << std::endl;
    print_info();
    std::cout << "~Building." << std::endl;

  }

  const char get_type() override {
    return 'b';
  }

  void print_info() override {
    int i = 0;
    for (auto const& elem: extra_coords) {
      std::cout << "x" << i << " = " << elem.x << std::endl;
      std::cout << "y" << i << " = " << elem.y << std::endl;
      ++i;
    }
  }

  std::vector<Coordinates>& get_extra_coords() {
    return extra_coords;
  }

  virtual Object* check_position(Coordinates coords) override {
    for (auto &elem_coords: extra_coords) {
      if (elem_coords == coords) return this;
    }
    return nullptr;
  }
};

#endif
