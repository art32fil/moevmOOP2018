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
		if (m_head) {
			Node* newHead = m_head->m_next;
			delete m_head;
			m_head = newHead;
		}
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
		for (int j = 0; j <i; j++) {
			current = current->m_next;
		}
		return current->m_t;
	}

private:
	struct Node {
		Node() : m_next(NULL), m_prev(NULL) {}
		Node(T t) : m_t(t), m_next(NULL), m_prev(NULL) {}
		T m_t;
		Node* m_next;
		Node* m_prev;
	};
	Node* m_head;
	Node* m_tail;
};
