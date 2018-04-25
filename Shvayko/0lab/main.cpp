#include <cstdlib>
#include <iostream>
#include "list.cpp"


using namespace std;



		
	int main()
	 {
		
		List<int> lst;
		cout<<"Введите размер списка  "<<endl;
		int size, enter;
		cin>>size;
		for(int i = 0;i<size;i++)
			{
			cout<<"Введите "<<i+1<<" число"<<endl;
			cin>>enter;
			lst.Add(enter);
			cout<<endl;
			}

		List <int> :: Iterator it;
		for(auto &Elem:lst)
			{
				Elem--;
			}
		
		it=lst.begin();
		cout<< *it<<endl;
		lst.Show();
	}

	
	
	
		
