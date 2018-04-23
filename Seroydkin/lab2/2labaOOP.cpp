#include "battlefield.h"

int main()
{
	const int background = system("color 0F");
	
	char x, y;
	unsigned int damage, res;

	ifstream fin("indata.txt");
	if (!fin)
	{
		cout << " [File not found]";
		return 1;
	}

	BF *game = new BF(fin);
	
	while (1)
	{
		cout << *game;

		cout << " input coordinates of target (separated by space) [q to exit]: ";
		cin >> x;

		if (x == 'q')
			break;

		cin >> y;
		if (game->checkfield((int)x - '0', (int)y - '0'))
		{
			cout << " input a damage value: ";
			cin >> damage;
			res = game->damagefield(damage);
			if (res == 1)
			{
				cout << " Red crown destroyed. Green team win\n";
				break;
			}
			else if (res == 2)
			{
				cout << " Green crown destroyed. Red ream win\n";
				break;
			}
		}
	}

	delete(game);
	getchar(); getchar();
	return 0;
}
