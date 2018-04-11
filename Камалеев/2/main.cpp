#include "object.h"
#include "field.h"

int main()
{
	//ifstream fl("input.txt");
	//int x, y, damage;
	ifstream fl("input.txt");
	int x, y, damage;
	Field field(fl);
	field.Arena();
	do {
		cout << "input coordinates of target (separated by space) [q to exit]:";
		cin >> x >> y;
		if (cin.fail()) {
			cin.clear(); cin.ignore(32767, '\n');
			break;
		}
		if (field.Is_Target_Hit(x, y)) {
			cout << "input a damage value:";
			cin >> damage;
			field.Attack(x, y, damage);
		}

	} while (!cin.fail());
	return 0;
	//shared_ptr<Crown> red_army = shared_ptr<Crown>(new Crown(1));
	//Object obj(1, 2, 3, red_army);
	//fl >> obj;
	return 0;
}



