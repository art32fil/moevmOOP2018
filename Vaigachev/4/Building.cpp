#include "Building.h"
/*
template<class T>
Building<T>::Building(ifstream& fin, const shared_ptr<Crown > t,char type): Object(fin,t,type)
{
	fin >> range.x >> range.y;
	cout << "Building : START:" << endl;
	cout << "	range.x = " << range.x << endl;
	cout << "	range.y = " << range.y << endl;
	cout << "	type	= " << type << endl;
	//set_exemplar(exem);
	cout << "Building : END." << endl << endl;
}

template<class T>
Building<T>::~Building()
{
	cout << "~Building : START:" << endl;
	cout << "	range.x = " << range.x << endl;
	cout << "	range.y = " << range.y << endl;
	delete exemplar;
	cout << "~Building : END." << endl << endl;
}

template<class T>
Object* Building<T>::is_on_position(_2dim delt) {
	bool up, right; // sectors
*/
	/* up,right answers where (range) 
		 ^up
		 |
	<- (pos) -> right
		 |	
		 v	(range)
	
	*//**/ /*
	//difficult because of ().y (it goes down)
	up = pos.y >= range.y;
	right = pos.x <= range.x;

	//maybe bags me dunno
	if (up && right) {
		if ((pos.x <= delt.x) && (range.x >= delt.x) && (pos.y >= delt.y) && (range.y <= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (!up && right) {
		if ((pos.x <= delt.x) && (range.x >= delt.x) && (pos.y <= delt.y) && (range.y >= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (up && !right) {
		if ((pos.x >= delt.x) && (range.x <= delt.x) && (pos.y >= delt.y) && (range.y <= delt.y)) {
			return this;
		}
		else return NULL;
	}
	if (!up && !right) {
		if ((pos.x >= delt.x) && (range.x <= delt.x) && (pos.y <= delt.y) && (range.y >= delt.y)) {
			return this;
		}
		else return NULL;
	}
	//complete withoout bugs
}

template<class T>
void Building<T>::set_exemplar(T exem)
{
	exemplar = exem;
}

template<class T>
T Building<T>::spawning()
{
	T copy = T(example);
	return copy;
}
*/
/*
ostream &operator<<(ostream &out, Building &ob) {
	if (ob.show_team() == 1) // 1
		out << "\033[32m";
	if (ob.show_team() == 2) // 0
		out << "\033[31m";
	out << "B" << "\033[0m";
	return out;

}
*/ /*
template<class T>
void Building<T>::print(ostream &out) {
	if (this->show_team() == 1) // 1
		out << "\033[32m";
	if (this->show_team() == 2) // 0
		out << "\033[31m";
	out << " B " << "\033[0m";
}


template<class T>
void Building<T>::show_stats()
{
	cout << " type: = " << type << "; id = " << get_id() << "; team = " << show_team() << "; health = " << show_health();;
}
*/