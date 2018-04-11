#include <iostream>
#include "Field.hpp"

using namespace std;
int main() {
    ifstream file("/Users/alenakuzmina/Documents/progs/oop1/oop1/input.txt");
    Field *field = new Field(file);
    char x, y;
    int damage;
    while (true) {
        field->printField();
        cout << "Input coordinates of target (separated by space) [q to exit]: ";
        cin >> x;
        if (x == 'q') break;
        cin >> y;
        if (field->checkArmyCoords(field->get_army_B(), field->get_size_B(), (int)y-48, (int)x - 48)) {
            cout << "Selected target is red\nInput a damage value: ";
            cin >> damage;
            field->checkArmyCoords(field->get_army_B(), field->get_size_B(), (int)y-48, (int)x - 48)->getDamage(damage);
        }
        if (field->checkArmyCoords(field->get_army_A(), field->get_size_A(), (int)y - 48, (int)x - 48)) {
            cout << "Selected target is green\nInput a damage value: ";
            cin >> damage;
            field->checkArmyCoords(field->get_army_A(), field->get_size_A(), (int)y-48, (int)x - 48)->getDamage(damage);
        }
        else {
            cout << "No Enemy here" << endl << "---------------------------------------" << endl;
        }
    }
    delete field;
    system("pause");
    return 0;
}
