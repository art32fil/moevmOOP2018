#include <iostream>
#include "field.h"

using namespace std;

int main() {

	//Object blue({ 1,1 }, 1);

	battlefield *game = new battlefield();
	cout << "Printing field..." << endl;
	game->print();
	cout << "Field printed!" << endl;
	char x, y = NULL;
	int damage;
	int result;
	while (true) {
		cout << "input coordinates of target (separeted by space) [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		//cout << (int)x - 48 << " " << (int)y - 48 << endl;
		if (game->check_position({ (int)x - 48, (int)y - 48 })) {
			cout << "[Target selected]" << endl << "Enter damage...";
			cin >> damage;
			result = game->hit({ (int)x - 48, (int)y - 48 }, damage);
			if (result) {
				cout << "team #" << result << " ddefeaded!" << endl;
				break;
			}
		}
		else cout << "[Miss]" << endl;
		game->print();
	}
	delete game;
	getchar();
	getchar();
}