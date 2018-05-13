#ifndef ITER
#define ITER
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
    bool operator!=(Iter const& equal);
    Iter &operator=(const Iter  &equal);
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
Iter<T> &Iter<T>::operator=(const Iter<T>  &equal)
{
    // if an attempt to make the element equal to itself was, so the pointer to it will return
    if(&equal == this)
        return *this;
    return Iter(this.get() = equal.get());
}

template <typename T>
bool Iter<T>::operator!=(Iter<T> const& equal)
{
    return !(elm == equal.elm);
}
//------------------------------------------------

#endif //ITER
