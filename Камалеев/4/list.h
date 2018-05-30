#pragma once
#include <iostream>
#include <cstdlib>
#include <assert.h> 
#include <fstream>
#include "crown.h"

template <typename T>
class element // ����� �������
{
public:
	element* next;
	element* prev;
	T info;
	element(const T info) : info(info), prev(NULL), next(NULL) {}
	~element() {
		delete info;
	}
};

template <typename T>
class List // ����� ������
{
	int size;
	element<T>* head;
	element<T>* tail;
public:
	class Iterator // ����� ��������
	{
	public:
		friend List<T>;
		element<T> *ptr;
		Iterator(element<T> *ptr = NULL) : ptr(ptr) {}; // ����������� ���������

		T& operator *() // �������� *
		{
			return ptr->info;
		};

		element<T>* operator ->() // �������� ->
		{
			return ptr;
		};

		Iterator operator ++(int)
		{
			Iterator t(*this);
			ptr = ptr->next;	
			return t;			
		}

		Iterator& operator ++() // �������� ++()
		{
			ptr = ptr->next;
			return *this;
		};

		Iterator& operator --() // �������� --()
		{
			ptr = ptr->prev;
			return *this;
		};

		friend bool operator !=(const Iterator& x, const Iterator& y) // �������� !=
		{
			return x.ptr != y.ptr;
		};

		friend bool operator ==(const Iterator& x, const Iterator& y) // �������� ==
		{
			return x.ptr == y.ptr;
		};

	};
	Iterator begin() const // �������� begin
	{
		return Iterator(head);
	}
	Iterator last()
	{
		return Iterator(tail);
	}
	Iterator end() const // �������� end
	{
		return Iterator(NULL);
	}
	List() {
		head = tail = NULL;
	}

	~List() // ���������� ������
	{
		while (head)
		{
			tail = head->next;
			delete head;
			head = tail;
		}
	};

	void Supl_End(T info) // ���������� � �����
	{
		element<T>*temp = new element<T>(info);
		if (temp == NULL) {
			exit(3);
		}
		temp->next = NULL;

		if (head != NULL)
		{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		else
		{
			temp->prev = NULL;
			head = tail = temp;
		}
	};

	void Delete(const T& info)
	{
		element<T> *t;
		Iterator it = begin();
		for (; it != end(); ++it)
			if (it.ptr->info == info) break;
		assert(it != end());
		t = it.ptr;
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
	void Print();
	void Supl_Begin(T info);
	void Supl_Pos(T info, int pos);
	void Erase_End();
	void Erase_Begin();
	void Erase_Pos(int pos);
	void Insert(const Iterator& iter, const T& info);
	element<T> *get(int index);
	T operator[] (int index);
};

template <typename T>
void List<T>::Print() // ������ ������
{
	element<T> *temp = head;
	while (temp != NULL)
	{
		cout << temp->info << " ";
		temp = temp->next;
	}
	cout << endl;
};
