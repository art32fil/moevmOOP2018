#include <iostream>
#include <cstdlib>
#include "list.cpp"

using namespace std;



int main()
{
	List <int> lst;
	cout << "Введите размер списка " << endl;
	int size, enter;
	cin >> size;
	for(int i=0;i<size;i++)
	{
		cout << "Введите  "<<i+1<<" число: ";
		cin >> enter;
		lst.Add(enter);
		cout <<endl;
	}
	List <int> :: Iterator it;
	for(it=lst.begin();it!=lst.end();it++)
	{
		(*it)++;
	}
	
	//for(auto &Elem: lst)               
		//{
		//	Elem++;	
		//}
	//it = lst.begin();
	//for(int i = 0;i<size;i++)
	//{
	//	cout << *it<<endl;
	//	it++;
	//}
	
	
	lst.Show();
	cout << lst[2].info<<endl;
	cout << lst[4].info<<endl;
}

