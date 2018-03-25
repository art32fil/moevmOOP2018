#pragma once
#include <iostream>
#include <cstdlib>
#include <assert.h> 

using namespace std;

template<class T>
struct Node {
	T data;
	Node* prev;
	Node* next;
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
	T set(T info);
	void pushFront(List* list, T info);
	void pushBack(List *list, T* info) {
	Node<T>*tmp = new Node<T>;
	if (tmp == NULL) {
		exit(3);
	}
	tmp->data = *info;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}
	void popFront(List *list);
	void popBack(List *list);
	void Insert(const Iterator& iter, const T& data);
	void Delete(const Iterator& iter);
	void show();
	//T begin();
	//T end();
};
