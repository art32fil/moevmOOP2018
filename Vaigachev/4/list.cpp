
//#include <cstlib>
#include "list.h"

template <typename T>
Node<T>::Node(const Node & another) 
{
	info = another.info;
	Next = another.Next;
	Prev = another.Prev;

};

template <typename T>
Node<T>::~Node() {
	delete info;
}

template <typename T>
List<T>::~List() {
	if ((Head->Next == NULL) && (Head->Prev == NULL)) {
		delete Head->info;
		return;
	}
	if (Head->Prev == NULL) {
		Node<T> *temp = Head;
		while ((temp->Next != Tail) && (temp->Next != NULL)) {
			temp = temp->Next;
			delete Head->info;
			Head = temp;
		}
		delete Head->info;
		delete Tail->info;

	}
}

template <typename T>
void List<T>::AddStart(T info){
    Node<T>*temp = new Node<T>;
    if(Head == NULL){
        temp->info = info;
        temp->Next = Tail;
        temp->Prev = NULL;
        Head = temp;
        Tail = Head;
        return;
    }
    temp->info = info;
    temp->Next = Head;
    temp->Prev = NULL;
    Head->Prev = temp;
    Head = temp;
}

template <typename T>
void List<T>::AddEnd(T info){
    Node<T> *temp = new Node<T>;
    temp->info = info;
    if(Tail == NULL){
        temp->Next = NULL;
        temp->Prev = Tail;
        Tail = temp;
        Head = Tail;
        return;
    }
    temp->Next = NULL;
    temp->Prev = Tail;
    Tail->Next = temp;
    Tail = temp;
}

template <typename T>
void List<T>::AddIndex(T info,int index){
    if(index == 0) {
        AddStart(info);
        return;
    };
    int size = 0;
    for(it = this->begin(); it != this->end(); it++) size++;
    size--;
    if(index >= size){
        AddEnd(info);
        return;
    }
    Node<T> *tmp1 = new Node<T>;
    Node<T> *tmp2 = new Node<T>;
    tmp2 = Head;
    size = 0;
    while(size != index){
        tmp2 = tmp2->Next;
        size++;
    }
    tmp1->info = info;
    tmp1->Next = tmp2->Next;
    tmp1->Next->Prev = tmp1;
    tmp1->Prev = tmp2;
    tmp1->Prev->Next = tmp1;
}

template <typename T>
void List<T>::DelStart(){
    if(Head == NULL){
        std::cerr << "Nothing to delete" << std::endl;
        exit(EXIT_FAILURE);
        return;
    }
	if (Head->Next == NULL) {
		delete Head->info;
		Head = NULL;
	}
    else {
        Head = Head->Next;
        Head->Prev->Next = NULL;
        delete Head->Prev->info ;
		Head->Prev = NULL;
    }
}

template <typename T>
void List<T>::DelEnd(){
    if(Tail == NULL){
        std::cerr << "Nothing to delete" << std::endl;
        exit(EXIT_FAILURE);
        return;
    }
	if (Tail->Prev == NULL) delete Tail;
    else {
        Tail = Tail->Prev;
        Tail->Next->Prev = NULL;
        delete Tail->Next->info;
		Tail->Next = NULL;
    }
}

template <typename T>
void List<T>::DelIndex(int index){
    if(index == 0) {
        DelStart();
        return;
    };
    int size = 0;
    for(it = this->begin(); it != this->end(); it++) size++;
    size--;
    if(index >= size){
        DelEnd();
        return;
    }
    Node<T> *tmp2 = new Node<T>;
    Node<T> *tr = new Node<T>;
    tmp2 = Head;
    size = 0;
    while(size - 1 != index){
        tmp2 = tmp2->Next;
        size++;
    }
    tr = tmp2->Prev;
    tmp2->Prev = tmp2->Prev->Prev;
    tmp2->Prev->Next= tmp2;
    delete tr;
    return;
}

template<typename T>
bool List<T>::Empty()
{
	if (Head == NULL) return true;
	else false;
}

template <typename T>
void List<T>:: Show(){
    Node<T>* temp=Tail;
    temp=Head;
    while(temp!=NULL){
        std::cout << temp->info << " ";
        temp=temp->Next;
    }
    std::cout<<"\n";
}


