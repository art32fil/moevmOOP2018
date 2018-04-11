#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <assert.h> 
#include <fstream>
#include "crown.h"

using namespace std;

template<class T>
struct Node {
	T data;
	Node* prev;
	Node* next;
	Node(const T* data) :data(*data),prev(nullptr), next(nullptr){}
};

template<class T>
class List {
	int size;
	Node<T>* head;
	Node<T>* tail;
public:

	class Iterator {

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


		Iterator& operator --()
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

		/*List<int>::Iterator& operator+=(Iterator & a, const Iterator & b) {
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

	List() {
	head = tail = NULL;
	}
	~List() {
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
}
	
	void pushBack(ifstream&f, const shared_ptr<Crown>& color) {
	T* obj = new T(f, color);
	Node<T>*tmp = new Node<T>(obj);
	obj->delete_crown();
	operator delete (obj);
	if (tmp == NULL) {
		exit(3);
	}
	//tmp->data = *info;
	tmp->next = NULL;
	tmp->prev = tail;
	if (tail) {
		tail->next = tmp;
	}
	tail = tmp;

	if (head == NULL) {
		head = tmp;
	}
	size++;
}
	void Delete(const T& data)
	{
	Node<T> *t;
	Iterator it= begin();
	for (; it != end(); ++it)
		if (it.p->data == data) break;
	assert(it != end());
	t = it.p;
	if (it == begin()) {
		head = t->next;
		if (!head) tail = NULL;
	}
	else
		if (it == last()) {
			tail = t->prev;
			t->prev->next = NULL;
			if (!tail) head = NULL;
		}
		else {
			t->prev->next = t->next;
			t->next->prev = t->prev;
		}
		delete t;
	}

	T set(T info);
	void pushFront(List* list, T info);
	void popFront(List *list);
	void popBack(List *list);
	void Insert(const Iterator& iter, const T& data);
	//T begin();
	//T end();
	//void show();
};



/*template <class T>
void List<T>::show()

{
	Node<T> *t = head;
	while (t != NULL)
	{
		cout << t->data << " ";
		t = t->next;
	}
	cout << endl;
}*/

#endif