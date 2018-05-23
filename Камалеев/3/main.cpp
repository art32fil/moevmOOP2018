#include "field.h"

int main(){
	ifstream fl("input.txt");
	int cmd, entr, x, y;
	string clr;
	Field* fld = new Field(fl);
	fld->Arena();
	do {
		cout << "Input army object you want to action (color, x, y) [q to exit]:";
		cin >> clr;
		if (clr == "q") break;
		cin >> x >> y;
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(32767, '\n');
			break;
		}
		if (fld->Is_Target_Hit(clr, x, y)) {
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
				if (!fld->Attack(clr, x, y, x, y)) cout << "Enemy object didn't located here!" << endl;
				fld->Arena();
				break;
			}
			default:
			{
				cout << "Incorrect command" << endl;
				break;
			}
			}
		}
		else cout << "There are no warrior with color "<< clr << endl;

		if (fld->red_army_size == 0) 
		{ 
			cout <<"\033[1;32m";
			cout << " Green Army Wins!" << endl;
			cout <<"\033[0m";
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
	system("pause");
	return 0;
}

