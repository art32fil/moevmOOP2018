#pragma once

#include <iostream>
#include <cstdlib>
#include <assert.h> 

using namespace std;

template<typename T>
struct Node {
T data;
Node* prev;
Node* next;
};

template<typename T>
class List {
int size;
Node<T>* head;
Node<T>* tail;
public:

class Iterator{

public:
	friend List<T>;

	Node<T>* p;
	Iterator(Node<T> *p = NULL) : p(p) {};
	
	T& operator *()
	{
		return p->data;
	}
	
	
	Iterator& operator ++()
	{
		p = p->next;		
		return *this;		
	}


	Iterator operator --()
	{
		p = p->prev;     
		return *this;		
	}

	friend bool operator ==(const Iterator& x, const Iterator& y)
	{
		return x.p == y.p;
	}

	friend bool operator !=(const Iterator& x, const Iterator& y)
	{
		return x.p != y.p;
	}
	Node<T>* operator ->(){
	return p;
}
	/*Node<int>& operator+=(List<int>::Iterator & a, const List<int>::Iterator & b) {
		a.p->data += b.p->data;
		return a;
	}*/
};
Iterator begin() const
{
	return Iterator(head);
}

Iterator end() const
{
	return 	Iterator(NULL);
}
Iterator last()
{
	return Iterator(tail);
}

List();
~List();
void pushFront(List* list, T info);
void pushBack(List *list, T info);
void popFront(List *list);
void popBack(List *list);
void Insert(const Iterator& iter, const T& data);
void Delete(const Iterator& iter);
void show();
};

