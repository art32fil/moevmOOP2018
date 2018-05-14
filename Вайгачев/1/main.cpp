#include <iostream>
#include "battlefield.h"

using namespace std;

int main() {
	
	//Object blue({ 1,1 }, 1);

	battlefield *game = new battlefield();
	cout << "Printing field..." << endl;
	game->print();
	cout << "Field printed!" << endl;
	char x, y = NULL;
	int damage;
	while (true) {
		cout << "input coordinates of target (separeted by space) [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		//cout << (int)x - 48 << " " << (int)y - 48 << endl;
		if (game->check_position({ (int)x - 48, (int)y - 48 })) {
			cout << "[Target selected]" << endl << "Enter damage..." ;
			cin >> damage;			
			game->check_position({ (int)x - 48, (int)y - 48 })->get_damage(damage);
		}
		else cout << "[Miss]" << endl;
		game->print();
	}
	delete game;
	getchar();
}