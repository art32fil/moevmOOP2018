#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "warrior.h"

class Swordsman: public Warrior {

public:

Swordsman(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, int force): Warrior(coords, hp, crown_ptr, force) {
  std::cout << "Swordsman:" << std::endl;
  std::cout << "Swordsman." << std::endl;
}

   

~Swordsman() {
  std::cout << "~Swordsman:" << std::endl;
  std::cout << "~Swordsman." << std::endl;
}

   

  const char get_type() override {
    return 's';
  }

   

std::vector<Coordinates> attack() override {
std::vector<Coordinates> attacked_coords;

Coordinates obj_coord = coord;
Coordinates begin_coord = obj_coord;
begin_coord.x--; begin_coord.y--;
Coordinates end_coord = begin_coord;
end_coord.x += 2; end_coord.y += 2;
Coordinates cur_coord = begin_coord;

while (cur_coord.y <= end_coord.y) {
  while (cur_coord.x <= end_coord.x) {
    attacked_coords.push_back(cur_coord);
    std::cout << "add (" << cur_coord.x << ", " << cur_coord.y << ")" << std::endl;
    cur_coord.x++;
  }
  cur_coord.y++;
  cur_coord.x = begin_coord.x;
}
  return attacked_coords;
}

};

#endif
