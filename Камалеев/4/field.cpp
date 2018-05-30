#include "field.h"
#include "windows.h"

Field::Field(ifstream& fl) {
	if (!fl.is_open()) {
		cout << "There are no file in directory!" << endl;
		exit(EXIT_FAILURE);
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
		if (type == 's') {
			red_army.Supl_End(new Swordsman(fl, color));
		}
		else if (type == 'b') {
			char s;
			fl >> s;
			if (s == 's')red_army.Supl_End(new Building<Swordsman>(fl, color, s));
			if (s == 'm')red_army.Supl_End(new Building<Magician>(fl, color, s));
		}
		else if (type == 'm') {
			red_army.Supl_End(new Magician(fl, color, x_size, y_size));
		}
		
	}
}

void Field::Get_Green_Army(ifstream&fl, const shared_ptr<Crown>& color) {
	fl >> green_army_size;
	char type;
	for (int i = 0; i < green_army_size; i++){
		fl >> type;
		if (type == 's') {
			green_army.Supl_End(new Swordsman(fl, color));
		}
		else if (type == 'b') {
			char s;
			fl >> s;
			if (s == 's')green_army.Supl_End(new Building<Swordsman>(fl, color, s));
			if (s == 'm')green_army.Supl_End(new Building<Magician>(fl, color, s));
		}
		else if (type == 'm') {
			green_army.Supl_End(new Magician(fl, color, x_size, y_size));
		}
	}
}

bool Field::Is_Target_Hit(string clr,string warrior, int x1, int y1) {
	bool flag = 0;
	if (clr == "r") {
		if (warrior == "b") {
			for (auto& it : red_army) {
				if (it->Is_Located(x1, y1) == 3) flag = 1;
			}
		}
		if (warrior == "m") {
			for (auto& it : red_army) {
				if (it->Is_Located(x1, y1) == 4) flag = 1;
			}
		}
		if (warrior == "s") {
			for (auto& it : red_army) {
				if (it->Is_Located(x1, y1) == 5) flag = 1;
			}
		}
	}
	else if (clr == "g") {
		if (warrior == "b") {
			for (auto& it : green_army) {
				if (it->Is_Located(x1, y1) == 3) flag = 1;
			}
		}
		if (warrior == "m") {
			for (auto& it : green_army) {
				if (it->Is_Located(x1, y1) == 4) flag = 1;
			}
		}
		if (warrior == "s") {
			for (auto& it : green_army) {
				if (it->Is_Located(x1, y1) == 5) flag = 1;
			}
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
			if (it->Is_Located(x, y) > 3) {
				switch (entr) {
				case 1:
				{
					if (it->Get_Y() >= 1) it->move_up();
					break;
				}
				case 2:
				{
					if (it->Get_Y() <= y_size - 2) it->move_down();
					break;
				}
				case 3:
				{
					if (it->Get_X() >= 1) it->move_left();
					break;
				}
				case 4:
				{
					if (it->Get_X() <= x_size - 2) it->move_right();
					break;
				}
				default:
				{
					cout << "Incorrect command." << endl;
					break;
				}
				}
				break;
			}
		}
	}
	else if (clr == "g"){
		for (auto it : green_army) {
			if (it->Is_Located(x, y) > 3) {
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
					cout << "Incorrect command." << endl;
					break;
				}
				}
				break;
			}
		}
	}
}

int Field::Get_Min_Enemy_HP(string clr, int x, int y) {
	int min = -1;
	if (clr == "r") {
		for (auto &it : red_army) {
			if (it->Is_Located(x, y)) {
				if (min == -1) min = it->Get_HP();
				if (it->Get_HP() < min) min = it->Get_HP();
			}
		}
	}
	else if (clr == "g") {
		for (auto &it : green_army) {
			if (it->Is_Located(x, y)) {
				if (min == -1) min = it->Get_HP();
				if (it->Get_HP() < min) min = it->Get_HP();
			}
		}
	}
	return min;
}

tuple<int, int> Field::Min_Ray(string clr, List<tuple<int, int, int>>* distance) {
	tuple<int, int> min = make_tuple(-1, -1);
	if (clr == "r") {
		for (auto it : *distance) {
			for (auto it1 : green_army) {
				if (!it1->Is_Located(get<0>(it), get<1>(it))) continue;
				else {
					if (get<0>(min) == -1 && get<1>(min) == -1) { 
						if(it1->Get_X()== get<0>(it) && it1->Get_X() == get<1>(it)) min = make_tuple(it1->Get_X(), it1->Get_Y());
						else  min = make_tuple(it1->Get_X1(get<0>(it)), it1->Get_Y1(get<1>(it)));
					}
					if (it1->Get_HP() < Get_Min_Enemy_HP("green", get<0>(min), get<1>(min))) { 
						if (it1->Get_X() == get<0>(it) && it1->Get_X() == get<1>(it)) min = make_tuple(it1->Get_X(), it1->Get_Y());
						else  min = make_tuple(it1->Get_X1(get<0>(it)), it1->Get_Y1(get<1>(it)));
					
					}
				}
			}

		}
	}
	else if (clr == "g") {
		for (auto it : *distance) {
			for (auto it1 : red_army) {
				if (!it1->Is_Located(get<0>(it), get<1>(it)))  continue;
				else {
					if (get<0>(min) == -1 && get<1>(min) == -1) {
						if (it1->Get_X() == get<0>(it) && it1->Get_X() == get<1>(it)) min = make_tuple(it1->Get_X(), it1->Get_Y());
						else  min = make_tuple(it1->Get_X1(get<0>(it)), it1->Get_Y1(get<1>(it)));
					}
					if (it1->Get_HP() < Get_Min_Enemy_HP("red", get<0>(min), get<1>(min))) {
						if (it1->Get_X() == get<0>(it) && it1->Get_X() == get<1>(it)) min = make_tuple(it1->Get_X(), it1->Get_Y());
						else  min = make_tuple(it1->Get_X1(get<0>(it)), it1->Get_Y1(get<1>(it)));
					}
				}
			}

		}
	}
	return min;
}

bool Field::Attack(string clr, string kind, int x1, int y1) {
	bool flag = 0;
	if (clr == "r") {
		auto i = red_army.begin();
		if (kind == "m") {
			while (i != red_army.end()) {
				if (i.ptr->info->Is_Located(x1, y1) == 4) break;
				++i;
			}
			List<tuple<int, int, int>>* range = i.ptr->info->attack();
			tuple<int, int> min = Min_Ray(clr, range);
			List<tuple<int, int, int>>* min_distance;
			if (x1 < get<0>(min) && y1 == get<1>(min)) {
				min_distance = i.ptr->info->right_distance();
				for (auto it1 : *min_distance) {
					auto it2 = green_army.begin();
					while (it2 != green_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == green_army.last()) {
									green_army.Delete(it2.ptr->info);
									green_army_size--;
									it2 = green_army.end();
									flag = 1;
								}
								else {
									it2++;
									green_army.Delete(it2.ptr->prev->info);
									green_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The green object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

			if (x1 > get<0>(min) && y1 == get<1>(min)) {
				min_distance = i.ptr->info->left_distance();
				for (auto it1 : *min_distance) {
					auto it2 = green_army.begin();
					while (it2 != green_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == green_army.last()) {
									green_army.Delete(it2.ptr->info);
									green_army_size--;
									it2 = green_army.end();
									flag = 1;
								}
								else {
									it2++;
									green_army.Delete(it2.ptr->prev->info);
									green_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The green object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 > get<1>(min)) {
				min_distance = i.ptr->info->up_distance();
				for (auto it1 : *min_distance) {
					auto it2 = green_army.begin();
					while (it2 != green_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == green_army.last()) {
									green_army.Delete(it2.ptr->info);
									green_army_size--;
									it2 = green_army.end();
									flag = 1;
								}
								else {
									it2++;
									green_army.Delete(it2.ptr->prev->info);
									green_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The green object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 < get<1>(min)) {
				min_distance = i.ptr->info->down_distance();
				for (auto it1 : *min_distance) {
					auto it2 = green_army.begin();
					while (it2 != green_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == green_army.last()) {
									green_army.Delete(it2.ptr->info);
									green_army_size--;
									it2 = green_army.end();
									flag = 1;
								}
								else {
									it2++;
									green_army.Delete(it2.ptr->prev->info);
									green_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The green object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
}
		else if (kind == "s") {
			while (i != red_army.end()) {
				if (i.ptr->info->Is_Located(x1, y1) == 5) break;
				++i;
			}

			List<tuple<int, int, int>>* range = i.ptr->info->attack();
			tuple<int, int> min = Min_Ray(clr, range);
			for (auto j : green_army) {
				if (j->Is_Located(get<0>(min), get<1>(min))) {
					j->Damage(get<2>(*(range->begin())));
					if (j->Is_Dead()) { green_army.Delete(j); green_army_size--; }
					else cout << "The green object got Damage" << endl;
					flag = 1;
					break;
				}
				++j;
			}
		}
	}
	else if (clr == "g") {
		auto i = green_army.begin();
		if (kind == "m") {
			while (i != green_army.end()) {
				if (i.ptr->info->Is_Located(x1, y1) == 4) break;
				++i;
			}
			List<tuple<int, int, int>>* range = i.ptr->info->attack();
			tuple<int, int> min = Min_Ray(clr, range);
			List<tuple<int, int, int>>* min_distance;
			if (x1 < get<0>(min) && y1 == get<1>(min)) {
				min_distance = i.ptr->info->right_distance();
				for (auto it1 : *min_distance) {
					auto it2 = red_army.begin();
					while (it2 != red_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == red_army.last()) {
									red_army.Delete(it2.ptr->info);
									red_army_size--;
									it2 = red_army.end();
									flag = 1;
								}
								else {
									it2++;
									red_army.Delete(it2.ptr->prev->info);
									red_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The red object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

			if (x1 > get<0>(min) && y1 == get<1>(min)) {
				min_distance = i.ptr->info->left_distance();
				for (auto it1 : *min_distance) {
					auto it2 = red_army.begin();
					while (it2 != red_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == red_army.last()) {
									red_army.Delete(it2.ptr->info);
									red_army_size--;
									it2 = red_army.end();
									flag = 1;
								}
								else {
									it2++;
									red_army.Delete(it2.ptr->prev->info);
									red_army_size--;
									flag = 1;
								}
							}else { flag = 1; cout << "The red object got Damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 > get<1>(min)) {
				min_distance = i.ptr->info->up_distance();
				for (auto it1 : *min_distance) {
					auto it2 = red_army.begin();
					while (it2 != red_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == red_army.last()) {
									red_army.Delete(it2.ptr->info);
									red_army_size--;
									it2 = red_army.end();
									flag = 1;
								}
								else {
									it2++;
									red_army.Delete(it2.ptr->prev->info);
									red_army_size--;
									flag = 1;
								}
							}
							{flag = 1; cout << "The red object got Damage" << endl; it2++; }
							
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 < get<1>(min)) {
				min_distance = i.ptr->info->down_distance();
				for (auto it1 : *min_distance) {
					auto it2 = red_army.begin();
					while (it2 != red_army.end()) {
						if (it2.ptr->info->Is_Located(get<0>(it1), get<1>(it1))) {
							it2.ptr->info->Damage(get<2>(it1));
							if (it2.ptr->info->Is_Dead()) {
								if (it2 == red_army.last()) {
									red_army.Delete(it2.ptr->info);
									red_army_size--;
									it2 = red_army.end();
									flag = 1;
								}
								else {
									it2++;
									red_army.Delete(it2.ptr->prev->info);
									red_army_size--;
									flag = 1;
								}
							}
							else { flag = 1; cout << "The red object got Damage" << endl; it2++; }
							
						}
						else it2++;
					}
				}
			}
}
		else if (kind == "s") {
			while (i != green_army.end()) {
				if (i.ptr->info->Is_Located(x1, y1) == 5) break;
				++i;
			}
			List<tuple<int, int, int>>* range = i.ptr->info->attack();
			tuple<int, int> min = Min_Ray(clr, range);
			for (auto j : red_army) {
				if (j->Is_Located(get<0>(min), get<1>(min))) {
					j->Damage(get<2>(*(range->begin())));
					if (j->Is_Dead()) { red_army.Delete(j); red_army_size--; }
					else cout << "The red object got Damage" << endl;
					flag = 1;
					break;
				}
				++j;
			}
		}
	}
	return flag;
}

void Field::Arena() {
	bool flag, red;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "  ";
	for (int i = 0; i < x_size; i++) cout << i;
	cout << endl << " +";
	for (int i = 0; i < x_size; i++) cout << "-";
	cout << "+" << endl;
	for (int i = 0; i < y_size; i++) {
		//cout<<"\033[0m";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << i << "|";
		for (int j = 0; j < x_size; j++) {
			flag = 1;
			red = 0;
			for (auto& it : red_army) {
				if (it->Is_Located(j, i) == 3) {
					//cout<<"\033[0;31m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					flag = 0;
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "b";
					red = 1;
					break;
				}
				if (it->Is_Located(j, i) == 4) {
					//cout<<"\033[0;31m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					flag = 0;
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "m";
					red = 1;
					break;
				}
				if (it->Is_Located(j, i) == 5) {
					//cout<<"\033[0;31m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					flag = 0;
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "s";
					red = 1;
					break;
				}
			}
			for (auto& it : green_army) {
				if (red) break;
				if (it->Is_Located(j, i) == 3) {
					//cout <<"\033[1;32m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "b";
					flag = 0;
					break;
				}
				if (it->Is_Located(j, i) == 4) {
					//cout <<"\033[1;32m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "m";
					flag = 0;
					break;
				}
				if (it->Is_Located(j, i) == 5) {
					//cout <<"\033[1;32m";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					if (it->Is_Dead()) {
						//cout<<"\033[0m";
						SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
						cout << ".";
					}
					else cout << "s";
					flag = 0;
					break;
				}
			}
			if (flag) {
				//cout<<"\033[0m";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				cout << ".";
			}
			if (j == y_size - 1) { SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); cout << "|" << endl; }
		}
	}
	//cout<<"\033[0m";
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	cout << " +";
	for (int i = 0; i < x_size; i++)cout << "-";
	cout << "+" << endl;
}

ostream& operator<<(ostream& ostr, const Field& fld) {
	ostr << fld.x_size << fld.y_size;
	return ostr;
}

istream& operator>>(istream &istr, Field &fld){
	istr >> fld.x_size >>fld.y_size;
 return istr;
}

void Field::Create_Object(string clr, int x, int y) {
	if (clr == "r") {
		for (auto it : red_army) {
			if (it->Is_Located(x, y) == 3) {
				int x1, y1, hp, strength;
				cin >> x1 >> y1 >> hp >> strength;
				if (it->Get_C() == 's') {
					cout << "Enter coordinates, hp, and strength of swordsman:";
					red_army.Supl_End(it->create(x1, y1, hp, strength, it->Get_Crown()));
				}
				else if (it->Get_C() == 'm') {
					cout << "Enter coordinates, hp, and strength of magician:";
					red_army.Supl_End(it->create(x1, y1, hp, strength, it->Get_Crown()));
				}
				break;
			}
		}

	}
	else if (clr == "g") {
		for (auto it : green_army) {
			if (it->Is_Located(x, y) == 3) {
				int x1, y1, hp, strength;
				cout << "Input the data of object (x, y, hp , strength):" << endl;
				cin >> x1 >> y1 >> hp >> strength;
				if (it->Get_C() == 's') {
					green_army.Supl_End(it->create(x1, y1, hp, strength, it->Get_Crown()));
				}
				else if (it->Get_C() == 'm') {
					green_army.Supl_End(it->create(x1, y1, hp, strength, it->Get_Crown()));
				}
				break;
			}
		}
	}
}



