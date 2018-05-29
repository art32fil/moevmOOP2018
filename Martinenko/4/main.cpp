#include "field.h"

int main(){
	ifstream f("input.txt");
	int cmd, x, y;
	string clr,kind,dir;
	Field* fld = new Field(f);
	fld->paint();
	do {
		cout << "input army object you want to action (color,kind, x, y) [q to exit]:";
		cin >> clr;
		if (clr == "q")break;
		cin >> kind >> x >> y;
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(32767, '\n');
			break;
		}
		if (fld->isIt(clr,kind,x, y)) {
			if (kind == "magician" || kind == "swordsman") {
				cout << "1. <dir> - move" << endl;
				cout << "2. attack" << endl;
				cin >> cmd;
				switch (cmd) {
				case 1:
				{
					cin >> dir;
					fld->move(clr, x, y, dir);
					fld->paint();
					break;
				}
				case 2:
				{
					if (!fld->attack(clr,kind, x, y))cout << "There are no enemy objects in the range area." << endl;
					fld->paint();
					break;
				}
				default:
				{
					cout << "Incorrect command." << endl;
					break;
				}
				}
			}
			if (kind == "building") {
				fld->add_warrior(clr, x, y);
				fld->paint();
			}
		}else cout << "There is no " << kind << "object with color "<< clr << endl;
		if (fld->isArmyA()) { cout << "		GREEN WINS!!!" << endl; break; }
		if (fld->isArmyB()) { cout << "		RED WINS!!!" << endl; break; }
	} while (1);
	delete fld;
	return 0;
}

