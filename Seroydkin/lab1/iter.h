#pragma once

template <typename T> class List;

template <typename T>
class Iter
{
	friend class List<T>;
	Node<T> *cur;

public:
	Iter() : cur(NULL) {};
	Iter(Node<T>* tmp) : cur(tmp) {};

	Iter operator ++()
	{
		cur = cur->next;
		return *this;
	}

	Iter operator ++(int)
	{
		Iter old(cur);
		cur = cur->next;
		return old;
	}

	Iter operator --()
	{
		cur = cur->prev;
		return *this;
	}

	Iter operator --(int)
	{
		Iter old(cur);
		cur = cur->prev;
		return old;
	}
	
	Node<T> *operator ->()
	{
		return cur;
	}

	T &operator *()
	{
		return cur->elem;

	}

	bool operator != (Iter const &other)
	{
		return !(cur == other.cur);
	}

	bool operator == (Iter const &other)
	{
		return (cur == other.cur);
	}
};