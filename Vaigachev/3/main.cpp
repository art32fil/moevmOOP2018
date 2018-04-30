#include <iostream>
#include "battlefield.h"
#include <string>

using namespace std;

int main() {
	
	//Object blue({ 1,1 }, 1);
	
	battlefield *game = new battlefield();
	cout << "Printing field..." << endl;
	game->print();
	cout << "Field printed!" << endl;
	char x, y = NULL;
	string da_way;
	int damage;
	int result = 0;
	int option;
	while (true) {
		cout << "input coordinates of target (separeted by space) [press q to exit]" << endl << "Enter coords: ";
		cin >> x;
		if (x == 'q') break;
		cin >> y;
		

		if (auto temp = game->check_position({ (int)x - 48, (int)y - 48 })) {
			cout << "[Target selected]" << endl;
			cout << "Choose option..." << endl;
			if (dynamic_cast<Warior *>(temp)) {
				cout << "1. Hit" << endl;
				cout << "2. Move" << endl;
				cin >> option;
				switch (option) {
				case(1):
					cin >> damage;
					result = game->hit({ (int)x - 48, (int)y - 48 }, damage);
					break;
				case(2):
					cin >> da_way;
					temp = game->relocate(da_way, dynamic_cast<Warior *>(temp));
					break;
				}
			}
			if (dynamic_cast<Building *>(temp)) {
				cout << "1. Be hitted" << endl;
				cin >> damage;
				result = game->hit({ (int)x - 48, (int)y - 48 }, damage);
			}
			if (result) {
				cout << "team #" << result << " Ddefeaded!" << endl;
				break;
			}
		}
		else cout << "[Miss]" << endl;
		game->print();
	}
	delete game;
	
	getchar();
	getchar();
	/*
	cout << "Field fight: START" << endl;
	ifstream fin("data.txt");
	if (fin.eof()) {
		cerr << "File not found!" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	const shared_ptr<Crown> crown1(new Crown(1));
	const shared_ptr<Crown> crown2(new Crown(2));


	Warior *w = new Warior(fin,crown1);

	delete w;

	getchar();*/

}