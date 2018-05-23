#include <iostream>
#include <string>
#include "Field.hpp"
#include "warrior.hpp"
#include <vector>

void deleteObj(Object* object, List<Object*> &army, int& count);
void attackAim(vector<tuple<int, int>>, List<Object*> &army, int, int);
using namespace std;
int main() {
    ifstream file("/Users/alenakuzmina/Documents/progs/oop1/oop1/input.txt");
    Field *field = new Field(file);
    Object *obj;
    char x, y;
    string color_army;    
    int input;
    while (true) {
        field->printField();
        cout << "Input army object you want to action (color, x, y) [q to exit]: ";
        cin>>color_army;
        if (color_army == "q") break;
        cin >> x;
        cin >> y;
        if(color_army == "green"){
            obj = field->checkArmyCoords(field->get_army_A(), field->get_size_A(), (int)y-48, (int)x - 48);
            if (obj) {
            if (obj->getType() == 'w') {
                    cout << "Input the action:\n1. Move\n2. Attack" << endl;
                    cin >> input;
                    switch (input) {
                        case 1:
                            cout << "1. Up\n2. Right\n3. Down\n4. Left" << endl;
                            cin >> input;
                            switch (input) {
                                case 1:
                                    if (obj->getY() != 0) {
                                    ((Warrior*)obj)->move_up();
                                    }
                                    break;
                                case 2:
                                    if (obj->getX() != field->getXSize() - 1) {
                                    ((Warrior*)obj)->move_right();
                                    }
                                    break;
                                case 3:
                                    if (obj->getY() != field->getYSize() - 1) {
                                    ((Warrior*)obj)->move_down();
                                    }
                                    break;
                                case 4:
                                    if (obj->getX() != 0) {
                                        ((Warrior*)obj)->move_left();
                                    }
                                    break;
                            }
                            break;
                        case 2:
                            attackAim(((Warrior*)obj)->attack(), field->get_army_B(), field->get_size_B(), ((Warrior*)obj)->get_force());
                            cout<<"Damage is get\n";
                            break;
                    }
                }
            }
            else {
                cout << "No Enemy here" << endl << "---------------------------------------" << endl;
            }
            if (!field->getCrownB().use_count()) {
                break;
            }
        }
        if(color_army=="red"){
            obj = field->checkArmyCoords(field->get_army_B(), field->get_size_B(), (int)y-48, (int)x - 48);
            if (obj) {
                if (obj->getType() == 'w') {
                    cout << "Input the action:\n1. Move\n2. Attack" << endl;
                    cin >> input;
                    switch (input) {
                        case 1:
                            cout << "1. Up\n2. Right\n3. Down\n4. Left" << endl;
                            cin >> input;
                            switch (input) {
                                case 1:
                                    if (obj->getY() != 0) {
                                        ((Warrior*)obj)->move_up();
                                    }
                                    break;
                                case 2:
                                    if (obj->getX() != field->getXSize() - 1) {
                                        ((Warrior*)obj)->move_right();
                                    }
                                    break;
                                case 3:
                                    if (obj->getY() != field->getYSize() - 1) {
                                        ((Warrior*)obj)->move_down();
                                    }
                                    break;
                                case 4:
                                    if (obj->getX() != 0) {
                                        ((Warrior*)obj)->move_left();
                                    }
                                    break;
                            }
                            break;
                        case 2:
                            attackAim(((Warrior*)obj)->attack(), field->get_army_A(), field->get_size_A(), ((Warrior*)obj)->get_force());
                            cout<<"Damage is get\n";
                            break;
                    }
                }
            }
            else {
                cout << "No Enemy here" << endl << "---------------------------------------" << endl;
            }
            if (!field->getCrownA().use_count()) {
                break;
            }
        }
    }
    delete field;
    system("pause");
    return 0;
}
