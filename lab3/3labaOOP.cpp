// 3labaOOP.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "battlefield.h"

int main()
{
	const int background = system("color 0F");

	ifstream fin("indata.txt");
	if (!fin)
	{
		cout << " [File not found]";
		return 1;
	}

	bool flag = true;

	BF *game = new BF(fin);
	cout << *game;
	while (1)
	{
		if (!game->play())
			break;
		cout << *game;
	}
	delete(game);
	getchar(); getchar();
	return 0;
}