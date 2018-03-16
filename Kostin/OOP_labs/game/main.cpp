// Лабораторная работа №1.
// Реализовать класс Объект, а также класс Поле_боя,
// являющийся обёрткой над контейнерами-армиями, хранящим экземпляры класса Объект.
// Объект должен иметь:
// Двумерные координаты.
// Очки жизней.
// Говорящий конструктор, говорящий деструктор.
// Функцию, которая принимает урон.
// Функцию, отвечающую на вопрос, есть ли Объект на указанной позиции.
// Считываться из файла.
// Поле_боя должно иметь:
// Контейнеры, хранящие объекты.
// Отрисовку Поля_боя на экране (разными цветами).
// Загружать объекты из файла
// Определять, располагается ли на заданных координатах объект той или иной армии.
#include <iostream>
#include "Battlefield.hpp"
#include "Object.hpp"

using namespace std;

void menu(){
    std::cout << '\n';
    std::cout << "*********************************************" << '\n';
    std::cout << "** 1 - check colour of army on postion     **" << '\n';
    std::cout << "** 0 - exit                                **" << '\n';
    std::cout << "*********************************************" << '\n';
    std::cout << '\n';
}

int main(int argc, char const *argv[]) {
    std::ifstream fin("input.txt");
    Battlefield btlf;
    btlf.Enter(fin);
    btlf.Draw_battlefield();
    Object obj;
    std::pair<int, Object&>* ob;
    size_t choice = 0;
    size_t pos_x = 0, pos_y = 0;
    size_t dmg = 0;

    while (true) {
        menu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 0:
                return 0;

            case 1:
                std::cout << "Enter position x and y: ";
                std::cin >> pos_x >> pos_y;
                obj = {pos_x, pos_y, 0}; //Colled of Constructor!
                ob = new std::pair<int, Object&>{btlf.check_colour_of_army_on_postion(obj)};
                if(ob->first == 1){
                    std::cout << "It is object of RED army!" << '\n';
                }
                else if(ob->first ==  2)
                    std::cout << "It is object of RED army!" << '\n';
                else if(ob->first == 3)
                    std::cout << "It is object don't belong any army!" << '\n';
                std::cout << '\n';
                std::cout << "Enter quantity of damage: ";
                std::cin >> dmg;
                ob->second.get_Damag(dmg);

                std::cout << '\n';
            break;
            default:
                std::cout << "Incorrect choice!" << '\n';
                //break;
        }
    }


    return 0;
}
