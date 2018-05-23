#pragma once

#include <iostream>

template <typename T>
class List {
private:
	struct Node;
public:
	class Iterator {
	public:
		Iterator(Node* node) : m_node(node) {}
		bool operator==(Iterator other) {
			return m_node == other.m_node;
		}

		bool operator!=(Iterator other) {
			return !operator==(other);
		}

		T& operator*() {
			return m_node->m_t;
		}

		void operator++() {
			if (m_node) {
				m_node = m_node->m_next;
			}
		}

		void operator+(int i) {
			for (int j = 0; j < i; j++) {
				m_node = m_node->m_next;
			}
		}
		void operator-(int i) {
			for (int j = 0; j < i; j++) {
				m_node = m_node->m_prev;
			}
		}
	private:
		Node * m_node;
	};

public:
	List() : m_head(NULL), m_tail(NULL) {}
	~List() {
		while (m_head) {
			remove();
		}
	}
	void append(T t) {
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
	void remove() {
		del(0);
	}
	void del(int i) {
		Node* current = m_head;
		for (int j = 0; j <i; j++) {
			current = current->m_next;
		}
		if (current == m_head || current == m_tail) {
			if (current == m_head) {
				current->m_prev = NULL;
				m_head = current->m_next;
			}
			if (current == m_tail) {
				m_tail = current->m_prev;
				if (m_tail)
					current->m_prev->m_next = NULL;
			}
		}
		else {
			current->m_prev->m_next = current->m_next;
			current->m_next->m_prev = current->m_prev;
		}
		delete current;

	}
	Iterator begin() {
		return Iterator(m_head);
	}
	Iterator end() {
		return Iterator(NULL);
	}
	size_t size();

	T& operator[](int i) {
		Node* current = m_head;
		for (int j = 0; j < i; j++) {
			current = current->m_next;
		}
		return current->m_t;
	}

private:
	struct Node {
		Node() : m_next(NULL), m_prev(NULL) {}
		Node(T t) : m_t(t), m_next(NULL), m_prev(NULL) {}
		~Node() {
			delete m_t;
		}
		T m_t;
		Node* m_next;
		Node* m_prev;
	};
	Node* m_head;
	Node* m_tail;
};
