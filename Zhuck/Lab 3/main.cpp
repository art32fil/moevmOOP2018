#include <iostream>
#include "Battlefield.hpp"
#include "Object.hpp"

using namespace std;

size_t Object::count = 0;
size_t Object::amount = 0;

void menu(){
    std::cout << '\n' <<
    "\033[1;35m*********************************************" <<
      '\n' << "** 1 - check colour of army on postion     **" <<
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
    //Object obj(temp);

    std::pair<int, Object&>* ob;
    size_t choice = 0;
    size_t pos_x = 0, pos_y = 0;
    size_t dmg = 0;
    size_t cnt = 0;

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
                

                std::cout << '\n' << "it's interim object : ";
                std::cout << '\n';

                Object obj = {pos_x, pos_y, temp}; //Colled of Constructor!

                ob = new std::pair<int, Object&>{btlf.check_colour_on_postion(obj)};
                if(ob->first == 1){
                    std::cout << "It is object of \033[1;31m RED \033[0m army!" << '\n';
                }
                else if(ob->first ==  2)
                    std::cout << "It is object of \033[1;32m GREEN \033[0m army!" << '\n';
                else if(ob->first == 3){
                    std::cout << "It is object don't belong any army!" << '\n';
                    break;
                }
                std::cout << '\n';
                std::cout << "Enter quantity of damage: ";
                std::cin >> dmg;
                ob->second.get_Damag(dmg);
                std::cout << '\n' << "Hit points: " << ob->second.get_hp() << endl;
                std::cout << '\n';
                btlf.Draw_battlefield();
                cnt = 0; //!!!!!!!!!!!!!!!Warning!
                if(ob->second.get_hp() <= 0 && ob->first == 1 ){ //
                    for (auto &el : btlf.get_red_arm()) {
                        if(ob->second.get_ID() == el.get_Info().get_ID()){
                            btlf.get_red_arm().Delete_elem(cnt);
                        }
                        cnt++;
                    }
                }
                cnt = 0;//!!!!!!!!!!!!!!!Warning!
                if(ob->second.get_hp() <= 0 && ob->first == 2 ){
                    for (auto &el : btlf.get_gr_arm()) {
                        if(ob->second.get_ID() == el.get_Info().get_ID()){
                            btlf.get_gr_arm().Delete_elem(cnt);
                        }
                        cnt++;
                    }
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
