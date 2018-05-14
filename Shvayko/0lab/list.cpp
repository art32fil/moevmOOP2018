#include <cstdlib>
#include <iostream>
#include "list.h"

using namespace std;


template <typename T>

List<T> :: ~List()
	{
		while (Head)
		{
			Tail = Head->Next;
			delete Head;
			Head = Tail;
		}
	};


template <typename T>		
	void List<T>::Show(){
		Elem<T> *temp = Head;
		while (temp!=NULL)
			{
			cout<<temp->value<<" ";
			temp=temp->Next;
			}
			cout<<"\n";
		            };
template <typename T>
	void List<T>::Add(T value){
		Elem<T> *temp = new Elem<T>;
		temp->Next = NULL;
		temp->value = value;
			if(Head!= NULL)
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
