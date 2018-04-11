#pragma once
#include "field.h"
#include "list.h"


Field::Field(ifstream& fl) { // Инициализация поля боя из файла
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
	cout << "Field." << endl;
}

Field::~Field(){ // Говорящий деструктор
	cout << "~Field:" << endl;
	red_army.~List();
	green_army.~List();
	cout << "~Field." << endl;
}

void Field::Get_Red_Army(ifstream& fl, const shared_ptr<Crown>& color) {
	fl >> red_army_size;
	for (int i = 0; i < red_army_size; i++)
		red_army.Supl_End(fl, color);
}

void Field::Get_Green_Army(ifstream& fl, const shared_ptr<Crown>& color) {
	fl >> green_army_size;
	for (int i = 0; i < green_army_size; i++)
		green_army.Supl_End(fl, color);
}

void Field::Arena() // Функция, выполняющая отрисовку поля боя
{
	bool flag;
	cout << "  ";
	for(int i = 0; i < x_size; i++) cout << i;
	cout << " " << endl << " +";
	for(int i = 0; i < x_size; i++) cout << "-";
	cout << "+" << endl;
	for(int i = 0; i < y_size; i++)
	{
		cout << "\033[0m";
		cout << i << "|";
		for (int j = 0; j < x_size; j++)
		{
			flag = 1;
			for (auto& it : red_army) {
				if (it.Is_Located(j, i))
				{
					cout << "\033[0;31m";
					flag = 0;
					if (it.Is_Dead()) { cout << "\033[0m"; cout << "."; }
					else cout << "o";
					break;
				}
			}
			
			for (auto& it : green_army) {
				if (it.Is_Located(j, i))
				{
					cout << "\033[1;32m";
					if (it.Is_Dead()) { cout << "\033[0m"; cout << "."; }
					else cout << "o";
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

bool Field::Is_Target_Hit(int x1, int y1) { // Функция, определяющая, куда выполнено попадание
	bool flag = 0;
	for (auto& it: red_army) {
		if (it.Is_Located(x1, y1)) { cout << "Selected target is red" << endl; flag = 1; }
	}
	for (auto& it: green_army) {
		if (it.Is_Located(x1, y1)) { cout << "Selected target is green" << endl; flag = 1; }
	}
	if (!flag) cout << "There isn't any object here!" << endl;
	return flag;
}

void Field::Attack(int x, int y, int damage) {
	bool flag = 0;
	for (auto& it : red_army) {
		if (it.Is_Located(x, y)) {
			it.Damage(damage);
			Arena();
			if (it.Is_Dead()) red_army.Delete(it);
			flag = 1;
			break;
		}
	}
	if (!flag) {
		for (auto& it : green_army) {
			if (it.Is_Located(x, y)) {
				it.Damage(damage);
				Arena();
				if (it.Is_Dead()) green_army.Delete(it);
				break;
			}
		}
	}
}

istream& operator >>(istream& str, Field& fld){
 str >> fld.x_size >>fld.y_size;
 return str;
}

ostream& operator <<(ostream& str, const Field& fld){
 str << fld.x_size << fld.y_size;
 return str;
}


