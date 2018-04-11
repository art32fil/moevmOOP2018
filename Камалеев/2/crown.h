#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Crown {
	int clr;
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
		if (flag) clr = 1;
		else clr = 0;
	}
	
	string Get_Color() {
		if (clr == 1) return "red";
		if (clr == 0) return "green";
		return "none";
	}
};