#include "Crown.h"


Crown::Crown(int col) :colour(col) {
	cout << "Crown: START" << endl;
	cout << "	colour = " << colour << endl;
	cout << "Crown: END" << endl;
};

int Crown::get_colour() {
	return colour;
}

Crown::~Crown() {
	cout << "~Crown: START" << endl;
	cout << "	colour = " << colour << endl;
	cout << "~Crown: END" << endl;
}