#include "field.h"

field::field(int x, int y)
{
	Xsize = x;
	Ysize = y;
}
void field::drow_field() {


	for (int i = 0; i < red_army.size(); i++) {
		if (!red_army[i].is_alive()) { red_army.del(i); }
		

	}
	for (int i = 0; i < green_army.size(); i++) {
		if (!green_army[i].is_alive()) {	green_army.del(i); }
		
	}

	int rSize = red_army.size();
	int gSize = green_army.size();
	for (int i = 0; i < Ysize + 1; i++) {

		for (int j = 0; j < Xsize + 1; j++) {
			point now = { j - 1, i - 1 };
			if (i == 0 && j == 0) {
				cout << "X";
				continue;
			}
			else if (i == 0) {
				cout << j - 1;
				continue;
			}
			else if (j == 0) {
				cout << i - 1;
				continue;
			}
			bool flag = 0;
			for (int k = 0; k < rSize; k++) {
				if (red_army[k].is_there(now)) {
					cout << "\033[31m•\033[0m";
					flag = 1;
					break;
				}
			}


			for (int m = 0; m < gSize; m++) {
				if (green_army[m].is_there(now)) {
					cout << "\033[32m•\033[0m";
					flag = 1;
					break;
				}
			}
			if (!flag) {
				cout << ".";
			}

		}
		cout << endl;
	}
}
void field::create_unit(int x, int y, int h, color c) {
	if (c == red) {
		unit a(x, y, h, red);
		red_army.add_to_end(a);
	}
	else {
		unit b(x, y, h, green);
		green_army.add_to_end(b);
	}
}

void field::enter(ifstream & fin)
{
	size_t q;
	int x, y, hp;
	fin >> this->Xsize >> this->Ysize;
	fin >> q;

	for (int i = 0; i < q; i++)
	{
		fin >> x >> y >> hp;
		this->create_unit(x, y, hp, red);
	}

	fin >> q;
	for (int i = 0; i < q; i++)
	{
		fin >> x >> y >> hp;
		this->create_unit(x, y, hp, green);
	}
}
