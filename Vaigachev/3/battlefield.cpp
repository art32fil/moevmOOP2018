#include "battlefield.h"
#include <fstream>
#include <iostream>
#include <string>
//#include <Windows.h>
//#include <list.cpp>
//#include <list.h>
#include "list.cpp"



const struct ConsoleColor {
	const string black = "\033[22;30m";
	const string red = "\033[22;31m";
	const string green = "\033[22;32m";
	const string brown = "\033[22;33m";
	const string blue = "\033[22;34m";
	const string magenta = "\033[22;35m";
	const string cyan = "\033[22;36m";// - cyan
	const string gray = "\033[22;37m";// - gray
	const string darkgrey = "\033[01;30m";// - dark gray
	const string lightred = "\033[01;31m";// - light red
	const string lightgreen = "\033[01;32m";// - light green
	const string yellow = "\033[01;33m";// - yellow
	const string lightblue = "\033[01;34m";// - light blue
	const string lightmagneta = "\033[01;35m";// - light magenta
	const string lightcyan = "\033[01;36m";// - light cyan
	const string white = "\033[01;37m";// - white
} console;
#define DEFBACKGR console.black
#define DEFFOREGR console.white
using namespace std;

battlefield::battlefield()
{
	cout << "Field fight: START" << endl;
	ifstream fin("data.txt");
	if (fin.eof()) {
		cerr << "File not found!" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	fin >> x_size >> y_size;
	cout << "	x_size = " << x_size << endl;
	cout << "	y_size = " << y_size << endl;

	const shared_ptr<Crown> crown1(new Crown(1));
	const shared_ptr<Crown> crown2(new Crown(2));


 	new_team(team1, fin,crown1);
	new_team(team2, fin,crown2);

	cout << "Field fight: END" << endl;
	/*
	for (auto Elem : *team1) {
		cout << "-------" << endl;
		cout << Elem->show_health() << endl;
		Elem->get_damage(7);
		cout << Elem->show_health() << endl;
	}
	*/
}

Object* battlefield::check_position(_2dim cor) {

	for (auto Elem : *team1) {
		if (Elem->is_on_position(cor)) return Elem->is_on_position(cor);
	}
	//return NULL;

	for (auto Elem : *team2) {
		if (Elem->is_on_position(cor)) return Elem->is_on_position(cor);
	}
	return NULL;
}
//todo: make reading of building , warrior & default
void battlefield::new_team(List<Object*> *new_team,ifstream& fin,const shared_ptr<Crown> t) {
	int size;
	char type;
	fin >> size;
	for (int i = 0; i < size; i++) {
		fin >> type;
		switch (type)
		{
		case('w'):
			new_team->AddEnd(new Warior(fin,t));
			break;
		case('b'):
			new_team->AddEnd(new Building(fin, t));
			break;
		default:
			break;
		}
		
	}
}


battlefield::~battlefield()
{
	cout << "~Field fight: START" << endl;
	delete team1;
	cout << "Another ++++++" << endl;;
	delete team2;
	cout << "~Field fight: END" << endl;
}

void battlefield::print() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, (WORD)((DEFBACKGR << 4) | DEFFOREGR));
	cout << console.yellow;
	cout << " + ";

	for (int i = 1; i < x_size + 1; i++) {
		printf("%2.d ", i);
	}
	cout << endl;
	for (int i = 1; i < x_size + 1; i++) {
		for (int j = 1; j < y_size + 1; j++) {
			if (j == 1) {
				cout << console.yellow;
				printf("%3.d", i);
				cout << DEFFOREGR;
			}
			auto temp = check_position({ j,i });
			if (temp) {/*
				if (temp->show_team() == 1) {
					//SetConsoleTextAttribute(hConsole, (WORD)((DEFBACKGR << 4) | Blue));
					//cout << console.blue;
					if (check_position({ j,i })->show_health() > 0) cout << " O ";
					else cout << " X ";
					//SetConsoleTextAttribute(hConsole, (WORD)((DEFBACKGR << 4) | DEFFOREGR));
					cout << DEFFOREGR;
				}
				if (check_position({ j,i })->show_team() == 2) {
					//SetConsoleTextAttribute(hConsole, (WORD)((DEFBACKGR << 4) | Red));
					//cout << console.red;
					if (check_position({ j,i })->show_health() > 0) cout << " O ";// << i << j;
					else cout << "X";
					//SetConsoleTextAttribute(hConsole, (WORD)((DEFBACKGR << 4) | DEFFOREGR));
					cout << DEFFOREGR;
				}*/
				this << *temp ;
			}
			else
			{
				cout << " . ";
			};
		}
		cout << endl;
	}
	//SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	cout << console.white;
}

//todo: bad realization
int battlefield::hit(_2dim pos, int dmg) {

	Object* temp = check_position(pos);
	if ((temp->get_damage(dmg))) {
		cout << endl << "count - " << temp->count << endl << "amount - " << temp->amount << endl << "use count " << temp->use_count() << endl;
		if (temp->last_representive()) return temp->show_team();
		del_from_position(pos);
	};
	return 0;
}


void battlefield::del_from_position(_2dim cor) {

	int i = 0;
	bool flag = false;

	for (auto Elem : *team1) {
		if (!Elem->is_on_position(cor)) i++; else {
			flag = true;
			break;
		}
	}
	if (flag) {
		team1->DelIndex(i);
		return;
	}

	int j = 0;
	bool mflag = false;
	for (auto Elem : *team2) {
		if (!Elem->is_on_position(cor)) {
			j++;

		}
		else {
			mflag = true;
			break;
		}
	}
	if (mflag) {
		team2->DelIndex(j);
		return;
	}
}

battlefield *const operator<<(battlefield *const bf, Object &obj)
{
	if (dynamic_cast<Warior*>(&obj)) {
		cout << *dynamic_cast<Warior*>(&obj);
	}
	if (dynamic_cast<Building*>(&obj)) {
		cout << *dynamic_cast<Building*>(&obj);
	}

	return bf;
}