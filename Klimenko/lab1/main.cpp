#include <iostream>
#include "container.h"
#include "unit.h"
#include <fstream>
#include <stdio.h>
#include "field.h"
using namespace std;

int main()
{
	ifstream fin("input.txt");
	field f;
	f.enter(fin);
	f.drow_field();
	char fl = 'n';
	int x, y, d;
	point p;
	while (fl != 'y') {

		cout << "Enter coordinates of target: " << endl;
		cin >> x >> y;
		p.x = x;
		p.y = y;
		cout << "Enter damage " << endl;
		cin >> d;
		for (int i = 0; i < f.red_army.size(); i++) {
			if (f.red_army[i].is_there(p)) {
				f.red_army[i].get_damage(d);
				break;
			}
		}

		for (int i = 0; i < f.green_army.size(); i++) {
			if (f.green_army[i].is_there(p)) {
				f.green_army[i].get_damage(d);
				break;
			}
		}

		f.drow_field();
		
		cout << "Do you whant to quit?" << endl;
		cin >> fl;
	}

	system("pause");

	return 0;
}
