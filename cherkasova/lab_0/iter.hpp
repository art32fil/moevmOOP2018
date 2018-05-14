#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>
#include "list.hpp"

using namespace std;

template <typename T> class Elem;
template <typename T> class List;

//-------------------Iterator-------------------------
template <typename T>
class Iter{    
    friend class List<T>; 
    friend class Elem<T>;               
    Elem<T> *elm; 

public:
    Iter(Elem<T> *ptr) : elm(ptr) {};
    
    Elem<T> &operator*();
    Elem<T> *operator->();
    Iter operator++(); 
    Iter operator--();
    bool operator!=(Iter const& r);
    Iter &operator=(const Iter  &r);
};
//------------------------------------------------


//-------------------IteratorMethods-------------------------
template <typename T>
Elem<T> &Iter<T>::operator*()  { return *elm; }

template <typename T>
Elem<T> *Iter<T>::operator->() { return elm; }

template <typename T>
Iter<T> Iter<T>::operator++()
{
    if(elm) elm = elm->next;
    return *this;
}

template <typename T>
Iter<T> Iter<T>::operator--()
{
    if(elm) elm = elm->prev;
    return *this;
}

template <typename T>
Iter<T> &Iter<T>::operator=(const Iter<T>  &r)
{
    // if an attempt to make the element equal to itself was, so the pointer to it will return
    if(&r == this)
        return *this;
    return Iter(this.get() = r.get());
}

template <typename T>
bool Iter<T>::operator!=(Iter<T> const& r)
{
    return !(elm == r.elm);
}

//------------------------------------------------

#endif //ITER_HPP