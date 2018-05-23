#ifndef CrownH
#define CrownH
#include <iostream>
#include <fstream>
#include <memory>

class Crown
{
	public:
	int color;
	Crown (int a):color(a)
	{
		std::cout<<"\nCrown\n";
		if (a==1) std::cout<<"color = red\n";
		if (a==2) std::cout<<"color = green\n";
	}
	int getcolor()
	{
		return color;
	}
	~Crown ()
	{  
		std::cout<<"\nCrown is dead\n";
		if (color==1) std::cout<<"color = red\n";
		if (color==2) std::cout<<"color = green\n";
	}
};


#endif 	
