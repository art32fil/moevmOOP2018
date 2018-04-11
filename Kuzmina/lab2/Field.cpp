
#include "Field.hpp"
#include <fstream>
#include <iostream>

using namespace std;
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

Field::Field(ifstream& file) {
    file >> x_size >> y_size >> size_A;
    cout << "Field:" << endl
    << "    x_size = " << x_size << endl
    << "    y_size = " << y_size << endl;
    std::shared_ptr<Crown> temp(new Crown("green"));
    crownA = temp;
    for (auto i = 0; i < size_A; i++) {
        armyA.Add_end(new Object(file, i, temp));
    }
    file >> size_B;
    std::shared_ptr<Crown> temp2(new Crown("red"));
    crownA = temp2;
    for (auto i = 0; i < size_B; i++) {
        armyB.Add_end(new Object(file, i+size_A,temp2));
    }
}

Field::~Field() {
    cout << "~Field:" << endl
    << "    x_size = " << x_size << endl
    << "    y_size = " << y_size << endl;
    for (auto it : armyA){
        if(it->getHp()<=0)
            break;
        delete (it);
    }
    for (auto it : armyB){
        if(it->getHp()<=0)
            break;
        delete (it);
    }
    cout << "~Field." << endl;
}
Object* Field::checkArmyCoords(List<Object*> army, int count, int i, int j){
    for (auto k = 0; k < count; k++) {
        if (army[k]->checkObjCoords(i, j)) {
            return army[k];
        }
    }
    return nullptr;
}

bool printArmy(List<Object*> &army, int color, int count, int i, int j) {
    for (auto k = 0; k < count; k++) {
        if (army[k]->checkObjCoords(i, j)) {
            char symb = 'O';
            if (army[k]->getHp()<=0) {
                symb = '.';
            }
            if (color == 1)
                std::cout << GREEN << symb;
            else
                std::cout << RED << symb;
            std::cout << BLACK;
            return true;
        }
    }
    return false;
}

void Field::printField() {
    cout<<endl<<"  ";
    for(auto i = 0; i < x_size; i++){
        cout<<i;
    }
    cout<<endl<<" +";
    for(auto i = 0; i < x_size; i++){
        cout<<"-";
    }
    cout<<"+"<<endl;
    for (auto i = 0; i < y_size; i++) {
        cout<<i<<"|";
        for (auto j = 0; j < x_size; j++) {
            if (printArmy(armyA, 1, size_A, i, j) || printArmy(armyB, 2, size_B, i, j)) {
                continue;
            }
            cout << ".";
        }
        cout <<"|"<< endl;
    }
    cout<<" +";
    for(auto i = 0; i < x_size; i++){
        cout<<"-";
    }
    cout<<"+"<<endl;
}

List<Object*>& Field::get_army_A() {
    return armyA;
}

List<Object*>& Field::get_army_B() {
    return armyB;
}

int Field::get_size_A() {
    return size_A;
}

int Field::get_size_B() {
    return size_B;
}

void Field::getDamage(List<Object*> army, int count, int i, int j, int damage) {
    for (auto k = 0; k < count; k++) {
        if (army[k]->checkObjCoords(i, j)) {
            army[k]->getDamage(damage);
        }
    }
}
