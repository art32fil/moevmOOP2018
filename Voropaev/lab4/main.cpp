#include <iostream>
#include "Battlefield.hpp"
#include "Object.hpp"

using namespace std;

size_t Object::count = 0;
size_t Object::amount = 0;



void menu(){
    cout << '\n' <<
    "\033[1;32m----------------" <<
      '\n' << "| p - play      |" <<
      '\n' << "| q - exit      |" <<
      '\n' << "-----------------\033[0m" <<
    '\n' << '\n';
}

int main(int argc, char const *argv[]) {
    ifstream fin("input.txt"); //определяем файл для считывания
    Battlefield btlf;//создаем поле
    btlf.Enter(fin);//считываем поля из файла
    btlf.Draw_battlefield();//рисуем поле
    shared_ptr<Crown> temp(new Crown("neutral"));
    //Object obj;//создаем объект
    
    char choice;
    size_t pos_x = 0, pos_y = 0;
    size_t dmg = 0;
    size_t cnt = 0;
    string army;
    char direction;
    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
		switch (choice)
		{
		case 'q':{
			cout << "---------------------------------------------" << '\n';}
			return 0;

		case 'p':{
			
			cout << "Enter position x and y: ";
			cin >> pos_x >> pos_y; //считываем координаты по x и y
			//cout << '\n' << "it's interim object : ";
			//cout << '\n';
			Warrior obj = { pos_x, pos_y, temp, 100}; //вызываем конструктор объекта с введенными координатами 
			pair<int, Warrior*> ob = btlf.check_colour_on_position(&obj);//пара для проверки принадлежности объекта к армиям
			if (ob.first == 1)
			{
				
				if (ob.second->get_hp() > 0)
					cout << "This object belongs to\033[1;31m RED \033[0m army!" << '\n';
				else {
					cout << "This is the dead object of \033[1;31m RED \033[0m army!" << endl;
					btlf.Draw_battlefield();
					break;
				}
			}
			else if (ob.first == 2)
			{
				if (ob.second->get_hp() > 0)
					cout << "This object belongs to\033[1;32m GREEN \033[0m army!" << '\n';
				else
				{
					cout << "This is the dead object of \033[1;32m GREEN \033[0m army!" << endl;
					btlf.Draw_battlefield();
					break;
				}
			}
			else if (ob.first == 3) {
				cout << "This object doesn't belong to any army!" << '\n';
				break;
			}
			cout << '\n';
			cout << "Tell warrior where to go" << endl;
			cin >> direction;
			ob.second->move_to_(direction);
			cout << endl;
			std::cout << '\n' << "Hit points: " << ob.second->get_hp() << endl;
                std::cout << '\n';
                btlf.Draw_battlefield();
                Object *tmp = btlf.check_position(dynamic_cast<Object*>(ob.second));
                if(tmp){
                    ob.second->Attack(tmp);
                    std::cout << "hp = " << tmp->get_hp() << '\n';
                    cnt = 0; //!!!!!!!!!!!!!!!Warning!
                    if(tmp->get_hp() <= 0 && ob.first == 1 && tmp->type()=='w'){ //
                        for (auto &el : btlf.get_gr_warr()) {
                            if(tmp->get_ID() == el.get_Info()->get_ID()){
                                btlf.get_gr_warr().Delete_elem(cnt);
                            }
                            cnt++;
                        }
                    }
                    if(tmp->get_hp() <= 0 && ob.first == 1 && tmp->type()=='b'){ //
                        for (auto &el : btlf.get_gr_build()) {
                            if(tmp->get_ID() == el.get_Info()->get_ID()){
                                btlf.get_gr_build().Delete_elem(cnt);
                            }
                            cnt++;
                        }
                    }
                    cnt = 0;//!!!!!!!!!!!!!!!Warning!
                    if(tmp->get_hp() <= 0 && ob.first == 2 && tmp->type()=='w'){
                        for (auto &el : btlf.get_red_warr()) {
                            if(tmp->get_ID() == el.get_Info()->get_ID()){
                                btlf.get_red_warr().Delete_elem(cnt);
                            }
                            cnt++;
                        }
                    }
                    if(tmp->get_hp() <= 0 && ob.first == 2 && tmp->type()=='b'){
                        for (auto &el : btlf.get_red_build()) {
                            if(tmp->get_ID() == el.get_Info()->get_ID()){
                                btlf.get_red_build().Delete_elem(cnt);
                            }
                            cnt++;
                        }
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
