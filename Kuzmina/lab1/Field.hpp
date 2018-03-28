#pragma once
#ifndef Field_hpp
#include <fstream>
#include "Obj.hpp"
#include "list.hpp"
#include "list.cpp"

using namespace std;

class Field {
private:
    int x_size; // ширина поля
    int y_size; // высота поля
    List<Object*> armyA; // контейнер первой армии
    List<Object*> armyB; // контейнер второй армии
    int size_A; // количество объектов первой армии
    int size_B; // количество объектов второй армии
public:
    Field(ifstream& file);
    ~Field();

    Object* checkArmyCoords(List<Object*> army, int count, int i, int j); // проверить наличие объектов армии на координатах
    List<Object*>& get_army_A(); // получить контейнер первой армии
    List<Object*>& get_army_B(); // получить контейнер второй армии
    int get_size_A(); // получить количество объектов первой армии
    int get_size_B(); // получить количество объектов второй армии
    void printField(); // напечатать поле
    void getDamage(List<Object*> army, int count, int i, int j, int damage); // получить урон
};
#endif 
