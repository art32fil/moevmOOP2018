#pragma once
template <typename T>
class Elem
{
public:
	T info;
	Elem *Next, *Prev;

};

template <typename T>
class List
{
	

	
public:
	Elem<T> *Head, *Tail;
	class Iterator
	{
		friend List<T>;
		Elem<T> *p;

	public:
		Iterator(Elem<T> *p = NULL): p(p){};
		const T& operator *() const
		{
			return p->info;
		};

		T& operator *()
		{
			return p->info;
		};
		
		//оператор ->
		
		
		Iterator operator ++()
		{
			p = p->Next;
			return *this;
		};

		Iterator operator ++(int)
		{
			p = p->Next;
			return *this;
		};

		Iterator operator --()
		{
			p = p->prev;
			return *this;
		};

		Iterator operator --(int)
		{
			p = p->Prev;
			return *this;
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
	List():Head(NULL), Tail(NULL){};
	~List();	
	Iterator begin() const
	{
		return Iterator(Head);
	}

	Iterator end() const
	{
		return 	Iterator(NULL);
	}
	
 	
  	
	void Show();
	void Add(T info);
	Elem<T> operator[] (int num);

		
};

