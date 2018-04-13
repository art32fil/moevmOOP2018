
#ifndef LIST_H
#define LIST_H

#include <iostream>
//using namespace std;

template <typename T> class List;
template <typename T> class Iterator;

template <typename T>
class Elem {
	friend class List<T>;
	friend class Iterator<T>;
private:
	T info;
	Elem<T>* next;
	Elem<T>* prev;

public:
	Elem(T &val) : info(val), next(NULL), prev(NULL) {}
	T& get_value() { return info; }
};

template <typename T>
class List {
	friend class Iterator<T>;
private:

	Elem<T>* head;
	Elem<T>* tail;

public:

	List() : head(NULL), tail(NULL) {}
	~List();

	bool is_null();
	int size();
	void show();

	Elem<T>* init(T &val);
	Elem<T>* get_elem(int num);
	Elem<T>* get_head() { return head; }
	Elem<T>* get_tail() { return tail; }

	void add_head(T &val);
	void add_tail(T &val);
	void add_num(T &val, int n);

	void delete_head();
	void delete_tail();
	void delete_num(int n);

	Iterator<T> begin();
	Iterator<T> end();

	T& operator[](int index);
	friend Elem<int> operator+(Elem<int> a, Elem<int> b);

};

template <typename T>
List<T>::~List()
{
	if(!is_null())
	{
		Elem<T>* tmp;
		while (head)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
}

template <typename T>
bool List<T>::is_null()
{
	if ((head == NULL)&&(tail == NULL)) return true;
	else return false;
}

template <typename T>
void List<T>::show()
{
	Elem<T>* cur = head;
	while (cur != NULL)
	{
		std::cout << cur->info << std::endl;
		cur = cur->next;
	}
}

template <typename T>
Elem<T>* List<T>::init(T &val)
{
	Elem<T>* tmp = new Elem<T>(val);
	return tmp;

}

template <typename T>
int List<T>::size()
{
	Elem<T>* tmp = head;
	int n = 0;
	while (tmp)
	{
		++n;
		tmp = tmp->next;
	}
	return n;
}

template <typename T>
Elem<T>* List<T>::get_elem(int num)
{
	int i = 0;
	Elem<T>* cur = head;
	while ((i != num) && (cur != NULL))
	{
		++i;
		cur = cur->next;
	}

	return cur;
}

template <typename T>
void List<T>::add_head(T &val)
{
	Elem<T>* tmp = init(val);

	if (is_null())
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tmp->next = head;
		head->prev = tmp;
		head = tmp;
	}
}

template <typename T>
void List<T>::add_tail(T &val)
{
	Elem<T>* tmp = init(val);

	if (is_null())
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
}

template <typename T>
void List<T>::add_num(T &val, int n)
{
	int num = size();
	if (is_null() || (n == 0))
	{
		add_head(val);
	}
	else if (n == (num - 1))
	{
		add_tail(val);
	}
	else if ((n > 0) && (n < (num - 1)))
	{
		Elem<T>* nxt = get_elem(n);
		Elem<T>* prv = nxt->prev;
		Elem<T>* tmp = init(val);
		tmp->next = nxt;
		nxt->prev = tmp;
		tmp->prev = prv;
		prv->next = tmp;
	}
}

template <typename T>
void List<T>::delete_head()
{
	if(!is_null())
	{
	Elem<T>* headcopy = head;
	Elem<T>* newhead = head->next;
	newhead->prev = NULL;
	head = newhead;
	delete headcopy;
	}
}


template <typename T>
void List<T>::delete_tail()
{
	if (!is_null())
	{
	Elem<T>* tailcopy = tail;
	Elem<T>* newtail = tail->prev;
	newtail->next = NULL;
	tail = newtail;
	delete tailcopy;
	}
}

template <typename T>
void List<T>::delete_num(int n)
{
	int size = this->size();
	if (!is_null())
	{
		if (n == 0) delete_head();
		else if (n == (size - 1)) delete_tail();
		else if ((n > 0) && (n < size))
		{
			Elem<T>* cur = get_elem(n);
			Elem<T>* prv = cur->prev;
			Elem<T>* nxt = cur->next;
			prv->next = nxt;
			nxt->prev = prv;
			delete cur;
		}
	}
}


template <typename T>
Iterator<T> List<T>::begin()
{
	Iterator<T> iter(head);
	return iter;
}

template <typename T>
Iterator<T> List<T>::end()
{
	Iterator<T> iter(NULL);
	return iter;
}

template <typename T>
T &List<T>::operator[](int index)
{
	Elem<T>* tmp = get_elem(index);
	return tmp->info;
}

//Elem<int> operator+(Elem<int> a, Elem<int> b)
//{
//	Elem<int> res(a.get_value() + b.get_value());
//	return res;
//}



#endif
