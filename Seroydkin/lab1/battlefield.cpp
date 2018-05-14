#include "battlefield.h"


BF::BF(ifstream &fin)
{
	fin >> xs >> ys;
	cout << " Field:\n";
	cout << "\t x_size = " << xs << endl;
	cout << "\t y_size = " << ys << endl;

	fin >> A1s;
	for (int i = 0; i < A1s; i++)
	{
		 Obj *arm1 = new Obj(fin);
		A1.addE(arm1);
	}

	fin >> A2s;
	for (int i = 0; i < A2s; i++)
	{
		Obj *arm2 = new Obj(fin);
		A2.addE(arm2);
	}

	makemap();

	cout << " Field.\n";
}


BF::~BF()
{
	cout << " ~Field:\n";
	for (auto &unit1 : A1)
		delete(unit1);
	for (auto &unit2 : A2)
		delete(unit2);
	cout << " ~Field.\n";
}


bool BF::checkfield(int x, int y)
{
	if (x < 0 || x > xs || y < 0 || y > ys)
	{
		cout << "This coordinates are out of range\n";
		return false;
	}

	for (auto &unit1 : A1)
	{
		if (unit1->checkobj(x, y))
		{
			it = unit1;
			cout << "Selected target is red\n";
			if (it->alive())
				return true;
			else
			{
				cout << "But it is already destroyed\n";
				return false;
			}
		}
	}

	for (auto &unit2 : A2)
	{
		if (unit2->checkobj(x, y))
		{
			it = unit2;
			cout << "Selected target is green\n";
			if (it->alive())
				return true;
			else
			{
				cout << "But it is already destroyed\n";
				return false;
			}
		}
	}

	cout << "No target on this coordinates\n";
	return false;
}


void BF::makemap()
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			mapBF[i][j] = info('B', '.');
		}
	}

	for (auto &unit1 : A1)
	{
		mapBF[unit1->get_x()][unit1->get_y()] = info('R', 'o');
	}

	for (auto &unit2 : A2)
	{
		mapBF[unit2->get_x()][unit2->get_y()] = info('G', 'o');
	}
}


void BF::color(char com)
{
	switch (com)
	{
	case 'B':
		cout << "\033[1;37m";
		break;
	case 'R':
		cout << "\033[1;31m";
		break;
	case 'G':
		cout << "\033[1;32m";
		break;
	default:
		break;
	}
}

void BF::showmap()
{
	cout << "  ";
	for (int i = 0; i < xs; i++)
		cout << i;
	cout << "\n +";
	for (int i = 0; i < xs; i++)
		cout << "-";
	cout << "+\n";
	for (int i = 0; i < xs; i++)
	{
		cout << i << "|";
		for (int j = 0; j < ys; j++)
		{
			color(mapBF[j][i].first);
			cout << mapBF[j][i].second;
		}
		color('B');
		cout << "|\n";
	}
	cout << " +";
	for (int i = 0; i < xs; i++)
		cout << "-";
	cout << "+\n";
}


void BF::damagefield(int dmg)
{
	it->damage(dmg);
	if (!it->alive())
		mapBF[it->get_x()][it->get_y()].second = 'x';
}