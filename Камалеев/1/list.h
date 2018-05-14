#pragma once

template <typename T>
class element // класс элемент
{
public:
	element* next;
	element* prev;
    T info;
};

template <typename T>
class List // класс список
{
public:
    element<T> *head, *tail;
    class Iterator // класс итератор
    {
	public:    
		friend List<T>;
        element<T> *ptr;
        
    
        Iterator(element<T> *ptr = NULL): ptr(ptr){}; // конструктор итератора

        T& operator *() // оператор *
        {
            return ptr->info;
        };

        element<T>* operator ->() // оператор ->
        {
            return ptr;
        };
  
        Iterator& operator ++(int) // оператор ++(int)
        {
            ptr = ptr->next;
            return *this;
        };
   
        Iterator& operator --(int) // оператор --(int)
        {
            ptr = ptr->prev;
            return *this;
        };

        friend bool operator !=(const Iterator& x, const Iterator& y) // оператор !=
        {
            return x.ptr != y.ptr;
        };
        
        friend bool operator ==(const Iterator& x, const Iterator& y) // оператор ==
        {
            return x.ptr == y.ptr;
        };
        
    };
    Iterator begin() const // оператор begin
    {
        return Iterator(head);
    }
    Iterator end() const // оператор end
    {
        return Iterator(NULL); 
    }
    List():head(NULL), tail(NULL){};
    
	~List() // деструктор списка
	{
		while (head)
		{
			tail = head->next;
			delete head;
			head = tail;
		}
	};

	void Supl_End(List *list, T* info) // добавление в конец
	{
		element<T> *temp = new element<T>;
		temp->info = *info;
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

    void Print();
    void Supl_Begin(T info);
    void Supl_Pos(T info, int pos);
    void Erase_End();
    void Erase_Begin();
    void Erase_Pos(int pos);
    element<T> *get(int index);
    T operator[] (int index);
};

