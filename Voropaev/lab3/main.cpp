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
    pair<int, Object&>* ob;
    char choice;
    size_t pos_x = 0, pos_y = 0;
    size_t dmg = 0;
    size_t cnt = 0;

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
			cout << '\n' << "it's interim object : ";
			cout << '\n';
			Object obj = { pos_x, pos_y, temp}; //вызываем конструктор объекта с введенными координатами 
			ob = new pair<int, Object&>{ btlf.check_colour_on_postion(obj) };//пара для проверки принадлежности объекта к армиям
			if (ob->first == 1)
			{
				
				if (ob->second.get_hp() > 0)
					cout << "This object belongs to\033[1;31m RED \033[0m army!" << '\n';
				else {
					cout << "This is the dead object of \033[1;31m RED \033[0m army!" << endl;
					btlf.Draw_battlefield();
					break;
				}
			}
			else if (ob->first == 2)
			{
				if (ob->second.get_hp() > 0)
					cout << "This object belongs to\033[1;32m GREEN \033[0m army!" << '\n';
				else
				{
					cout << "This is the dead object of \033[1;32m GREEN \033[0m army!" << endl;
					btlf.Draw_battlefield();
					break;
				}
			}
			else if (ob->first == 3) {
				cout << "This object doesn't belong to any army!" << '\n';
				break;
			}
			cout << '\n';
			cout << "Enter quantity of damage: ";
			cin >> dmg;
			ob->second.get_Damag(dmg); //наносит введенный урон выбранному объекту
			
			cout << '\n' << "Hit points: " << ob->second.get_hp() << endl;
			cout << '\n';
			btlf.Draw_battlefield();//перерисовывает поле после всех изменений, сделанных на выполненном ходу
			cnt = 0;
			if (ob->second.get_hp() <= 0 && ob->first == 1)
			{
				for (auto &el: btlf.get_red_arm())
				{
					if (ob->second.get_ID() == el.get_Info().get_ID())
						btlf.get_red_arm().Delete_elem(cnt);
					cnt++;
				}
			}
			cnt = 0;
			if (ob->second.get_hp() <= 0 && ob->first == 2)
			{
				for (auto &el : btlf.get_gr_arm())
				{
					if (ob->second.get_ID() == el.get_Info().get_ID())
						btlf.get_gr_arm().Delete_elem(cnt);
					cnt++;
				}
			}
			
			btlf.Draw_battlefield();
			}break;

		default:{
			cout << "Incorrect choice!" << '\n';}
			break;
		}
                
        }
	return 0;
    }


  
