#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Crown {
	int color;
public:
	Crown() {
		cout << "Crown:" << endl;
		cout << "	color = " << Get_Color() << endl;
		cout << "Crown." << endl;
	}

	Crown(bool flag) {
		Set_Color(flag);
		cout << "Crown:" << endl;
		cout << "	color = " << Get_Color() << endl;
		cout << "Crown." << endl;
	}

	~Crown() {
		cout << "~Crown:" << endl;
		cout << "	color = " << Get_Color() << endl;
		cout << "~Crown." << endl;
	}

	void Set_Color(bool flag) {
		if (flag) color = 1;
		else color = 0;
	}
	
	string Get_Color() {
		if (color == 0) return "green";
		if (color == 1) return "red";
		return "none";
	}
};