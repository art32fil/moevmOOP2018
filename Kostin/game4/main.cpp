#include <iostream>
#include "Battlefield.hpp"
#include "Object.hpp"
#include "Warrior.hpp"

using namespace std;

size_t Object::count = 0;
size_t Object::amount = 0;

void menu(){
    std::cout << '\n' <<
    "\033[1;35m*********************************************" <<
      '\n' << "** 1 - choice the object                   **" <<
      '\n' << "** 0 - exit                                **" <<
      '\n' << "*********************************************\033[0m" <<
    '\n' << '\n';
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("input.txt");
    Battlefield btlf;
    btlf.Enter(fin);
    btlf.Draw_battlefield();

    std::shared_ptr<Crown> temp(new Crown("Nan"));
    size_t choice = 0;
    size_t pos_x = 0, pos_y = 0;
    // size_t dmg = 0;
    // size_t cnt = 0;
    string army, direction;

    while (true) {
        menu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 0:
            std::cout << "---------------------------------------------" << '\n';

            return 0;

            case 1: {
                std::cout << "Enter position x and y: ";
                std::cin >> pos_x >> pos_y;

                // std::cout << '\n' << "it's interim object : ";
                // std::cout << '\n';

                Warrior obj = {pos_x, pos_y, temp, 100}; //Colled of Constructor!
                std::pair<int, Warrior*> ob = btlf.check_colour_on_postion(&obj);

                if(ob.first == 1){
                    std::cout << "It is object of \033[1;31m RED \033[0m army!" << '\n';
                }
                else if(ob.first == 2)
                    std::cout << "It is object of \033[1;32m GREEN \033[0m army!" << '\n';
                else if(ob.first == 3){
                    std::cout << "\033[1;34m It is object don't belong any army!\033[0m" << '\n';
                    break;
                }
                std::cout << "Enter direction of Warrior" << '\n';
                std::cin >> direction;
                ob.second->move_to_(direction);

                std::cout << '\n';
                std::cout << "Enter quantity of damage: ";

                std::cout << '\n' << "Hit points: " << ob.second->get_hp() << endl;
                std::cout << '\n';
                btlf.Draw_battlefield();
                Object *tmp = btlf.check_postion(dynamic_cast<Object*>(ob.second));
                if(tmp){

                    std::tuple<List<Warrior*>&, List<Warrior*>&, List<Building*>&,
                    List<Building*>& > army(btlf.get_gr_warr(), btlf.get_red_warr(),
                    btlf.get_gr_build(), btlf.get_red_build());

                    ob.second->Attack(tmp, army);
                    std::cout << "hp = " << tmp->get_hp() << '\n';
                }
                btlf.Draw_battlefield();
                break;
                }
            default:
                std::cout << "Incorrect choice!" << '\n';
                break;
        }
    }


    return 0;
}
