#include "my_vector.hpp"

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

template <typename T>
class Iterator {
    friend class List<T>;
    Elem<T> *el;

public:
    Iterator(Elem<T> *e): el(e){};

    Iterator &operator++ (); //especial for prefix
    Iterator &operator-- ();
    void     operator++  (int);      //for postfix
    void     operator--  (int);
    Elem<T>  &operator*  ();
    Elem<T>  *operator-> ();
    bool     operator!=  (Iterator const& r);
    Iterator &operator=  (const Iterator  &r);
};

template <typename T>
Iterator<T> &Iterator<T>::operator= (const Iterator<T>  &r)
{
    //Если попытка сделать объект равным себе же, просто возвращаем указатель на него
    if(&r == this)
        return *this;
    return Iterator(this.info = r.info);
}

//------------------------------------------------------
template <typename T>
Iterator<T> &Iterator<T>::operator++ (){
    //std::cout << "op++" << std::endl;
    if(el)
        el = el->next;
    return *this;
}

template <typename T>
void Iterator<T>::operator++ (int){
    if(el)
        el = el->next;
}

template <typename T>
Iterator<T> &Iterator<T>::operator-- (){
    if(el)
        el = el->prev;
    return *this;
}

template <typename T>
void Iterator<T>::operator-- (int){
    if(el)
        el = el->prev;
}

template <typename T>
Elem<T> &Iterator<T>::operator* (){
    //std::cout << "op*" <<std::endl;
    return *el;
}

template <typename T>
Elem<T> *Iterator<T>::operator-> (){
    return el;
}

template <typename T>
bool Iterator<T>::operator!=(Iterator<T> const& r)
{
    //std::cout << "op!=" << std::endl;
    return !(el == r.el);
}

//------------------------------------------------------------------------------

#endif //ITERATOR_HPP
