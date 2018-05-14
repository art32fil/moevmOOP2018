#include <iostream>
#include "iter.h"

template <typename T>
size_t List<T>::size() {
	size_t s = 0;
	for (Iterator it = begin(); it != end(); ++it) {
		++s;
	}
	return s;
}