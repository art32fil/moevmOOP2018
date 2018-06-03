#ifndef CROWN_H
#define CROWN_H
#include <iostream>

using namespace std;





class Crown
{
	const int colour;
public:
	Crown(int col);
	int get_colour();
	~Crown();
};

#endif // CROWN_H