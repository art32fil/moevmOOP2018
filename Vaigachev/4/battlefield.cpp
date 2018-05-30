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

vector<Object*> battlefield::return_temp()
{
	return temp;
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


void battlefield::new_team(std::vector<Object*> *new_team,ifstream& fin,const shared_ptr<Crown> t) {
	int size;
	char type;
	fin >> size;
	for (int i = 0; i < size; i++) {
		fin >> type;
		switch (type)
		{
		case('w'):
			new_team->push_back(new Warior(fin,t,type));
			break;
		case('s'):
			new_team->push_back(new Swordsman(fin, t, type));
			break;
		case('m'):
			new_team->push_back(new Magikan(fin, t, type));
			break;
		case('b'):
			char spawn_type;
			/*_2dim spawn_cor;
			Warior* unit_w;
			Building<Warior*>* B_W;
			Swordsman* unit_s;
			Building<Swordsman*>* B_S;
			Magikan* unit_m;
			Building<Magikan*>* B_M;*/
			fin >> spawn_type ;
			switch (spawn_type)
			{
			case('w'): {
				Warior* unit_w = new Warior(fin, t, spawn_type);
				Building<Warior>* B_W = new Building<Warior>(fin, t, type);
				B_W->set_exemplar(unit_w);
				new_team->push_back(B_W); 
			}
				break;
			case('s'): {
				Swordsman* unit_s = new Swordsman(fin, t, spawn_type);
				Building<Swordsman>* B_S = new Building<Swordsman>(fin, t, type);
				B_S->set_exemplar(unit_s);
				new_team->push_back(B_S); 
			}
				break;
			case('m'): {
				Magikan* unit_m = new Magikan(fin, t, spawn_type);
				Building<Magikan>* B_M = new Building<Magikan>(fin, t, type);
				B_M->set_exemplar(unit_m);
				new_team->push_back(B_M); 
			}
				break;
			default:
				break;
			}
		default:
			break;
		}
		
	}
}


battlefield::~battlefield()
{
	cout << "~Field fight: START" << endl;
	//delete team1;
	for (auto o : *team1) delete o;
	team1->clear();
	delete team1;
	cout << "Another ++++++" << endl;;
	//delete team2;
	for (auto o : *team2) delete o;
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
int battlefield::command_to_attack(int id) {
	
	Object* unit = select_by_id(id);
	if (!unit->is_a_building()) {
		Warior* war = dynamic_cast<Warior *>(unit);
		
		return war->attack(list_of_enemies(war));
	}
	
	/*
	Object* unit = select_by_id(id);
	if (define_type(unit) == 'w') {
		Warior* war  = dynamic_cast<Warior *>(unit);
		vector <Object *> *list = select_by_coords(war->get_coords());
		if (list->capacity() == 1) if (unit->get_damage(war->give_force())) if( war->last_representive()) return (war->show_team() == 1) ? 2 : 1 ; //suicide is hard work
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
	return 0;*/

	return 0;
}

/*
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
}*/
/*
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
*/
battlefield *const operator<<(battlefield *const bf, Object &obj)
{
	cout << obj;

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

void battlefield::select_by_coords(_2dim cor) {

	if(!temp.empty()) temp.clear();

	for (auto Elem : *team1) {
		if (Elem->is_on_position(cor)) temp.push_back(Elem);
	}

	for (auto Elem : *team2) {
		if (Elem->is_on_position(cor)) temp.push_back(Elem);
	}

}

char battlefield::define_type(Object * obj)
{
	return obj->get_type();
}

vector<Object*>* battlefield::list_of_enemies(Object *unit)
{

	if (unit->show_team() == 1) return team2;
	if (unit->show_team() == 2) return team1;
	return 0;
}

vector<Object*>* battlefield::list_of_friends(Object *unit)
{

	if (unit->show_team() == 1) return team1;
	if (unit->show_team() == 2) return team2;
	return 0;
}

void battlefield::add_unit(int id)
{
	Object* obj = select_by_id(id);
	if (obj->get_type() == 'b') {
		list_of_friends(obj)->push_back(obj->spawn());
	}
	else {
		cerr << "Not a building!" << endl;
	}

}

