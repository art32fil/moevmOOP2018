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
		if (is == 's') {
			armyA.pushBack(new Swordsman(f, color));
		}
		else if(is == 'b') {
			char c;
			f >> c;
			if (c == 's')armyA.pushBack(new Building<Swordsman>(f, color));
			if (c == 'm')armyA.pushBack(new Building<Magician>(f, color));
		}
		else if (is == 'm') {
			armyA.pushBack(new Magician(f, color, x_size, y_size));
		}
		
	}
}
void Field::getB(ifstream&f, const shared_ptr<Crown>& color) {
	f >> size_B;
	char is;
	for (int i = 0; i < size_B; i++){ 
		f >> is;
		if (is == 's') {
			armyB.pushBack(new Swordsman(f, color));
		}
		else if (is == 'b') {
			char c;
			f >> c;
			if (c == 's')armyB.pushBack(new Building<Swordsman>(f, color));
			if (c == 'm')armyB.pushBack(new Building<Magician>(f, color));
		}
		else if (is == 'm') {
			armyB.pushBack(new Magician(f, color, x_size, y_size));
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
				if (it->isObject(j, i) == 4) {
					cout<<"\033[0;31m";
					empty = 0;
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "m";
					foundA = 1;
					break;
				}
				if (it->isObject(j, i) == 5) {
					cout<<"\033[0;31m";
					empty = 0;
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "s";
					foundA = 1;
					break;
				}
			}
			
			for (auto& it: armyB){
				if (foundA) break;
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
				if (it->isObject(j, i) == 4) {
					cout <<"\033[1;32m";
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "m";
					empty = 0;
					break;
				}
				if (it->isObject(j, i) == 5) {
					cout <<"\033[1;32m";
					if (it->isDead()) {
						cout<<"\033[0m";
						cout << ".";
					}
					else cout << "s";
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

bool Field::isIt(string clr, string kind, int x1, int y1) {
	bool tag = 0;
	if (clr == "red") {
		if (kind == "building") {
			for (auto& it : armyA) {
				if (it->isObject(x1, y1) == 3) tag = 1;
			}
		}
		if (kind == "magician") {
			for (auto& it : armyA) {
				if (it->isObject(x1, y1) == 4) tag = 1;
			}
		}
		if (kind == "swordsman") {
			for (auto& it : armyA) {
				if (it->isObject(x1, y1) == 5) tag = 1;
			}
		}
	}
	else if (clr == "green") {
		if (kind == "building") {
			for (auto& it : armyB) {
				if (it->isObject(x1, y1) == 3) tag = 1;
			}
		}
		if (kind == "magician") {
			for (auto& it : armyB) {
				if (it->isObject(x1, y1) == 4) tag = 1;
			}
		}
		if (kind == "swordsman") {
			for (auto& it : armyB) {
				if (it->isObject(x1, y1) == 5) tag = 1;
			}
		}
	}
	return tag;
}

void Field::move(string clr,int x, int y, string dir) {
	if (clr == "red") {
		for (auto it : armyA) {
			if (it->isObject(x, y) > 3) { 
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
			if (it->isObject(x, y) > 3) {
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

int Field::get_hp(string clr,int x,int y) {
	int min = -1;
	if (clr == "red") {
		for (auto &it : armyA) {
			if (it->isObject(x, y)) {
				if (min == -1) min = it->get_hp();
				if (it->get_hp() < min) min = it->get_hp();
			}
		}
	}
	else if (clr == "green") {
		for (auto &it : armyB) {
			if (it->isObject(x, y)) {
				if (min == -1) min = it->get_hp();
				if (it->get_hp() < min) min = it->get_hp();
			}
		}
	}
	return min;
}

tuple<int,int> Field::min_range(string clr, List<tuple<int, int, int>>* range) {
	tuple<int, int> min = make_tuple(-1, -1);
	if (clr == "red") {
		for (auto it : *range) {
			for (auto it1 : armyB) {
				if (!it1->isObject(get<0>(it), get<1>(it))) continue;
				else {
					if (get<0>(min) == -1 && get<1>(min) == -1) {
						if (it1->get_y() == get<0>(it) && it1->get_x() == get<1>(it)) min = make_tuple(it1->get_x(), it1->get_y());
						else  min = make_tuple(it1->get_x1(get<0>(it)), it1->get_y1(get<1>(it)));
					}
					if (it1->get_hp() < get_hp("green", get<0>(min), get<1>(min))) { 
						if (it1->get_y() == get<0>(it) && it1->get_x() == get<1>(it)) min = make_tuple(it1->get_x(), it1->get_y());
						else  min = make_tuple(it1->get_x1(get<0>(it)), it1->get_y1(get<1>(it)));
					}
				}
			}

		}
	}
	else if (clr == "green") {
		for (auto it : *range) {
			for (auto it1 : armyA) {
				if (!it1->isObject(get<0>(it), get<1>(it)))  continue;
				else {
					if (get<0>(min) == -1 && get<1>(min) == -1) { 
						if (it1->get_y() == get<0>(it) && it1->get_x() == get<1>(it)) min = make_tuple(it1->get_x(), it1->get_y());
						else  min = make_tuple(it1->get_x1(get<0>(it)), it1->get_y1(get<1>(it)));
					}
					if (it1->get_hp() < get_hp("red", get<0>(min), get<1>(min))) {						
						if (it1->get_y() == get<0>(it) && it1->get_x() == get<1>(it)) min = make_tuple(it1->get_x(), it1->get_y());
						else  min = make_tuple(it1->get_x1(get<0>(it)), it1->get_y1(get<1>(it))); }
				}
			}

		}
	}
	return min;
}

bool Field::attack(string clr,string kind, int x1, int y1) {
	bool tag = 0;
	if (clr == "red") {
		auto i = armyA.begin();
		if (kind == "magician") {
			while (i != armyA.end()) {
				if (i.p->data->isObject(x1, y1) == 4) break;
				++i;
			}
			List<tuple<int, int, int>>* range = i.p->data->attack();
			tuple<int, int> min = min_range(clr, range);
			List<tuple<int, int, int>>* min_range;
			if (x1 < get<0>(min) && y1 == get<1>(min)) {
				min_range = i.p->data->right_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else it2++;
						}
						else { tag = 1; cout << "The green object got damage" << endl; it2++; }
					}
				}
			}

			if (x1 > get<0>(min) && y1 == get<1>(min)) {
				min_range = i.p->data->left_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->up_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->down_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}


			if (x1 < get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->ru_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

			if (x1 < get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->rd_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 > get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->lu_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 > get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->ld_range();
				for (auto it1 : *min_range) {
					auto it2 = armyB.begin();
					while (it2 != armyB.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyB.last()) {
									armyB.Delete(it2.p->data);
									it2 = armyB.end();
									tag = 1;
								}
								else {
									it2++;
									armyB.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The green object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

		}
		else if (kind == "swordsman") {
			while (i != armyA.end()) {
				if (i.p->data->isObject(x1, y1) == 5) break;
				++i;
			}
		
		List<tuple<int,int,int>>* range = i.p->data->attack();
		tuple<int, int> min = min_range(clr, range);
				for (auto j: armyB) {
					if (j->isObject(get<0>(min),get<1>(min))) {
						j->damage(get<2>(*(range->begin())));
						if (j->isDead()) armyB.Delete(j);
						else cout << "The green object got damage" << endl;
						tag = 1;
						break;
					}
					++j;
				}	
		}
	}
	else if (clr == "green") {
		auto i = armyB.begin();
		if (kind == "magician") {
			while (i != armyB.end()) {
				if (i.p->data->isObject(x1, y1) == 4) break;
				++i;
			}
			List<tuple<int, int, int>>* range = i.p->data->attack();
			tuple<int, int> min = min_range(clr, range);
			List<tuple<int, int, int>>* min_range;
			if (x1 < get<0>(min) && y1 == get<1>(min)) {
				min_range = i.p->data->right_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

			if (x1 > get<0>(min) && y1 == get<1>(min)) {
				min_range = i.p->data->left_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->up_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 == get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->down_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}


			if (x1 < get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->ru_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

			if (x1 < get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->rd_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 > get<0>(min) && y1 > get<1>(min)) {
				min_range = i.p->data->lu_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}
			if (x1 > get<0>(min) && y1 < get<1>(min)) {
				min_range = i.p->data->ld_range();
				for (auto it1 : *min_range) {
					auto it2 = armyA.begin();
					while (it2 != armyA.end()) {
						if (it2.p->data->isObject(get<0>(it1), get<1>(it1))) {
							it2.p->data->damage(get<2>(it1));
							if (it2.p->data->isDead()) {
								if (it2 == armyA.last()) {
									armyA.Delete(it2.p->data);
									it2 = armyA.end();
									tag = 1;
								}
								else {
									it2++;
									armyA.Delete(it2.p->prev->data);
									tag = 1;
								}
							}
							else { tag = 1; cout << "The red object got damage" << endl; it2++; }
						}
						else it2++;
					}
				}
			}

		}
		else if (kind == "swordsman") {
			while (i != armyB.end()) {
				if (i.p->data->isObject(x1, y1) == 5) break;
				++i;
			}		
			List<tuple<int, int, int>>* range = i.p->data->attack();
			tuple<int, int> min = min_range(clr, range);
			for (auto j : armyA) {
				if (j->isObject(get<0>(min), get<1>(min))) {
					j->damage(get<2>(*(range->begin())));
					if (j->isDead()) armyA.Delete(j);
					else cout << "The red object got damage" << endl;
					tag = 1;
					break;
				}
				++j;
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

