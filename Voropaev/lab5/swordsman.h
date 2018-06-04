#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "warrior.h"

class Swordsman: public Warrior {

public:

Swordsman(Coordinates coords, int hp, const std::shared_ptr<Crown> crown_ptr, int force): Warrior(coords, hp, crown_ptr, force) {
  std::cout << "Swordsman:" << std::endl;
  std::cout << "Swordsman." << std::endl;
}

//--------------------------------------

~Swordsman() {
  std::cout << "~Swordsman:" << std::endl;
  std::cout << "~Swordsman." << std::endl;
}

//--------------------------------------

  const char get_type() override {
    return 's';
  }

//--------------------------------------

std::vector<Coordinates> attack() override {
vector<Coordinates> attacked_coords;
		Coordinates started = coord;
		Coordinates current = started;
		for(int Xcoord = -1; Xcoord <= 1; Xcoord++)
		{
			
			
			for(int Ycoord = -1; Ycoord <= 1; Ycoord++)
			{
				if(((started.x + Xcoord)) < 0 || ((started.x + Xcoord) > 9))
					Xcoord++;
				if(started.y + Ycoord < 0 || started.y + Ycoord > 9)
					Ycoord++;
				current.x = started.x;
				current.y = started.y;
				current.x += Xcoord;
				current.y += Ycoord;
				attacked_coords.push_back(current);
				current.x = started.x;
				current.y = started.y;
			}
			
		}
		return attacked_coords;
}

};

#endif
