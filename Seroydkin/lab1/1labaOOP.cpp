#include "battlefield.h"

int main()
{
	const int background = system("color 0F");

	char x, y;
	unsigned int damage;

	ifstream fin("indata.txt");
	if (!fin)
	{
		cout << " [File not found]";
		return 1;
	}

	BF *game = new BF(fin);
	
	while (1)
	{
		game->showmap();

		cout << "input coordinates of target (separated by space) [q to exit]: ";
		cin >> x;

		if (x == 'q')
			break;

		cin >> y;
		if (game->checkfield((int)x - '0', (int)y - '0'))
		{
			cout << "input a damage value: ";
			cin >> damage;
			game->damagefield(damage);
		}
	}

	delete(game);
	getchar(); getchar();
    return 0;
}
