#include "field.h"

Field::Field(ifstream& fl) {
	if (!fl.is_open()) {
		cout << "There are no file in directory!" << endl;
		exit(1);
		system("pause");
	}
	fl >> x_size >> y_size;
	cout << "Field:" << endl;
	cout << "	x_size = " << x_size << endl;
	cout << "	y_size = " << y_size << endl;
 	shared_ptr<Crown> red_army = shared_ptr<Crown>(new Crown(1));
	clr_red_army = red_army;
	Get_Red_Army(fl, red_army);
	shared_ptr<Crown> green_army = shared_ptr<Crown>(new Crown(0));
	clr_green_army = green_army;
	Get_Green_Army(fl, green_army);
	cout << "Field."<<endl;
}

Field::~Field(){
	cout << "~Field:" << endl;
	red_army.~List();
	green_army.~List();
	cout << "~Field." << endl;
}

void Field::Get_Red_Army(ifstream&fl, const shared_ptr<Crown>& color) {
	fl >> red_army_size;
	char type;
	for (int i = 0; i < red_army_size; i++){
		fl >> type;
		if (type == 'w') {
			red_army.Supl_End(new Warrior(fl, color));
		}
		else if (type == 'b') {
			red_army.Supl_End(new Building(fl, color));
		}
		
	}
}

void Field::Get_Green_Army(ifstream&fl, const shared_ptr<Crown>& color) {
	fl >> green_army_size;
	char type;
	for (int i = 0; i < green_army_size; i++){
		fl >> type;
		if (type == 'w') {
			green_army.Supl_End(new Warrior(fl,color));
		}
		else if (type == 'b') {
			green_army.Supl_End(new Building(fl, color));
		}
	}
}

bool Field::Is_Target_Hit(string clr,int x1,int y1) {
	int type = 0;
	bool flag = 0;
	if (clr == "r") {
		for (auto& it : red_army) {
			if (it->Is_Located(x1, y1) == 2) flag = 1;
		}
	}
	else if (clr == "g") {
		for (auto& it : green_army) {
			if (it->Is_Located(x1, y1) == 2) flag = 1;
		}
	}
	return flag;
}

void Field::Movement_Menu() {
	cout << "Where would you like to move?" << endl;
	cout << "1. Move Up" << endl;
	cout << "2. Move Down" << endl;
	cout << "3. Move Left" << endl;
	cout << "4. Move Right" << endl;
}

void Field::Movement(string clr, int entr, int x, int y) {
	int type = 0;
	if (clr == "r") {
		for (auto it : red_army) {
			if (it->Is_Located(x, y) == 2) {
				switch (entr) {
				case 1:
				{
					if (it->Get_Y() > 0) it->move_up();
					break;
				}
				case 2:
				{
					if (it->Get_Y() < y_size - 1) it->move_down();
					break;
				}
				case 3:
				{
					if (it->Get_X() > 0) it->move_left();
					break;
				}
				case 4:
				{
					if (it->Get_X() < x_size - 1) it->move_right();
					break;
				}
				default:
				{
					cout << "Incorrect command" << endl;
					break;
				}
				}
				break;
			}
		}
	}
	else if (clr == "g"){
		for (auto it : green_army) {
			if (it->Is_Located(x, y) == 2) {
				switch (entr) {
				case 1:
				{
					if (it->Get_Y() > 0) it->move_up();
					break;
				}
				case 2:
				{
					if (it->Get_Y() < y_size - 1) it->move_down();
					break;
				}
				case 3:
				{
					if (it->Get_X() > 0) it->move_left();
					break;
				}
				case 4:
				{
					if (it->Get_X() < x_size - 1) it->move_right();
					break;
				}
				default:
				{
					cout << "Incorrect command" << endl;
					break;
				}
				}
				break;
			}
		}
	}
}

bool Field::Attack(string clr, int x1, int y1, int x2, int y2) {
	int type = 0;
	bool flag = 0;
	if (clr == "r") {
		auto i = red_army.begin();
		while (i != red_army.end()) {
			if (i.ptr->info->Is_Located(x1, y1) == 2) break;
			++i;
		}
		List<tuple<int,int,int>>* range = i.ptr->info->attack();
		for (auto k : *range) {
			if (get<0>(k) == x2 && get<1>(k) == y2) {
				for (auto j: green_army) {
					if (j->Is_Located(x2, y2)) {
						j->Damage(get<2>(k));
						if (j->Is_Dead()) { green_army.Delete(j); green_army_size--; }
						else cout << "Green object got hit" << endl;
						flag = 1;
						break;
					}
					++j;
				}
			} 
		}
		
	}
	else if (clr == "g") {
		auto i = green_army.begin();
		while (i != green_army.end()) {
			if (i.ptr->info->Is_Located(x1, y1) == 2) break;
			++i;
		}
		List<tuple<int, int, int>>* range = i.ptr->info->attack();
		for (auto k : *range) {
			if (get<0>(k) == x2 && get<1>(k) == y2) {
				for (auto j : red_army) {
					if (j->Is_Located(x2, y2)) {
						j->Damage(get<2>(k));
						if (j->Is_Dead()) { red_army.Delete(j); red_army_size--; }
						else cout << "Red object got hit" << endl;
						flag = 1;
						break;
					}
					++j;
				}
			}
		}
	}
	return flag;
}

void Field::Arena() // ‘ункци€, выполн€юща€ отрисовку пол€ бо€
{
	int type = 0;
	bool flag, red;
	cout << "  ";
	for (int i = 0; i < x_size; i++) cout << i;
	cout << endl << " +";
	for (int i = 0; i < x_size; i++) cout << "-";
	cout << "+" << endl;
	for (int i = 0; i < y_size; i++)
	{
		cout << "\033[0m";
		cout << i << "|";
		for (int j = 0; j < x_size; j++)
		{
			flag = 1;
			red = 0;
			for (auto& it : red_army) {
				if (it->Is_Located(j, i) == 2) {
					cout << "\033[0;31m";
					flag = 0;
					if (it->Is_Dead()) {
						cout << "\033[0m";
						cout << ".";
					}
					else cout << "w";
					red = 1;
					break;
				}
				if (it->Is_Located(j, i) == 3) {
					cout << "\033[0;31m";
					flag = 0;
					if (it->Is_Dead()) {
						cout << "\033[0m";
						cout << ".";
					}
					else cout << "b";
					red = 1;
					break;
				}
			}

			for (auto& it : green_army) {
				if (red) break;
				if (it->Is_Located(j, i) == 2) {
					cout << "\033[1;32m";
					if (it->Is_Dead()) {
						cout << "\033[0m";
						cout << ".";
					}
					else cout << "w";
					flag = 0;
					break;
				}
				if (it->Is_Located(j, i) == 3) {
					cout << "\033[1;32m";
					if (it->Is_Dead()) {
						cout << "\033[0m";
						cout << ".";
					}
					else cout << "b";
					flag = 0;
					break;
				}

			}
			if (flag) {
				cout << "\033[0m";
				cout << ".";
			}
			if (j == y_size - 1) cout << "\033[0m" << "|" << endl;

		}
	}
	cout << " +";
	for (int i = 0; i < x_size; i++) cout << "-";
	cout << "+" << endl;
}
