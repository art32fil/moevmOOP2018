#include <iostream>

using namespace std;

#include "field.h"
#include "warrior.h"
#include "knight.h"
#include "mage.h"
#include "building.h"

//void getDamage(List<Object*> &army, int count, int i, int j, int damage);
void deleteObjectFromList(Object* object, List<Object*> &army, int& count);
ostream &operator<<(ostream &ostr, Field &fd);
void attackAim(vector<tuple<int, int>>, List<Object*> &army, int&, int);
void mageAttackAim(vector<tuple<int, int>>, List<Object*> &army, int&, int, Mage*);

int main() {
	ifstream file("input.txt");
	Field *field;
	Object *obj;
	field = new Field(file);
	char x, y;
	int input;
	while (true) {
		cout << *field;
		cout << "Current army: green [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		obj = field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - '0' , (int)x - 48);
		if (obj) {
			if (obj->getType() == 'w' || obj->getType() == 'k' || obj->getType() == 'm') {
				cout << "1. Move\n2. Attack" << endl;
				cin >> input;
				switch (input) {
				case 1:
					cout << "1. Move Up\n2. Move Right\n3. Move Down\n4.Move Left" << endl;
					cin >> input;
					switch (input) {
					case 1:
						if (obj->getY() != 0) {
							((Warrior*)obj)->moveUp();
						}
						break;
					case 2:
						if (obj->getX() != field->getXSize() - 1) {
							((Warrior*)obj)->moveRight();
						}
						break;
					case 3:
						if (obj->getY() != field->getYSize() - 1) {
							((Warrior*)obj)->moveDown();
						}
						break;
					case 4:
						if (obj->getX() != 0) {
							((Warrior*)obj)->moveLeft();
						}
						break;
					}
					break;
				case 2:
					switch (obj->getType()) {
					case 'w':
						attackAim(((Warrior*)obj)->attack(), field->getArmyB(), field->getCountArmyB(), ((Warrior*)obj)->getPower());
						break;
					case 'k':
						attackAim(((Knight*)obj)->attack(), field->getArmyB(), field->getCountArmyB(), ((Warrior*)obj)->getPower());
						break;
					case 'm':
						mageAttackAim(((Mage*)obj)->attack(), field->getArmyB(), field->getCountArmyB(), ((Warrior*)obj)->getPower(), (Mage*)obj);
						break;
					}
				}
			}
			else if (obj->getType() == 'b') {
				switch (((Building<>*)obj)->getBuildingType()) {
				case 'w':
					((Building<Warrior>*)obj)->spawn();
					break;
				case 'k':
					((Building<Knight>*)obj)->spawn();
					break;
				case 'm':
					((Building<Mage>*)obj)->spawn();
					break;
				}
			}
		}
		else {
			cout << "No Object here" << endl << "---------------------------------------" << endl;
		}
		if (!field->getCrownB().use_count()) {
			break;
		}
		cout << *field;
		cout << "Current army: red [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		obj = field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48);
		if (obj) {
			if (obj->getType() == 'w' || obj->getType() == 'k' || obj->getType() == 'm') {
				cout << "1. Move\n2. Attack" << endl;
				cin >> input;
				switch (input) {
				case 1:
					cout << "1. Move Up\n2. Move Right\n3. Move Down\n4.Move Left" << endl;
					cin >> input;
					switch (input) {
					case 1:
						if (obj->getY() != 0) {
							((Warrior*)obj)->moveUp();
						}
						break;
					case 2:
						if (obj->getX() != field->getXSize()-1) {
							((Warrior*)obj)->moveRight();
						}
						break;
					case 3:
						if (obj->getY() != field->getYSize()-1) {
							((Warrior*)obj)->moveDown();
						}
						break;
					case 4:
						if (obj->getX() != 0) {
							((Warrior*)obj)->moveLeft();
						}
						break;
					}
					break;
				case 2:
					switch (obj->getType()) {
					case 'w': 
						attackAim(((Warrior*)obj)->attack(), field->getArmyA(), field->getCountArmyA(), ((Warrior*)obj)->getPower());
						break;
					case 'k':
						attackAim(((Knight*)obj)->attack(), field->getArmyA(), field->getCountArmyA(), ((Warrior*)obj)->getPower());
						break;
					case 'm':
						mageAttackAim(((Mage*)obj)->attack(), field->getArmyA(), field->getCountArmyA(), ((Warrior*)obj)->getPower(), (Mage*)obj);
						break;
					}
					
				}
			}
			else if (obj->getType() == 'b') {
				switch (((Building<>*)obj)->getBuildingType()) {
				case 'w':
					((Building<Warrior>*)obj)->spawn();
					break;
				case 'k':
					((Building<Knight>*)obj)->spawn();
					break;
				case 'm':
					((Building<Mage>*)obj)->spawn();
					break;
				}
			}
		}
		else {
			cout << "No Object here" << endl << "---------------------------------------" << endl;
		}
		if (!field->getCrownA().use_count()) {
			break;
		}
	}
	delete field;
	//system("pause");
	return 0;
}