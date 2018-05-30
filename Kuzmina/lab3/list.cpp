#include <iostream>
#include <cstdlib>
#include "list.hpp"

using namespace std;

template <typename T>
List<T>::~List()
{
    while (head)
    {
        tail = head->Next;
        //delete head;
        head = nullptr;
        head = tail;
    }
};
template <typename T>
void List<T>::Add_end(T info)
{
    element<T> *temp = new element<T>;
    temp->Next = NULL;
    temp->info = info;
    
    if(head!=NULL)
    {
        temp->Prev = tail;
        tail->Next = temp;
        tail = temp;
    }
    else
    {
        temp->Prev = NULL;
        head = tail = temp;
    }
};
template <typename T>
element<T> *List<T>::get(int index){
    size_t count = 0;
    element<T> *temp = head;
    while ( temp && (count < index)) {
        temp = temp->Next;
        count++;
    }
    return temp;
}
template <typename T>
T List<T>::operator[](int index){
    element<T> *temp = get(index);
    return temp->info;
}

