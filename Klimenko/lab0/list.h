#pragma once
template <typename T>

class Elem
{
public:
	T value;
	Elem *Next,*Prev;
};

template <typename T>
class List
{	
	public:
	Elem<T> *Head,*Tail;
	
	class Iterator
	{
		friend List<T>;
		Elem<T> *p;

		public:

		Iterator(Elem<T> *p = NULL): p(p){};
		const T& operator *() const
		{
			return p->value;
		};

		T& operator *()
		{
			return p->value;
		};

		//скобки


		Iterator& operator ++()
		{
			p = p->Next;
			return *this;
		};

		Iterator& operator ++(int)
		{
			Iterator t(*this);
			p = p->Next;
			return t;
		};

		
		Iterator& operator --()
		{
			p = p->Prev;
			return *this;
		};

		Iterator& operator --(int)
		{
			Iterator t(*this);
			p = p->Prev;
			return t;
		};

		friend bool operator !=(const Iterator& x, const Iterator& y)
		{
			return x.p != y.p;
		};

		friend bool operator ==(const Iterator& x, const Iterator& y)
		{
			return x.p == y.p;
		};
		};

	
	List():Head(NULL),Tail(NULL){};
	~List();

	Iterator begin() const
	{
		return Iterator(Head);
	}
	
	Iterator end() const
	{
		
		return NULL;
	}
	
	void Show();
	void Add(T value);
};
