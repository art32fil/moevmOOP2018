#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "warrior.h"
using namespace std;
class Magician: public Warrior {
private:
  int range;

public:
  Magician(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, int force, int _range): Warrior(coords, hp, crown_ptr, force),
            range(range) {
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
    std::cout << "  range = " << range << std::endl;
  }

  //----------------------------------------------------------

  const char get_type() override {
    return 'm';
  }

  //----------------------------------------------------------

  int get_attack_range() {
    return range;
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

  std::vector<Coordinates> attack(char direction) override
	{
		vector<Coordinates> attacked_coords;
		Coordinates current = coord;
		
		switch(direction)
		{
			case 'd':
			{
				for(int Xcoord = 0; Xcoord < range; Xcoord++)
				{
					current.x++;
					attacked_coords.push_back(current);
				}
				break;
			}
			case 'a':
			{
				for(int Xcoord = 0; Xcoord < range; Xcoord++)
				{
					current.x--;
					attacked_coords.push_back(current);
				}
				break;
			}
			case 's':
			{
				for(int Ycoord = 0; Ycoord < range; Ycoord++)
				{
					current.y++;
					attacked_coords.push_back(current);
				}
				break;
			}
			case 'w':
			{
				for(int Ycoord = 0; Ycoord < range; Ycoord++)
				{
					current.y--;
					attacked_coords.push_back(current);
				}
				break;
			}
			default:
			{
				cout << "Wrong direction " << endl;
				break;
			}

			
		}
		return attacked_coords;
	}

};

#endif

