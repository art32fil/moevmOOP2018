#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
using namespace std;


template <class type>
struct element {
	type info;
	element *next, *prev;

};


template<class type>
class container {

	element<type>* begin;
	element<type>* end;

public:

	class iterator {
		element<type>* pointer;

	public:
		iterator(element<type>* p) : pointer(p) {}

		element<type>* operator+(int i) {
			for (int k = 0; k < i; k++) {
				pointer = pointer->next;
			}
			return pointer;
		}

		element<type>* operator-(int i) {
			for (int k = 0; k < i; k++) {
				pointer = pointer->prev;
			}
			return pointer;
		}

		element<type>* begin() {
			while (pointer->prev) {
				pointer = pointer - 1;
			}
			return pointer;
		}

		element<type>* end() {
			while (pointer->prev) {
				pointer = pointer + 1;
			}
			return pointer;
		}

		element<type>& operator*() {
			return *pointer;
		}

		element<type>* operator->() {
			return pointer;
		}

		void operator=(iterator it) {
			this->pointer = it.pointer;
		}

		bool operator!=(element<type>* p) {
			return *pointer != *p;
		}

		element<type>*& get() {
			return pointer;
		}
	};

	container() {
		begin = nullptr;
		end = nullptr;
	}

	void add_to_end(type el);
	void add_to_begin(type& el);

	void add(int i, type el) {
		iterator it(begin);
		iterator it2(begin);
		it = it + (i - 1);
		it2 = it2 + i;

		element<type>* p = new element<type>;
		p->info = el;
		p->next = it2.get();
		p->prev = it.get();
		it->next = p;
		it2->prev = p;
	}

	type& operator[] (int i) {
		iterator it(begin);
		it = it + i;
		return it->info;
	}

	int size() {

		if (begin == nullptr) {
			return 0;
		}
		else {
			iterator p(begin);
			int s = 1;
			while (p.get() != end) {
				p = p + 1;
				++s;
			}
			return s;
		}

	}
	void del_from_end() {
		element<type>* p = end;
		end = end->prev;
		end->next = nullptr;
		delete p;
	}
	void del_from_begin() {
		element<type>* p = begin;
		begin = begin->next;
		begin->prev = nullptr;
		delete p;
	}

	void del(int i) {
		if (i == 0)
		{
			this->del_from_begin();
			return;
		}
		else if (i == this->size() - 1) {
			this->del_from_end();
		}

		iterator it2(begin);
		it2 = it2 + i;
		iterator it(begin);
		it = it + (i - 1);
		it->next = it->next->next;
		it->next->prev = it.get();
		delete it2.get();
	}
};


template<class type>
void container<type>::add_to_end(type el)
{

	if (begin == nullptr) {
		begin = new element<type>;
		begin->info = el;
		begin->next = nullptr;
		begin->prev = nullptr;
		end = begin;
	}
	else {
		element<type>* p = end;
		end->next = new element<type>;
		end = end->next;
		end->prev = p;
		end->info = el;
		end->next = nullptr;
	}
}

template<class type>
void container<type>::add_to_begin(type & el)
{

		if (begin == nullptr) {
			begin = new element<type>;
			begin->info = el;
			begin->next = nullptr;
			begin->prev = nullptr;
			end = begin;
		}
		else {
			element<type>* p = begin;
			begin->prev = new element<type>;
			begin = begin->prev;
			begin->next = p;
			begin->info = el;
			begin->prev = nullptr;
		}
}

#endif // CONTAINER_H