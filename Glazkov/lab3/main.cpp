#include <iostream>

using namespace std;

#include "field.h"

//void getDamage(List<Object*> &army, int count, int i, int j, int damage);
void deleteObjectFromList(Object* object, List<Object*> &army, int& count);
ostream &operator<<(ostream &ostr, Field &fd);

int main() {
	int input;
	ifstream file("input.txt");
	Field *field;
	cout << "1. From file\n2. From console" << endl;
	cin >> input;
	switch (input) {
	case 1:
		field = new Field(file);
		break;
	case 2:
		field = new Field(cin);
		break;
	default:
		return 0;
	}
	char x, y;
	int damage;
	while (true) {
		cout << *field;
		cout << "Current army: green [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		cout << "Eneter damage: ";
		cin >> damage;
		if (field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48)) {
			field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48)->getDamage(damage);
			if (field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48)->getHp() <= 0) {
				deleteObjectFromList(field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48), field->getArmyB(), field->getCountArmyB());
				//cout << field->getCrownB().use_count() << endl;
			}
		}
		else {
			cout << "No Enemy here" << endl << "---------------------------------------" << endl;
		}
		cout << *field;
		cout << "Current army: red [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		cout << "Eneter damage: ";
		cin >> damage;
		if (field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48)) {
			field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48)->getDamage(damage);
			if (field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48)->getHp() <= 0) {
				deleteObjectFromList(field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48), field->getArmyA(), field->getCountArmyA());
				//cout << field->getCrownA().use_count() << endl;
			}
		}
		else {
			cout << "No Enemy here" << endl << "---------------------------------------" << endl;
		}
	}
	delete field;
	system("pause");
	return 0;
}