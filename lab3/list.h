#pragma once

#include <iostream>

using namespace std;

template <typename T> class Iter;

template <typename T>
struct Node
{
	T elem;
	Node *next,
		*prev;
};

template <typename T>
class List
{
	friend class Iter<T>;
public:
	Node<T> *head, *tail;

	List() : head(NULL), tail(NULL) {}
	~List();

	void addB(T);
	void addE(T);
	void insert(T, int);

	void delB();
	void delE();
	void erase(int);

	bool empty();
	void show();
	int size();

	T operator [] (int);

	Iter<T> begin()
	{
		return Iter<T>(head);
	}

	Iter<T> end()
	{
		return Iter<T>(NULL);
	}
};

template <typename T>
List<T>::~List()
{
	while (!empty())
	{
		tail = head->next;
		delete(head);
		head = tail;;
	}
}

template <typename T>
void List<T>::addB(T val)
{
	Node<T> *tmp = new Node<T>;
	tmp->prev = NULL;
	tmp->elem = val;
	tmp->next = head;
	if (!empty())
		head->prev = tmp;
	else
		tail = tmp;
	head = tmp;
}

template <typename T>
void List<T>::addE(T val)
{
	Node<T> *tmp = new Node<T>;
	tmp->elem = val;
	tmp->next = NULL;
	if (empty())
	{
		tmp->prev = NULL;
		head = tail = tmp;
	}
	else
	{
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
}

template <typename T>
void List<T>::insert(T val, int ind)
{
	if (ind == 0 || empty())
		addB(val);
	else if (ind >= size())
		addE(val);
	else
	{
		Node<T> *tmp = new Node<T>;
		tmp->elem = val;
		Node<T> *pos = head;
		for (int i = 0; i < ind; i++)
			pos = pos->next;
		tmp->prev = pos->prev;
		tmp->next = pos;
		pos->prev->next = tmp;
		pos->prev = tmp;
	}
}

template <typename T>
void List<T>::delB()
{
	if (!empty())
	{
		if (head == tail)
		{
			delete(head);
			head = tail = NULL;
		}
		else
		{
			Node<T> *tmp = head->next;
			tmp->prev = NULL;
			delete(head);
			head = tmp;
		}
	}
}

template <typename T>
void List<T>::delE()
{
	if (!empty())
	{
		if (tail == head)
		{
			delete(tail);
			tail = head = NULL;
		}
		else
		{
			Node<T> *tmp = tail->prev;
			tmp->next = NULL;
			delete(tail);
			tail = tmp;
		}
	}
}

template <typename T>
void List<T>::erase(int ind)
{
	if (ind == 0 || empty())
		delB();
	else if (ind >= size() - 1)
		delE();
	else
	{
		Node<T> *pos = head;
		for (int i = 0; i < ind; i++)
			pos = pos->next;
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete(pos);
	}
}

template <typename T>
bool List<T>::empty()
{
	if (head == NULL)
	{
		return true;
	}
	else
		return false;
}

template <typename T>
void List<T>::show()
{
	if (!empty())
	{
		Node<T> *tmp = head;
		cout << "Your data: [ ";
		while (tmp)
		{
			cout << tmp->elem << " ";
			tmp = tmp->next;
		}
		cout << "]" << endl << endl;
	}
}

template <typename T>
int List<T>::size()
{
	int count = 0;
	Node<T> *tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return count;
}

template <typename T>
T List<T>::operator[](int ind)
{
	Node<T> *tmp = head;
	for (int i = 0; i < ind; i++)
		tmp = tmp->next;
	return tmp->elem;
}