#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;



template <typename T>
void List<T>::Print() // печать списка
{
    element<T> *temp = head;
    while(temp != NULL)
    {
        cout << temp->info<<" ";
        temp = temp->next;
    }
    cout << endl;
};

template <typename T>
void List<T>::Supl_Begin(T info) // добавление в начало
{
    element<T> *temp = new element<T>;
    temp->prev = NULL;
    temp->info = info;
    temp->next = head;
    head->prev = temp;
    head = temp;
};

template <typename T>
void List<T>::Supl_Pos(T info,int pos) // добавление по позиции
{
    element<T> *temp = new element<T>;
    temp->info = info;
    element<T> *n = head;
    for(int i = 1; i < pos; i++){
        n = n->next;
    }
    temp->prev = n->prev;
    n->prev = temp;
    temp->next = n;
    n = head;
    for(int i = 2; i < pos; i++){
        n = n->next;
    }
    n->next = temp;
};

template <typename T>
void List<T>::Erase_Begin(){ // удаление первого
    element<T> *temp = head->next;
    temp->prev = NULL;
    delete (head);
    head = temp;
}

template <typename T>
void List<T>::Erase_End(){ // удаление последнего
    element<T> *temp = tail->prev;
    temp->next = NULL;
    delete (tail);
    tail = temp;
}

template <typename T>
void List<T>::Erase_Pos(int pos){ // удаление по позиции
    element<T> *temp = head;
    element<T> *n = head->next->next;
    for(int i = 2; i < pos; i++){
        temp = temp->next;
        n = n->next;
    }
    delete(temp->next);
    temp->next = n;
    n->prev = temp;
}

template <typename T>
element<T> *List<T>::get(int index){ // элемент по номеру
    size_t count = 0;
    element<T> *temp = head;
    while (temp && count < index - 1) {
        temp = temp->next;
        count++;
    }
    return temp;
}

template <typename T>
T List<T>::operator[](int index){ // оператор []
    element<T> *temp = get(index);
    return temp->info;
}

