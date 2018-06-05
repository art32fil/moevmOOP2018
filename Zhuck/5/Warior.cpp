#include "Warior.h"
#include <stack>

using namespace std;


Warior::Warior(ifstream& fin, const shared_ptr<Crown> t,char type): Object(fin,t,type)
{
	fin >> force;
	cout << "Warior : START:" << endl;
	cout << "	force = " << force << endl;
	cout << "	type  = " << type << endl;
	cout << "Warior: END." << endl ;
}

Warior::Warior(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type) : Object(posit, hp, t, type)
{
	force = forc;
	cout << "Warior : START:" << endl;
	cout << "	force = " << force << endl;
	cout << "	type  = " << type << endl;
	cout << "Warior: END." << endl;
}

Warior::Warior(const Warior & W) :Object(W)
{
	
	force = W.force;
	cout << "$Warior : START:" << endl;
	cout << "	force = " << force << endl;
	//cout << "	type  = " << type << endl;
	cout << "$Warior: END." << endl;
	//cout << "Copy created!" << endl;
	//return new Warior(W);
}



Warior::~Warior()
{
	cout << endl;
	cout << "~Warior : START:" << endl;
	cout << "	force = " << force << endl;
	cout << "~Warior: END." << endl ;
}
/*
istream &operator>>(istream &in, Warior &ob) {
	in >> (Object&) ob >> ob.force;
	return in;
}*/
/*
ostream &operator<<(ostream &out, Warior &ob) {
	
}
*/
Warior* Warior::move(char option) {
	switch (option)
	{
	case('w'):
		pos.y--;
		break;
	case('d'):
		pos.x++;
		break;
	case('s'):
		pos.y++;
		break;
	case('a'):
		pos.x--;
		break;
	default:
		cerr << "wrong command! " << option << endl;
		break;
	}
	return this;
}

int Warior::give_force()
{
	return force;
}

//todo: delete and do with vector
int Warior::attack(vector <Object*> * enemies)
{


	
	_2dim m_cords = get_coords();

	//dont delete and use for at the same time - use stack
	stack<int> deleted_ides;
	int tmp = -1; // no result

	// Processing of attack without hitting
	for (Object* e : *enemies) {
		if (available_rivals(e))
			tmp = e->get_damage(give_force());
		if (tmp != -1 && !e->last_representive()) {
			//del_by_id(e->get_id(), enemies);
			deleted_ides.push(e->get_id());
			tmp = -1;
		}
		else{
			if(e->last_representive()) return e->show_team();
		}
	}

	
	//deleting from the field
	int i = -1;
	while (!deleted_ides.empty()) {
		i = deleted_ides.top();
		
		del_by_id(i, enemies);
		if (enemies->empty())
			return show_team(); // this team won
		deleted_ides.pop();		
	}

	
	return 0; // all ok
	

}

void Warior::show_stats()
{
	cout << " type: = " << type << "; id = " << get_id() << "; team = " << show_team() << "; force = " << give_force() << "; health = " << show_health();
}

void Warior::print(ostream &out) {
	if (this->show_team() == 1) // 1
		out << "\033[32m";
	if (this->show_team() == 2) // 0
		out << "\033[31m";
	out << " W " << "\033[0m";
}

void Warior::del_by_id(int id, vector <Object*>* enem) {
	
	if (id == -1) return;

	int i = 0;
	//bool flag = false;

	for (auto o : *enem) {
		if (o->get_id() == id) {
			delete o;
			break;
		}
		i++;
	}

	enem->erase(enem->begin() + i);
	/*
	for (auto Elem : *enem) {
		if (Elem->get_id() != id) i++; else {
			flag = true;
			break;
		}
	}
	if (flag) {
		delete enem->at(i);
		enem->erase(enem->begin() + i);
		return;
	}*/
}

Object * Warior::available_rivals(Object* e)
{
	return e->is_on_position(this->get_coords());
}

