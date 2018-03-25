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
	getArmies(f);
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


void Field::getArmies(ifstream&f){
	f >> size_A;
	for (int i = 0; i < size_A; i++) {
		//Object obj(f);
		armyA.pushBack(&armyA,new Object(f));
	}
	 f >> size_B;
	for (int i = 0; i < size_B; i++) {
		//Object obj(f);
		armyB.pushBack(&armyB, new Object(f));
	}
}

void Field::paint(){
cout<<"  ";
for(int i = 0;i <y_size;i++)cout<< i;
cout << endl << "  +";
for (int i =0;i<y_size-2;i++)cout << "-";
cout <<"+"<<endl;
for (int i = 0;i<x_size;i++){
	cout<<"\033[0m";
	cout << i << "|";
	for (int j = 0;j<y_size;j++){
		auto it1 = armyA.begin();
		auto it2 = armyB.begin();
	for (;it1 !=armyA.end();++it1){
	if (it1.p->data.isObject(i,j)){ 
		cout<<"\033[0;31m";		
		if(it1.p->data.isDead())cout  <<"x";
		else cout << "o";
		break;	
			}
		}
	
	while(it2!=armyB.end()){
	if(it2.p->data.isObject(i,j)){
		cout <<"\033[1;32m";
		if (it2.p->data.isDead())cout <<"x";
		else cout << "o";
		break;
	}
	++it2;
	}
	if (it1 == armyA.end() && (it2 == armyB.end())) { 
		cout<<"\033[0m";
		cout << "."; 
	}

	if(j ==y_size - 1) cout <<endl;	
}
	
}
	cout<<"\033[0m";
	cout << "  +--------+"<<endl;

}

bool Field::isIt(int x1,int y1) {
	bool tag = 0;
	for (auto it = armyA.begin(); it != armyA.end(); ++it) {
		if (it.p->data.isObject(x1, y1)) { cout << "Selected target is red" << endl; tag = 1; }
	}
	for (auto it = armyB.begin(); it != armyB.end(); ++it) {
		if (it.p->data.isObject(x1, y1)) { cout << "Selected target is green" << endl; tag = 1; }
	}
	if (!tag) cout << "There isn't  object here!" << endl;
	return tag;
}

void Field::attack(int x,int y,int dmg) {

		auto it = armyA.begin();
		while (it != armyA.end()) {
			if (it.p->data.isObject(x, y)) { 
				it.p->data.damage(dmg);
				break;
			}
			++it;
		}
		it = armyB.begin();
		while (it != armyB.end()) {
			if (it.p->data.isObject(x, y)) { 
				it.p->data.damage(dmg);
				break;
			}
			++it;
		}
		paint();
}
