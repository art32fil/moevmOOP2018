#pragma once
#ifndef list_hpp
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
        Iterator operator ++()
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
    void Add_end(T info);
    element<T> *get(int index);
    T operator[] (int index);
};
#endif

