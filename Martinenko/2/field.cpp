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
	for (int i = 0; i < size_A; i++){ armyA.pushBack(f,color);}
}
void Field::getB(ifstream&f, const shared_ptr<Crown>& color) {
	f >> size_B;
	for (int i = 0; i < size_B; i++){ armyB.pushBack(f, color);}
	}

void Field::paint(){
	bool tag;
cout<<"  ";
for(int i = 0;i <x_size;i++)cout<< i;
cout << endl << "  +";
for (int i =0;i<x_size-2;i++)cout << "-";
cout <<"+"<<endl;
for (int i = 0;i<y_size;i++){
	cout<<"\033[0m";
	cout << i << "|";
	for (int j = 0;j<x_size;j++){
		tag = 1;

	for (auto& it: armyA){
	if (it.isObject(j,i)){ 
		cout<<"\033[0;31m";
		tag = 0;	
		if(it.isDead()){cout<<"\033[0m"; cout  <<".";}
		else cout << "o";
		break;	
			}
		}

	for (auto& it: armyB){
	if(it.isObject(j,i)){
		cout <<"\033[1;32m";
		if (it.isDead()){cout<<"\033[0m"; cout <<".";}
		else cout << "o";
		tag = 0;
		break;
	}
	}
	if (tag) { 
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

bool Field::isIt(int x1,int y1) {
	bool tag = 0;
	for (auto& it: armyA) {
		if (it.isObject(x1, y1)) { cout << "Selected target is red" << endl; tag = 1; }
	}
	for (auto& it : armyB) {
		if (it.isObject(x1, y1)) { cout << "Selected target is green" << endl; tag = 1; }
	}
	if (!tag) cout << "There isn't  object here!" << endl;
	return tag;
}

void Field::attack(int x,int y,int dmg) {

		bool tag = 0;		
		for (auto& it: armyA){
			if (it.isObject(x, y)) { 
				it.damage(dmg);
				paint();
				if(it.isDead()) armyA.Delete(it);
				tag = 1;
				break;
			}
		}
		if(!tag){
		for (auto& it: armyB){
			if (it.isObject(x, y)) { 
				it.damage(dmg);
				paint();
				if(it.isDead()) armyB.Delete(it);
				break;
				}
			}
		}
}

istream& operator >>(istream& s, Field& fld){
 s >> fld.x_size >>fld.y_size;
 return s;
}

ostream& operator <<(ostream& s, const Field& fld){
 s << fld.x_size << fld.y_size;
 return s;
}

