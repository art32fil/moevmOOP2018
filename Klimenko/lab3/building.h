#ifndef BUILDING_H
#define BUILDING_H
#include "Object.h"
<<<<<<< HEAD

=======
>>>>>>> 12cbd71f862c9caf9069973ad3fa3da2e569ec44
class Building :public Object
{
	_2dim range;
public:
	Building(ifstream&, const shared_ptr<Crown >);
	~Building();

	Object* is_on_position(_2dim);
	//thinkaboutit friend istream &operator>>(istream &in, Building &ob);
	friend ostream &operator<<(ostream &out, Building &ob);
};

#endif