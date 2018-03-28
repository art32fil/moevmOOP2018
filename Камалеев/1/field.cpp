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
	Get_Armies(fl);
	cout << "Field." << endl;
}
Field::~Field(){ // Говорящий деструктор
	cout << "~Field:" << endl;
	red_army.~List();
	green_army.~List();
	cout << "~Field." <<endl;
	//system("pause");
}

void Field::Get_Armies(ifstream& fl){ // Инициализация контейнеров-армий объектами
	fl >> red_army_size;
	for (int i = 0; i < red_army_size; i++) {
		red_army.Supl_End(&red_army,new Object(fl));
	}
	fl >> green_army_size;
	for (int i = 0; i < green_army_size; i++) {
		green_army.Supl_End(&green_army, new Object(fl));
	}
}

void Field::Arena() // Функция, выполняющая отрисовку поля боя
{
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
			auto it1 = red_army.begin();
			auto it2 = green_army.begin();
			for (; it1 != red_army.end(); it1++)
			{
				if (it1.ptr->info.Is_Located(j, i))
				{
					cout<< "\033[0;31m";		
					if (it1.ptr->info.Is_Dead()) cout << "x";
					else cout << "o";
					break;
				}
			}

			for (; it2 != green_army.end(); it2++)
			{
				if (it2.ptr->info.Is_Located(j, i))
				{
					cout << "\033[1;32m";
					if (it2.ptr->info.Is_Dead()) cout << "x";
					else cout << "o";
					break;
				}
			}
			if (it1 == red_army.end() && (it2 == green_army.end()))
				cout << "\033[0m" << ".";

			if (j == y_size - 1) cout << "\033[0m" << "|" << endl;
		}
	
	}
	cout << " +";
	for (int i = 0; i < x_size; i++) cout << "-";
	cout << "+" << endl;
}

bool Field::Is_Target_Hit(int x1, int y1) { // Функция, определяющая, куда выполнено попадание
	bool flag = false;
	for (auto it = red_army.begin(); it != red_army.end(); it++) {
		if (it.ptr->info.Is_Located(x1, y1)) { cout << "Selected target is red" << endl; flag = true; }
	}
	for (auto it = green_army.begin(); it != green_army.end(); it++) {
		if (it.ptr->info.Is_Located(x1, y1)) { cout << "Selected target is green" << endl; flag = true; }
	}
	if (!flag) cout << "There isn't any object here!" << endl;
	return flag;
}

void Field::Attack(int x, int y, int damage) {

		auto it = red_army.begin();
		while (it != red_army.end()) {
			if (it.ptr->info.Is_Located(x, y)) {
				it.ptr->info.Damage(damage);
				break;
			}
			it++;
		}
		
		it = green_army.begin();
		while (it != green_army.end()) {
			if (it.ptr->info.Is_Located(x, y)) { 
				it.ptr->info.Damage(damage);
				break;
			}
			it++;
		}
		Arena();
}
