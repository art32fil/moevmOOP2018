#include <iostream>
#include "iter.h"

template <typename T>
List<T>::List() : m_head(NULL), m_tail(NULL) {}

template <typename T>
void List<T>::append(const T &t) {
	if (Node* node = new Node(t)) {
		if (m_head != NULL) {
			node->m_prev = m_tail;
			m_tail->m_next = node;
			m_tail = node;
		}
		else {
			m_head = m_tail = node;
		}
	}
}

template <typename T>
void List<T>::remove() {
	if (m_head) {
		Node* newHead = m_head->m_next;
		delete m_head;
		m_head = newHead;
	}
}

template <typename T>
List<T>::~List() {
	while (m_head) {
		remove();
	}
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(m_head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
	return Iterator(NULL);
}

template <typename T>
size_t List<T>::size() {
	size_t s = 0;
	for (Iterator it = begin(); it != end(); ++it) {
		++s;
	}
	return s;
}