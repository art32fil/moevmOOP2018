#include "field.h"

int main(){
	ifstream fl("G:\\Files\\input.txt");
	int cmd, entr, x, y;
	string clr,cr;
	Field* fld = new Field(fl);
	fld->Arena();
	do {
		cout << "Input army object you want to action (color, creature, x, y) [q to exit]:";
		cin >> clr;
		if (clr == "q") break;
		cin >> cr >> x >> y;
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(32767, '\n');
			break;
		}
		if (fld->Is_Target_Hit(clr,cr, x, y)) {
			if (cr == "m" || cr == "s") {
				cout << "What would you like to do? 1|2" << endl;
				cout << "1. Move" << endl;
				cout << "2. Attack" << endl;
				cin >> cmd;
				switch (cmd) {
				case 1:
				{
					fld->Movement_Menu();
					cin >> entr;
					fld->Movement(clr, entr, x, y);
					fld->Arena();
					break;
				}
				case 2:
				{
					if (!fld->Attack(clr, cr, x, y)) cout << "There is no enemy object." << endl;
					fld->Arena();
					break;
				}
				default:
				{
					cout << "Incorrect command." << endl;
					break;
				}
				}
			}
			else if (cr == "b") {
				fld->Create_Object(clr, x, y);
				fld->Arena();
			}
		}
		else cout << "There is no " << cr <<" object with color "<< clr << endl;
		if (fld->red_army_size == 0)
		{
			cout << "\033[1;32m";
			cout << " Green Army Wins!" << endl;
			cout << "\033[0m";
			break;
		}
		if (fld->green_army_size == 0)
		{
			cout << "\033[0;31m";
			cout << " Red Army Wins!" << endl;
			cout << "\033[0m";
			break;
		}
	} while (1);
	delete fld;
	return 0;
}

