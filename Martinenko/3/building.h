#ifndef BUILDING_H
#define BUILDING_H
#include "object.h"
#include "list.h"
#include <tuple>

class Building : public Object {
private:
	List<tuple<int, int>>* location;
public:
	Building(ifstream& f, const shared_ptr<Crown>& clr);
	Building(int x, int y, int hp, List<tuple<int, int>>* location,const shared_ptr<Crown> crown);
	int isObject(int x1, int y1);
	void _location() {
		location = new List<tuple<int, int>>;
	}
	~Building();
};

#endif