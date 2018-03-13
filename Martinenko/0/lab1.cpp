//#include <iostream>
#include "list.cpp"
//using namespace std;

//template<typename T>
//class Iterator;


/*template<typename T>
class Iterator {
List<T>* data;
int i;
public:
T begin();
T end();
};*/

int main() {
	setlocale(LC_ALL, "Rus");
	List <int> lst;
	List <int> ::Iterator it;
	int size, enter,cmd;
	cout << "Enter size of the list: " << endl;
	cin >> size;
	
	for (int i = 0; i<size; i++)
	{
		cout << "Enter  " << i + 1 << " integer number: ";
		cin >> enter;
		lst.pushBack(&lst,enter);
		cout << endl;
	}
	it = lst.begin();
	
	cout << endl;
	cout << "Where do you want to insert to?" << endl;
	cout << "1.Begin" << endl;
	cout << "2.End" << endl;
	cout << "3.Certain place" << endl;
	cin >> cmd;
	
	switch (cmd) {
	case 1:
	{
		cout << "Enter integer number:" << endl;
		cin >> enter;
		lst.pushFront(&lst, enter);
		size++;
		break;
	}
	case 2: 
	{
		cout << "Enter integer number:" << endl;
		cin >> enter;
		lst.pushBack(&lst, enter);
		size++;
		break;
	}
	case 3: 
	{
		int c;
		cout << "Enter integer number:" << endl;
		cin >> enter;
		cout << "Enter number of position (from 1 to " << size << "):" << endl;
		cin >> c;
		for (int i = 1; i < c;i++)++it;
		lst.Insert(it, enter);
		size++;
		break;
	}
	default:
	{
		cout << "Incorrect input" << endl;
		break;
	}
	}
	
	lst.show();
	cout << endl;
	cout << "Where do you want to delete from?" << endl;
	cout << "1.Begin" << endl;
	cout << "2.End" << endl;
	cout << "3.Certain place" << endl;
	cout << "Your choice: " << endl;
	cin >> cmd;
	
	switch (cmd) {
	case 1: 
	{
		lst.popFront(&lst);
		size--;
		break;
	}
	case 2: 
	{
		lst.popBack(&lst);
		size--;
		break;	
	}
	case 3: 
	{
		int c;
		cout << "Enter number of position (from 1 to " << size << "):" << endl;
		cin >> c;
		it = lst.begin();
		for (int i = 1; i < c; i++)++it;
		lst.Delete(it);
		size--;
		break;
	}
	default: 
	{
		cout << "Incorrect input" << endl;
		break;
	} 
	}
	cout << "-------------------------" << endl;

	lst.show();
	for (List <int> ::Iterator it2 = lst.begin(); it2 != lst.end(); ++it2) {
		int elem = *it2;

		elem = 3;
	}
	for (int elem : lst) {
		elem = 3;
	}
	lst.show();
 return 0;
}


