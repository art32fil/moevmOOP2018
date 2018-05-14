#pragma once
template <typename T>
class element
{
public:
    T info;
    element *Next, *Prev;
};

template <typename T>
class List
{
public:
    element<T> *head, *tail;
    class Iterator
    {
        friend List<T>;
        element<T> *p;
        
    public:
        Iterator(element<T> *p = NULL): p(p){};
        T& operator *()
        {
            return p->info;
        };
        element<T>* operator ->()
        {
            return p;
        };
        Iterator operator ++(int)
        {
            p = p->Next;
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
    Iterator begin() const
    {
        return Iterator(head);
    }
    Iterator end() const
    {
        return Iterator(NULL);
    }
    List():head(NULL), tail(NULL){};//конструктор
    ~List();//деструктор
    void Show();
    void Add_end(T info);
    void Add_begin(T info);
    void Add_pos(T info, int pos);
    void Del_end();
    void Del_begin();
    void Del_pos(int pos);
    element<T> *get(int index);
    T operator[] (int index);
};

