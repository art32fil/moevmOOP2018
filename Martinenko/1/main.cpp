#include "object.h"
#include "field.h"


int main(){
	ifstream f("input.txt");
	int x, y,dmg;
	Field fld(f);
	fld.paint();
	do {
		cout << "input coordinates of target (separated by space) [q to exit]:";
		cin >> x >> y;
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(32767, '\n');
			break;
		}
		if (fld.isIt(x, y)) {
			cout << "input a damage value:";
			cin >> dmg;
			fld.attack(x, y, dmg);
		}

	} while (!cin.fail());
	return 0;
}

