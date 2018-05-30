#include <iostream>
#include "warrior.hpp"
#include <vector>
using namespace std;

void deleteObj(Object* object, List<Object*> &army, int& count);

Warrior::Warrior(ifstream& file, const shared_ptr<Crown> crown) : Object(file, crown) {
    getType() = 'w';
    file >> force;
    cout << "Warrior:" << endl;
    cout << "    force = " << force << endl;
    cout << "Warrior." << endl;
}

Warrior::~Warrior() {
    cout << "~Warrior:" << endl;
    cout << "    force = " << force << endl;
    cout << "Warrior." << endl;
}

vector<tuple<int, int>> Warrior::attack() {
    vector<tuple<int, int>> attack_range;
    attack_range.push_back(tuple<int, int>(getX(), getY()));
    return attack_range;
}

void Warrior::move_up() {
    getY() -= 1;
}

void Warrior::move_right() {
    getX() += 1;
}

void Warrior::move_down() {
    getY() += 1;
}

void Warrior::move_left() {
    getX() -= 1;
}

int Warrior::get_force() {
    return force;
}

