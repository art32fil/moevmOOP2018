#include "list.h"


/*template<class T>
List<T>::List() {
	head = tail = NULL;
}*/

template<class T>
T List<T>::set(T info) {
	Node<T>* node = new Node<T>;
	node->next = NULL;
	node->data = info;

	return node->data;
}

template<class T>
void List<T>::pushFront(List* list, T info) {
	Node<T> *tmp = new Node<T>;
	if (tmp == NULL) {
		exit(1);
	}
	tmp->data = info;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->size++;
}

/*template<class T>
void List<T>::pushBack(List *list, T info) {
	Node<T>*tmp = new Node<T>;
	if (tmp == NULL) {
		exit(3);
	}
	tmp->data = info;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}*/

template<class T>
void List<T>::popFront(List *list) {
	Node<T> *prev;
	if (list->head == NULL) {
		exit(2);
	}

	prev = list->head;
	list->head = list->head->next;
	if (list->head) {
		list->head->prev = NULL;
	}
	if (prev == list->tail) {
		list->tail = NULL;
	}
	delete prev;
	list->size--;
}

template<class T>
void List<T>::popBack(List *list) {
	Node<T> *next;
	if (list->tail == NULL) {
		exit(4);
	}

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail) {
		list->tail->next = NULL;
	}
	if (next == list->head) {
		list->head = NULL;
	}

	delete next;
	list->size--;
}

/*template<class T>
List<T>::~List() {
	while (head)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
}*/


template <class T>
void List<T>::Insert(const Iterator& iter, const T& data)
{
	Iterator i;
	Node <T>*t;
	Node<T>*n = new Node<T>;
	n->data = data;
	if (iter == end()) {
		if (head)head->next = n;
		else head = n;
		n->prev = tail;
		tail = n;
		n->next = NULL;
	}
	else
		if (iter == begin()) {
			if (head) head->prev = n;
			else head = n;
			n->next = head;
			head = n;
		}
		else {
			for (i = begin(); i != end(); ++i)
				if (i == iter) break;
			assert(i != end());
			t = i.p->prev;
			t->next = n;
			n->prev = t;
			n->next = i.p;
			i.p->prev = n;
		}
}

template <class T>
void List<T>::Delete(const Iterator& iter)
{
	Node<T> *t;
	Iterator i;
	for (i = begin(); i != end(); ++i)
		if (i == iter) break;
	assert(i != end());
	t = i.p;
	if (i == begin()) {
		head = t->next;
		if (!head) tail = NULL;
	}
	else
		if (i == last()) {
			tail = t->prev;
			if (!tail) head = NULL;
		}
		else {
			t->prev->next = t->next;
			t->next->prev = t->prev;
		}
		delete t;
}


template <class T>
void List<T>::show()

{
	Node<T> *t = head;
	while (t != NULL)
	{
		cout << t->data << " ";
		t = t->next;
	}
	cout << endl;
}
