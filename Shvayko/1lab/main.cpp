#include <iostream>
#include "Battlefield.hpp"
#include "Object.hpp"

using namespace std;

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
    Object obj;//создаем объект
    pair<int, Object&>* ob;
    char choice;
    size_t pos_x = 0, pos_y = 0;
    size_t dmg = 0;

    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 'q':
            cout << "---------------------------------------------" << '\n';
                return 0;

            case 'p':
                cout << "Enter position x and y: ";
                cin >> pos_x >> pos_y; //считываем координаты по x и y
                cout << '\n' << "it's interim object : ";
                cout << '\n';
               obj = {pos_x, pos_y}; //вызываем конструктор объекта с введенными координатами 
                ob = new pair<int, Object&>{btlf.check_colour_on_postion(obj)};//пара для проверки принадлежности объекта к армиям
                if(ob->first == 1){
			if(ob->second.get_hp()>0)
                    		cout << "This object belongs to\033[1;31m RED \033[0m army!" << '\n';
			else { 
				cout<<"This is the dead object of \033[1;31m RED \033[0m army!" << endl; 
				btlf.Draw_battlefield();
				break;
			     }
                }
                else if(ob->first ==  2)
		{   if(ob->second.get_hp()>0)
                    	cout << "This object belongs to\033[1;32m GREEN \033[0m army!" << '\n';
		    else 
			{
				cout<<"This is the dead object of \033[1;32m GREEN \033[0m army!" << endl; 
				btlf.Draw_battlefield();
				break;
			}
		}
                else if(ob->first == 3){
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

 

            break;
            default:
                cout << "Incorrect choice!" << '\n';
                //break;
        }
    }


    return 0;
}
