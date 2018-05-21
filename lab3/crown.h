#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Crown
{
	double clr;
public:
	Crown(int col) : clr(col)
	{
		cout << " Crown:\n";
		cout << "\t color = " << color() << endl;
		cout << " Crown.\n";
	}

	~Crown()
	{
		cout << " ~Crown:\n";
		cout << "\t color = " << color() << endl;
		cout << " ~Crown.\n";
	}

	string color()
	{
		if (clr == 1)
			return "red";
		else
			return "green";
	}
};