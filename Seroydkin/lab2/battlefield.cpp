#include "battlefield.h"


BF::BF(ifstream &fin)
{
	fin >> xs >> ys;
	cout << " Field:\n";
	cout << "\t x_size = " << xs << endl;
	cout << "\t y_size = " << ys << endl;

	fin >> A1s;
	auto A1flag = make_shared<Crown>(1);
	for (int i = 0; i < A1s; i++)
	{
		Obj *arm1 = new Obj(fin, A1flag);
		A1.addE(arm1);
	}

	fin >> A2s;
	auto A2flag = make_shared<Crown>(2);
	for (int i = 0; i < A2s; i++)
	{

		Obj *arm2 = new Obj(fin, A2flag);
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
		cout << " This coordinates are out of range\n";
		return false;
	}

	int i = -1;
	for (auto &unit1 : A1)
	{
		i++;
		if (unit1->checkobj(x, y))
		{
			path = make_pair(1, i);
			cout << " Selected target is red\n";
			if (unit1->alive())
				return true;
			else
			{
				cout << " But it is already destroyed\n";
				return false;
			}
		}
	}
	
	i = -1;
	for (auto &unit2 : A2)
	{
		i++;
		if (unit2->checkobj(x, y))
		{
			path = make_pair(2, i);
			cout << " Selected target is green\n";
			if (unit2->alive())
				return true;
			else
			{
				cout << " But it is already destroyed\n";
				return false;
			}
		}
	}

	cout << " No target on this coordinates\n";
	return false;
}


int BF::damagefield(int dmg)
{
	if (path.first == 1)
	{
		auto it = A1[path.second];
		if (it->damage(dmg))
		{
			A1.erase(path.second);
			mapBF[it->Get_X()][it->Get_Y()].second = 'x';
			delete(it);
			if (A1.size() == 0)
				return 1;
		}
	}
	else
	{
		auto it = A2[path.second];
		if (it->damage(dmg))
		{
			A2.erase(path.second);
			mapBF[it->Get_X()][it->Get_Y()].second = 'x';
			delete(it);
			if (A2.size() == 0)
				return 2;	
		}
	}
	return 0;
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
		mapBF[unit1->Get_X()][unit1->Get_Y()] = info('R', 'o');
	}

	for (auto &unit2 : A2)
	{
		mapBF[unit2->Get_X()][unit2->Get_Y()] = info('G', 'o');
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
	for (int j = 0; j < ys; j++)
	{
		cout << j << "|";
		for (int i = 0; i < xs; i++)
		{
			color(mapBF[i][j].first);
			cout << mapBF[i][j].second;
		}
		color('B');
		cout << "|\n";
	}
	cout << " +";
	for (int i = 0; i < xs; i++)
		cout << "-";
	cout << "+\n";
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