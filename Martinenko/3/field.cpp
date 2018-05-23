#include "field.h"


Field::Field(ifstream& f) {
	if (!f.is_open()) {
		cout << "File can't be opened!" << endl;
		exit(EXIT_FAILURE);
		system("pause");
	}
	f >> x_size >> y_size;
	cout << "Field:" << endl
	<< "	xSize = " << x_size << endl
	<< "	ySize = " << y_size << endl;
 	shared_ptr<Crown> A = shared_ptr<Crown>(new Crown(1));
	clrA = A;
	getA(f, A);
	shared_ptr<Crown> B = shared_ptr<Crown>(new Crown(0));
	clrB = B;
	getB(f, B);
	//A.reset();
	//B.reset();
	cout << "Field."<<endl;
}
Field::~Field(){
	cout<<"~Field."<<endl
	<< "	xSize = " << x_size << endl
	<< "	ySize = " << y_size << endl;
	armyA.~List();
	armyB.~List();
	cout <<"~Field."<<endl;

}

void Field::getA(ifstream&f, const shared_ptr<Crown>& color) {
	f >> size_A;
	char is;
	for (int i = 0; i < size_A; i++){ 
		f >> is;
		if (is == 'w') {	
			armyA.pushBack(new Warrior(f, color));
		}
		else if(is == 'b') {
			armyA.pushBack(new Building(f, color));
		}
		
	}
}
void Field::getB(ifstream&f, const shared_ptr<Crown>& color) {
	f >> size_B;
	char is;
	for (int i = 0; i < size_B; i++){ 
		f >> is;
		if (is == 'w') {
			armyB.pushBack(new Warrior(f,color));
		}
		else if (is == 'b') {
			armyB.pushBack(new Building(f, color));
		}
	}
}

void Field::paint(){
	bool empty,foundA;
	cout<<"  ";
	for(int i = 0;i <x_size;i++)cout<< i;
	cout << endl << "  +";
	for (int i =0;i<x_size-2;i++)cout << "-";
	cout <<"+"<<endl;
	for (int i = 0;i<y_size;i++){
		cout<<"\033[0m";
		cout << i << "|";
		for (int j = 0;j<x_size;j++){
			empty = 1;
			foundA = 0;
			for (auto& it: armyA){
				if (it->isObject(j,i) == 2){ 
					cout<<"\033[0;31m";
					empty = 0;	
					if(it->isDead()){
						cout<<"\033[0m";
						cout  <<".";}
					else cout << "w";
					foundA = 1;
					break;	
				}
				if (it->isObject(j, i) == 3) {
					cout<<"\033[0;31m";
					empty = 0;
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "b";
					foundA = 1;
					break;
				}
			}
			
			for (auto& it: armyB){
				if (foundA) break;
				if(it->isObject(j,i) == 2){
					cout <<"\033[1;32m";
					if (it->isDead()){
						cout<<"\033[0m";
						cout <<".";}
					else cout << "w";
					empty = 0;
					break;
				}
				if (it->isObject(j, i) == 3) {
					cout <<"\033[1;32m";
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "b";
					empty = 0;
					break;
				}
			}
			if (empty) { 
				cout<<"\033[0m";
				cout << "."; 
			}
			if(j ==y_size - 1) cout <<endl;	
		}
	}
	cout<<"\033[0m";
	cout << "  +";
	for (int i =0;i<x_size-2;i++)cout << "-";
	cout <<"+"<<endl;

}

bool Field::isIt(string clr,int x1,int y1) {
	bool tag = 0;
	if (clr == "red") {
		for (auto& it : armyA) {
			if (it->isObject(x1, y1) == 2) tag = 1;
		}
	}
	else if (clr == "green") {
		for (auto& it : armyB) {
			if (it->isObject(x1, y1) == 2) tag = 1;
		}
	}
	return tag;
}

void Field::move(string clr,int x, int y, string dir) {
	if (clr == "red") {
		for (auto it : armyA) {
			if (it->isObject(x, y)==2) { 
				if (dir == "up") {
					if (it->get_y() >= 1) it->move_up();
				}
				if (dir == "down") {
					if (it->get_y() <= y_size-2) it->move_down();
				}
				if (dir == "right") {
					if (it->get_x() <= x_size - 2) it->move_right();
				}
				if (dir == "left") {
					if (it->get_x() >= 1) it->move_left();
				}
				break;
			}
		}
	}
	else if(clr == "green"){
		for (auto it : armyB) {
			if (it->isObject(x, y)==2) {
				if (dir == "up") {
					if (it->get_y() >= 1) it->move_up();
				}
				if (dir == "down") {
					if (it->get_y() <= y_size - 2) it->move_down();
				}
				if (dir == "right") {
					if (it->get_x() <= x_size - 2) it->move_right();
				}
				if (dir == "left") {
					if (it->get_x() >= 1) it->move_left();
				}
				break;
			}
		}
	}
}

bool Field::attack(string clr, int x1, int y1,int x2,int y2) {
	bool tag = 0;
	if (clr == "red") {
		auto i = armyA.begin();
		while (i != armyA.end()) {
			if (i.p->data->isObject(x1, y1) == 2) break;
			++i;
		}
		List<tuple<int,int,int>>* range = i.p->data->attack();
		for (auto k : *range) {
			if (get<0>(k) == x2 && get<1>(k) == y2) {
				for (auto j: armyB) {
					if (j->isObject(x2, y2)) { 
						j->damage(get<2>(k));
						if (j->isDead()) armyB.Delete(j);
						else cout << "The green object got damage" << endl;
						tag = 1;
						break;
					}
					++j;
				}
			} 
		}
		
	}
	else if (clr == "green") {
		auto i = armyB.begin();
		while (i != armyB.end()) {
			if (i.p->data->isObject(x1, y1) == 2) break;
			++i;
		}
		List<tuple<int, int, int>>* range = i.p->data->attack();
		for (auto k : *range) {
			if (get<0>(k) == x2 && get<1>(k) == y2) {
				for (auto j : armyA) {
					if (j->isObject(x2, y2)) { 
						j->damage(get<2>(k));
						if (j->isDead()) armyA.Delete(j);
						else cout << "The red object got damage" << endl;
						tag = 1;
						break;
					}
					++j;
				}
			}
		}
	}
	return tag;
}
bool Field::isArmyA() {
	if (armyA.get_size() == 0) return true;
	else return false;
}

bool Field::isArmyB() {
	if (armyB.get_size() == 0) return true;
	else return false;
}
istream& operator >>(istream& s, Field& fld){
 s >> fld.x_size >>fld.y_size;
 return s;
}

ostream& operator <<(ostream& s, const Field& fld){
 s << fld.x_size << fld.y_size;
 return s;
}

