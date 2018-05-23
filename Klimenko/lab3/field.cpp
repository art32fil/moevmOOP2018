#include "field.h"
#include <fstream>
#include <iostream>
#include <string>
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
	ifstream fin("input.txt");
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


	new_team(team1, fin, crown1);
	new_team(team2, fin, crown2);

	cout << "Field fight: END" << endl;

}

Object* battlefield::check_position(_2dim cor) {

	for (auto Elem : *team1) {
		if (Elem->is_on_position(cor)) return Elem->is_on_position(cor);
	}

	for (auto Elem : *team2) {
		if (Elem->is_on_position(cor)) return Elem->is_on_position(cor);
	}
	return NULL;
}
void battlefield::new_team(List<Object*> *new_team, ifstream& fin, const shared_ptr<Crown> t) {
	int size;
	char type;
	fin >> size;
	for (int i = 0; i < size; i++) {
		fin >> type;
		switch (type)
		{
		case('w'):
			new_team->AddEnd(new Warior(fin, t));
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

void battlefield::print() 
{
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
			if (temp) {
				this << *temp;
			}
			else
			{
				cout << " . ";
			};
		}
		cout << endl;
	}
	cout << console.white;
}

int battlefield::hit(_2dim pos, int id) {

	Object* unit = select_by_id(id);
	if (define_type(unit) == 'w') {
		Warior* war = dynamic_cast<Warior *>(unit);
		vector <Object *> *list = select_by_coords(war->get_coords());
		if (list->capacity() == 1) if (unit->get_damage(war->give_force())) if (war->last_representive()) return (war->show_team() == 1) ? 2 : 1; //suicide is hard work
		for (auto obj : *list) {
			if (obj->get_id() == war->get_id()) continue;
			if (auto tmp = obj->get_damage(war->give_force())) {
				if (obj->last_representive()) return war->show_team();
				del_by_id(tmp);
			}
		}
	}
	else {
		cerr << "Selected id is not unit!" << endl;
		return 0;
	}
	return 0;
}


void battlefield::del_by_id(int id) {

	int i = 0;
	bool flag = false;

	for (auto Elem : *team1) {
		if (Elem->get_id() != id) i++; else {
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
		if (Elem->get_id() != id) {
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

Warior * battlefield::relocate(string da_way, Warior *unit) {
	for (char option : da_way) {
		switch (option)
		{
		case('w'):
			if (unit->get_coords().y > 1) unit->move(option);
			else goto end;
			break;
		case('d'):
			if (unit->get_coords().x < x_size) unit->move(option);
			else goto end;
			break;
		case('s'):
			if (unit->get_coords().y < y_size) unit->move(option);
			else goto end;
			break;
		case('a'):
			if (unit->get_coords().x > 1) unit->move(option);
			else goto end;
			break;
		default:
		end:
			cout << "* bump *" << endl;
			return unit;
			break;
		}
	}
	return unit;
}

Object * battlefield::select_by_id(int id)
{
	for (auto Elem : *team1) {
		if (Elem->get_id() == id) return Elem;
	}
	//return NULL;

	for (auto Elem : *team2) {
		if (Elem->get_id() == id) return Elem;
	}
	return NULL;
}

vector <Object*>* battlefield::select_by_coords(_2dim cor) {

	vector <Object* > *temp = new vector<Object*>;

	for (auto Elem : *team1) {
		if (Elem->is_on_position(cor)) temp->push_back(Elem);
	}

	for (auto Elem : *team2) {
		if (Elem->is_on_position(cor)) temp->push_back(Elem);
	}

	return temp;

}

char battlefield::define_type(Object * obj)
{
	if (dynamic_cast<Warior*>(obj)) {
		return 'w';
	}
	if (dynamic_cast<Building*>(obj)) {
		return 'b';
	}
	else return 'o';
}