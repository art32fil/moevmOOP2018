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
void List<T>::Show()
{
    element<T> *temp = head;
    while(temp!=NULL)
    {
        cout<<temp->info<<" ";
        temp = temp->Next;
    }
    cout<<endl;
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
void List<T>::Add_begin(T info)
{
    element<T> *temp = new element<T>;
    temp->Prev = NULL;
    temp->info = info;
    temp->Next = head;
    head->Prev = temp;
    head = temp;
};
template <typename T>
void List<T>::Add_pos(T info,int pos)
{
    element<T> *temp = new element<T>;
    temp->info = info;
    element<T> *k = head;
    for(int i = 1; i< pos; i++){
        k = k->Next;
    }
    temp->Prev = k->Prev;
    k->Prev = temp;
    temp->Next = k;
    k = head;
    for(int i = 2; i< pos; i++){
        k = k->Next;
    }
    k->Next = temp;
};
template <typename T>
void List<T>::Del_begin(){
    element<T> *temp = head->Next;
    temp->Prev = NULL;
    delete (head);
    head = temp;
}
template <typename T>
void List<T>::Del_end(){
    element<T> *temp = tail->Prev;
    temp->Next = NULL;
    delete (tail);
    tail = temp;
}
template <typename T>
void List<T>::Del_pos(int pos){
    element<T> *temp = head;
    element<T> *k = head->Next->Next;
    for(int i = 2; i<pos; i++){
        temp = temp->Next;
        k=k->Next;
    }
    delete(temp->Next);
    temp->Next = k;
    k->Prev = temp;
}
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


