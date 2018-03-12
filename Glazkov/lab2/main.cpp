#include <iostream>
#include "object.h"
#include "field.h"

using namespace std;
int main() {

	ifstream file("input.txt");
	Field *field = new Field(file);
	char x, y;
	int damage;
	while (true) {
		field->printField();
		cout << "Current army: green [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		if (field->checkArmyCoords(field->getArmyB(), field->getCountArmyB(), (int)y-48, (int)x - 48)) {
			cout << "Eneter damage: ";
			cin >> damage;
			field->getDamage(field->getArmyB(), field->getCountArmyB(), (int)y - 48, (int)x - 48, damage);
		}
		else {
			cout << "No Enemy here" << endl << "---------------------------------------" << endl;
		}
		field->printField();
		cout << "Current army: red [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		if (field->checkArmyCoords(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48)) {
			cout << "Eneter damage: ";
			cin >> damage;
			field->getDamage(field->getArmyA(), field->getCountArmyA(), (int)y - 48, (int)x - 48, damage);
		}
		else {
			cout << "No Enemy here" << endl << "---------------------------------------" << endl;
		}
	}
	delete field;
	system("pause");
	return 0;
}