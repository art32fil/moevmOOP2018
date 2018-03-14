#include <iostream>
#include "iter.cpp"

using namespace std;

int main() {
	List<int> list;
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);

	for (auto it = list.begin(); it != list.end(); it+2) {
		cout << *it << endl;
	}
	for (int elem : list) {
		cout << elem << endl;
	}
	system("pause");
	return 0;
}