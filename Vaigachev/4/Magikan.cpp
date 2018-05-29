#include "Magikan.h"
#include <stack>



Magikan::Magikan(ifstream& fin, const shared_ptr<Crown> t, char type) : Warior(fin, t, type)
{
	fin >> range;
	cout << "Magikan : START:" << endl;
	cout << "	range  = " << range << endl;
	cout << "Magikan: END." << endl;
}

Magikan::Magikan(_2dim posit, int hp, int forc, const shared_ptr<Crown> t, char type,int range) : Warior(posit, hp, forc, t, type), range(range)
{
	cout << "Magikan : START:" << endl;
	cout << "	range  = " << range << endl;
	cout << "Magikan: END." << endl;
}

Magikan::Magikan(const Magikan & M):Warior(M),range(M.range)
{
	cout << "$Magikan : START:" << endl;
	cout << "	range  = " << range << endl;
	cout << "$Magikan: END." << endl;
}

Magikan::~Magikan()
{
	cout << endl;
	cout << "~Magikan : START:" << endl;
	cout << "	range  = " << range << endl;
	cout << "~Magikan: END." << endl;
}

void Magikan::print(std::ostream & out)
{
	if (this->show_team() == 1) // 1
		out << "\033[32m";
	if (this->show_team() == 2) // 0
		out << "\033[31m";
	out << " M " << "\033[0m";
}

int Magikan::attack(std::vector<Object*>* enemies)
{
	
	if (!info_directions.empty()) info_directions.clear();

	/*using map <int , vector <int> > -key contains directions:     (clock/&@)
	1 -'north'
	2 -'north-east'
	3 -'e'
	4 -'se'
	5 -'s'
	6 -'sw'
	7 -'w'
	8 -'nw'

	- value contans ids of object that belongs to 1-8 direction
	*/

	int min = 100000;
	int min_dir = 10;
	Object* min_health_obj = NULL;
	int tmp = -1; // no result

	for (auto e : *enemies) {
		if (auto temp = available_rivals(e)) {
			if (temp->show_health() <= min) {
				min_health_obj = temp;
				min = min_health_obj->show_health();
				min_dir = last_dir;
			}
		}
	}

	stack<int> deleted_ides;

	if (min_dir != 10) {
		for (auto e: info_directions[min_dir]) {
			if (tmp = e->get_damage(this->give_force())) {
				deleted_ides.push(tmp);
				tmp = -1;
			};
		}
	}
	else return 0;


	int i = -1;
	while (!deleted_ides.empty()) {
		i = deleted_ides.top();

		del_by_id(i, enemies);
		if (enemies->empty())
			return show_team(); // this team won
		deleted_ides.pop();
	}


	/*
	del_by_id(tmp, enemies);
	if (enemies->empty())
		return show_team(); // this team won
	return 0; // all ok
	*/


	/*
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

	if (min_health_obj != NULL) tmp = min_health_obj->get_damage(this->give_force());
	else return 0;

	
	del_by_id(tmp, enemies);
	if (enemies->empty())
		return show_team(); // this team won*/
	return 0; // all ok

}

Object * Magikan::available_rivals(Object * e)
{
	_2dim c = this->get_coords();

	for (int i = 1; i <= range; i++) {
		if (auto tmp = e->is_on_position({ c.x + 0,c.y - i })) { last_dir = 1; info_directions[1].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x + i,c.y - i })) { last_dir = 2; info_directions[2].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x + i,c.y + 0 })) { last_dir = 3; info_directions[3].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x + i,c.y + i })) { last_dir = 4; info_directions[4].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x + 0,c.y + i })) { last_dir = 5; info_directions[5].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x - i,c.y + i })) { last_dir = 6; info_directions[6].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x - i,c.y + 0 })) { last_dir = 7; info_directions[7].push_back(tmp); return tmp; }
		if (auto tmp = e->is_on_position({ c.x - i,c.y - i })) { last_dir = 8; info_directions[8].push_back(tmp); return tmp; }
	}

	/*
	for (int i = m_cords.x - range; i <= m_cords.x + 1; i++) {
		for (int j = m_cords.y - range; j <= m_cords.y + 1; j++) {
			if (e->is_on_position({ i,j })) {
				switch (switch_on)
				{
				default:
					break;
				}
			
			
			}return e;
			if (((m_cords.x == i) && (m_cords.y == j))) continue;
			
		}
	}
	
	*/




	/*
	_2dim m_cords = this->get_coords();

	for (int i = m_cords.x - range; i <= m_cords.x + 1; i++) {
		for (int j = m_cords.y - range; j <= m_cords.y + 1; j++) {
			if (((m_cords.x == i) && (m_cords.y == j))) continue;
			if (e->is_on_position({ i,j })) return e;
		}
	}*/
	return 0;
}