
#include "Field.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "warrior.hpp"
#include "building.hpp"

using namespace std;
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE   "\033[34m"      /* Blue */
void fillArmy(List<Object*>& army, shared_ptr<Crown>& temp, ifstream& file) {
    char objectType;
    file >> objectType;
    switch (objectType) {
        case 'w':
            army.Add_end(new Warrior(file, temp));
            break;
        case 'b':
            army.Add_end(new Building(file, temp));
            break;
    }
}
Field::Field(ifstream& file) {
    file >> x_size >> y_size >> size_A;
    cout << "Field:" << endl
    << "    x_size = " << x_size << endl
    << "    y_size = " << y_size << endl;
    std::shared_ptr<Crown> temp(new Crown("green"));
    crownA = temp;
    for (auto i = 0; i < size_A; i++) {
        fillArmy(armyA, temp, file);
    }
    file >> size_B;
    std::shared_ptr<Crown> temp2(new Crown("red"));
    crownB = temp2;
    for (auto i = 0; i < size_B; i++) {
        fillArmy(armyB, temp2, file);
    }
}

Field::~Field() {
    cout << "~Field:" << endl
    << "    x_size = " << x_size << endl
    << "    y_size = " << y_size << endl;
    for (auto it : armyA){
        if(it->getHp()<=0)
            break;
        switch (it->getType()) {
            case 'w':
                delete ((Warrior*)it);
                break;
            case 'b':
                delete ((Building*)it);
                break;
        }
    }
    for (auto it : armyB){
        if(it->getHp()<=0)
            break;
        switch (it->getType()) {
            case 'w':
                delete ((Warrior*)it);
                break;
            case 'b':
                delete ((Building*)it);
                break;
        }
    }
    cout << "~Field." << endl;
}
Object* Field::checkArmyCoords(List<Object*> army, int count, int i, int j){
    for (auto k = 0; k < count; k++) {
        if (army[k]->checkObjCoords(i, j)) {
            return army[k];
        }
        if (army[k]->getType() == 'b') {
            if (((Building*)army[k])->Is_Build_Located(i, j)) {
                return army[k];
            }
        }
    }
    return nullptr;
}

bool printArmy(List<Object*> &army, int color, int count, int i, int j) {
    for (auto k = 0; k < count; k++) {
        if (army[k]->checkObjCoords(i, j)) {
            if (army[k]->getHp()<=0) {
                return false;
            }
            char symb = 'w';
            if (army[k]->getType() == 'b') {
                symb = 'b';
            }
            if (color == 1)
                std::cout << GREEN << symb;
            else
                std::cout << RED << symb;
            std::cout << BLACK;
            return true;
        }
        else if (army[k]->getType() == 'b') {
            if (((Building*)army[k])->Is_Build_Located(i, j)) {
                char symb = 'b';
                if (army[k]->getHp()<=0) {
                    return false;
                }
                if (color == 1)
                    std::cout << GREEN << symb;
                else
                    std::cout << RED << symb;
                std::cout << BLACK;
                return true;
            }
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
void deleteObj(Object* object, List<Object*> &army, int& count) {
    for (int i = 0; i < count; i++) {
        if (army[i]->checkObjCoords(object->getY(), object->getX())) {
            switch (army[i]->getType()) {
                case 'w':
                    delete ((Warrior*)army[i]);
                    break;
                case 'b':
                    delete ((Building*)army[i]);
                    break;
            }
            count--;
        }
    }
}
void attackAim(vector<tuple<int, int>> attackRange, List<Object*> &army, int count, int power) {
    for (int i = 0; i < attackRange.size(); i++) {
        for (auto armyI : army) {
            if (armyI->checkObjCoords(get<1>(attackRange[i]), get<0>(attackRange[i]))) {
                armyI->getDamage(power);
                if (armyI->getHp() <= 0) {
                    deleteObj(armyI, army, count);
                }
                return;
            }
            else if (armyI->getType() == 'b') {
                if (((Building*)armyI)->Is_Build_Located(get<1>(attackRange[i]), get<0>(attackRange[i]))) {
                    armyI->getDamage(power);
                    if (armyI->getHp() <= 0) {
                        deleteObj(armyI, army, count);
                    }
                    return;
                }
            }
        }
    }
}
int Field::getXSize() {
    return x_size;
}
int Field::getYSize() {
    return y_size;
}
weak_ptr<Crown> Field::getCrownA() {
    return crownA;
}
weak_ptr<Crown> Field::getCrownB() {
    return crownB;
}
