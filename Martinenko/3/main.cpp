#include "field.h"

int main(){
	ifstream f("input.txt");
	int cmd, x, y;
	string clr,dir;
	Field* fld = new Field(f);
	fld->paint();
	do {
		cout << "input army object you want to action (color, x, y) [q to exit]:";
		cin >> clr;
		if (clr == "q")break;
		cin >> x >> y;
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(32767, '\n');
			break;
		}
		if (fld->isIt(clr,x, y)) {
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
				if (!fld->attack(clr, x, y, x, y))cout << "There is no enemy object." << endl;
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
		else cout << "There is no warror with color "<< clr << endl;
		if (fld->isArmyA()) { cout <<"\033[1;32m";cout << "		GREEN WINS!!!" << endl;cout<<"\033[0m"; break; }
		if (fld->isArmyB()) {  cout<<"\033[0;31m";cout << "		RED WINS!!!" << endl;cout<<"\033[0m"; break; }
	} while (1);
	delete fld;
	return 0;
}

