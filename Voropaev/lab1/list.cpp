#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;

template <typename T>
List<T>::~List()
	{
		while (Head)
		{
			Tail = Head->Next;
			delete Head;
			Head = Tail;
		}
	};

template <typename T>
void List<T>::Show()
	{
		Elem<T> *temp = Head;
		while(temp!=NULL)
		{
			cout<<temp->info<<" ";
			temp = temp->Next;
		}
		cout<<"\n";
	};
template <typename T>
void List<T>::Add(T info)
	{
		Elem<T> *temp = new Elem<T>;
		temp->Next = NULL;
		temp->info = info;
		
		if(Head!=NULL)
		{
			temp->Prev = Tail;
			Tail->Next = temp;
			Tail = temp;
		}
		else
		{
			temp->Prev = NULL;
			Head = Tail = temp;
		}
	};
template <typename T>
Elem<T> List<T>::operator[](int num)
   	{
       		Elem<T> *current = Head;
 
       		for(int i = 0 ; i <= num; i++)
       		{
           		if(i != num)
                		current = current->Next;
       		}
		return *current;
   	};

