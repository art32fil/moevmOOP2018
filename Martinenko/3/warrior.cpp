#include "warrior.h"

Warrior::Warrior(ifstream& f,const shared_ptr<Crown>& clr): Object(f,clr) {
	f >> force;
	cout << "Warrior:"<<endl
         << "	force = " << force << endl
         << "Warrior."<<endl;
    }

Warrior::Warrior(int x, int y, int hp,int force, const shared_ptr<Crown> crown): Object(x,y,hp,crown), force(force) {
	cout << "Warrior:" << endl
		 << "	force = " << force << endl
		 << "Warrior." << endl;
}
Warrior::~Warrior() {
	cout << "~Warrior:" << endl
		 << "	force = " << force << endl
		 << "~Warrior." << endl;
}

void Warrior::move_up() {
	get_y()--;
}

void Warrior::move_down() {
	get_y()++;
}

void Warrior::move_right() {
	get_x()++;
}

void Warrior::move_left() {
	get_x()--;
}


int Warrior::isObject(int x1, int y1) {
	if (get_x() == x1 && get_y() == y1) return 2;
	return 0;
}

List<tuple<int, int, int>>* Warrior::attack()  {
	List<tuple<int, int, int>>* range = new List<tuple<int, int, int>>;
	range->pushBack(tuple<int, int, int>(get_x(), get_y(), force));
	return range;
}