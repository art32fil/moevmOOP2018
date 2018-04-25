#include <iostream>
#include "List.h"
#include "Iter.h"

using namespace std;

void menu()
{
	cout << "1) Work with list\n";
	cout << "2) Work with iterator\n";
	cout << "3) Reset all\n";
	cout << "4) Exit\n";
	cout << "Your choice: ";
}

void menu1()
{
	cout << "1) Add element at the beginning\n";
	cout << "2) Add element at the end\n";
	cout << "3) Insert element at position\n";
	cout << "4) Delete element from the beginning\n";
	cout << "5) Delete element from the end\n";
	cout << "6) Erase element at position\n";
	cout << "7) Show list\n";
	cout << "8) Return\n";
	cout << "Your choice: ";
}

void menu2()
{
	cout << "1) Make first element as current\n";
	cout << "2) Make last element as current\n";
	cout << "3) Next element\n";
	cout << "4) Previous element\n";
	cout << "5) Set current by index\n";
	cout << "6) Show current element\n";
	cout << "7) Return\n";
	cout << "Your choice: ";
}

void listfun(List <int> &cont)
{
	bool flag = true;
	int com, data;
	while (flag)
	{
		menu1();
		cin >> com;
		switch (com)
		{
		case 1:
			cout << "Enter data: ";
			cin >> data;
			cont.addB(data);
			break;
		case 2:
			cout << "Enter data: ";
			cin >> data;
			cont.addE(data);
			break;
		case 3:
			cout << "Enter data: ";
			cin >> data;
			cout << "Enter position: ";
			cin >> com;
			cont.insert(data, com);
			break;
		case 4:
			cont.delB();
			cout << "Element deleted\n";
			break;
		case 5:
			cont.delE();
			cout << "Element deleted\n";
			break;
		case 6:
			cout << "Enter position: ";
			cin >> com;
			cont.erase(com);
			cout << "Element deleted\n";
			break;
		case 7:
			cont.show();
			break;
		case 8:
			flag = false;
			break;
		default:
			cout << "\t[wrong command]\n";
			break;
		}
	}
}

void iterfun(List<int> &cont)
{
	Iter<int> it;
	bool flag = true;
	int com;
	if (!cont.empty())
	{
		while (flag)
		{
			menu2();
			cin >> com;
			switch (com)
			{
			case 1:
				it = cont.begin();
				cout << "First element: " << *it << endl;
				break;
			case 2:
				it = cont.last();
				cout << "Last element: " << *it << endl;
				break;
			case 3:
				cout << "Current element before:" << *it << endl;
				cout << "Current element after: " << *++it << endl;
				break;
			case 4:
				cout << "Current element before:" << *it << endl;
				cout << "Current element after: " << *--it << endl;
				break;
			case 5:
				cout << "Enter index: ";
				cin >> com;
				it = cont[com];
				cout << "Current element: " << *it << endl;
				break;
			case 6:
				cout << "Current element: " << *it << endl;
				break;
			case 7:
				flag = false;
				break;
			default:
				cout << "\t[wrong command]\n";
				break;
			}
		}
	}
	else
		cout << "List is empty\n";
}

int main()
{
	List<int> cont;
	cont.addB(322);
	cont.addB(13);
	cont.addB(666);
	cont.addB(11);
	bool flag = true;
	int com;
	while (flag)
	{
		menu();
		cin >> com;
		switch (com)
		{
		case 1:
			listfun(cont);
			break;
		case 2:
			iterfun(cont);
			break;
		case 3:
			cont.~List();
			break;
		case 4:
			flag = false;
			break;
		default:
			cout << "\t[wrong command]\n";
			break;
		}
	}
	cont.~List();
	getchar();
    return 0;
}
