#include "Swordsman.h"



Swordsman::Swordsman(ifstream& fin, const shared_ptr<Crown> t, char type) : Warior(fin, t, type)
{
	cout << "Swordsman : START:" << endl;
	cout << "Swordsman: END." << endl;
}

Swordsman::Swordsman(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type) : Warior(posit, hp, forc,t,type)
{
	cout << "Swordsman : START:" << endl;
	cout << "Swordsman: END." << endl;
}

Swordsman::Swordsman(const Swordsman & S): Warior(S)
{
	cout << "$Swordsman : START:" << endl;
	cout << "$Swordsman: END." << endl;
}

Swordsman::~Swordsman()
{
	cout << endl;
	cout << "~Swordsman : START:" << endl;
	cout << "~Swordsman: END." << endl;
}



void Swordsman::print(std::ostream & out)
{
	if (this->show_team() == 1) // 1
		out << "\033[32m";
	if (this->show_team() == 2) // 0
		out << "\033[31m";
	out << " S " << "\033[0m";
}

int Swordsman::attack(std::vector<Object*>* enemies)
{
	_2dim m_cords = get_coords();
	int min = 100000;
	Object* min_health_obj = NULL;
	int tmp = -1; // no result

	for (auto* e : *enemies) {
		if (auto temp = available_rivals(e)) {
			if (temp->show_health() <= min) {
				min_health_obj = temp;
				min = min_health_obj->show_health();
			}
			//tmp = temp->get_damage(this->give_force());
		}
	}

	if(min_health_obj != NULL) tmp = min_health_obj->get_damage(this->give_force());
	else return 0;


	del_by_id(tmp, enemies);
	if (enemies->empty())
		return show_team(); // this team won
	return 0; // all ok

	/*
	//dont delete and use for at the same time - use stack
	stack<int> deleted_ides;
	int tmp = -1; // no result

				  // Processing of attack without hitting
	for (Object* e : *enemies) {
		if (e->is_on_position(m_cords))
			tmp = e->get_damage(give_force());
		if (tmp != -1 && !e->last_representive()) {
			//del_by_id(e->get_id(), enemies);
			deleted_ides.push(e->get_id());
			tmp = -1;
		}
		else {
			if (e->last_representive()) return e->show_team();
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
	*/

	
	
	
}

Object * Swordsman::available_rivals(Object * e)
{
	_2dim m_cords = this->get_coords();

	for (int i = m_cords.x - 1; i <= m_cords.x + 1; i++) {
		for (int j = m_cords.y - 1; j <= m_cords.y + 1; j++) {
			if ((m_cords.x == i) && (m_cords.y == j)) continue;
			if (e->is_on_position({ i,j })) return e;
		}
	}

	return 0;


}
