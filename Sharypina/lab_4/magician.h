#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "warrior.h"

class Magician: public Warrior {
private:
  int attack_range;

public:
  Magician(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, int force, int range): Warrior(coords, hp, crown_ptr, force),
            attack_range(range) {
    std::cout << "Magician:" << std::endl;
    print_info();
    std::cout << "Magician." << std::endl << std::endl;
  }

  //----------------------------------------------------------

  ~Magician() {
    std::cout << "~Magician:" << std::endl;
    std::cout << "~Magician." << std::endl;
  }

  //----------------------------------------------------------

  void print_info() override {
    std::cout << "  range = " << attack_range << std::endl;
  }

  //----------------------------------------------------------

  const char get_type() override {
    return 'm';
  }

  //----------------------------------------------------------

  int get_attack_range() {
    return attack_range;
  }

  //----------------------------------------------------------

  std::vector<Coordinates> attack() override { //атака на соседней клетке
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

  //----------------------------------------------------------

  std::vector<Coordinates> attack(int degrees) override { //перегрузка функции: атака по лучу под углом
    //int degree;
    //std::cin >> degree;
    std::vector<Coordinates> attacked_coords;
    Coordinates cur_coords = this->coord;
    switch (degrees) {
      case 0: { //горизоталь вправо
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x++;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case 45: { //диагональ вправо вверх
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x++; cur_coords.y--;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case 90: { //вертикаль вверх
        for (int i = 0; i < attack_range; i++) {
          cur_coords.y--;
          attacked_coords.push_back(cur_coords);
        std::cout << "add (" << cur_coords.x << ", " << cur_coords.y << ")" << std::endl;

        }
        break;
      }
      case 135: { //диагональ влево вверх
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x--; cur_coords.y--;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case 180: { //горизоталь влево
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x--;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case -45: { //диагональ вправо вниз
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x++; cur_coords.y++;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case -90: { //вертикаль вниз
        for (int i = 0; i < attack_range; i++) {
          cur_coords.y++;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      case -135: { //диагональ влево вниз
        for (int i = 0; i < attack_range; i++) {
          cur_coords.x--; cur_coords.y++;
          attacked_coords.push_back(cur_coords);
        }
        break;
      }
      default: {
        std::cout << "wrong degree value :^( "  << std::endl;
        break;
      }
    }
    return attacked_coords;
  }

};

#endif
