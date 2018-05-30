#ifndef CROWN_H
#define CROWN_H
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Crown {
	int color;
public:
	Crown() {
		cout <<"Crown:" << endl
			<< "	color = " << get_color() << endl
			<< "Crown." << endl;
	}
	Crown(bool tag) {
		set_color(tag);
		cout << "Crown:" << endl
			<< "	color = " << get_color() << endl
			<< "Crown." << endl;
	}
	~Crown() {
	   cout << "~Crown:" << endl
			<< "	color = " << get_color() << endl
			<< "~Crown." << endl;
	}
	string get_color() {
		if (color == 1) return "red";
		if (color == 0) return "green";
		return "none";
	}
	void set_color(bool tag) {
		if (tag) color = 1;
		else color = 0;
	}
};

#endif