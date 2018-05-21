#include "battlefield.h"


BF::BF(ifstream &fin)
{
	char type;
	fin >> xs >> ys;
	cout << " Field:\n";
	cout << "\t x_size = " << xs << endl;
	cout << "\t y_size = " << ys << endl;

	fin >> A1s;
	auto A1flag = make_shared<Crown>(1);
	for (int i = 0; i < A1s; i++)
	{
		fin >> type;
		if (type == 'w')
		{
			War *war1 = new War(fin, A1flag);
			A1war.addE(war1);
		}
		else
		{
			Bld *bld1 = new Bld(fin, A1flag);
			A1bld.addE(bld1);
		}
	}

	fin >> A2s;
	auto A2flag = make_shared<Crown>(2);
	for (int i = 0; i < A2s; i++)
	{
		fin >> type;
		if (type == 'w')
		{
			War *war1 = new War(fin, A2flag);
			A2war.addE(war1);
		}
		else
		{
			Bld *bld1 = new Bld(fin, A2flag);
			A2bld.addE(bld1);
		}
	}

	makemap();
	cout << " Field.\n";
}


BF::~BF()
{
	cout << "\n Free memory\n";
	cout << " ~Field:\n";
	for (auto &unit1 : A1war)
		delete(unit1);
	for (auto &unit1 : A1bld)
		delete(unit1);
	for (auto &unit2 : A2war)
		delete(unit2);
	for (auto &unit2 : A2bld)
		delete(unit2);
	cout << " ~Field.\n";
}


bool BF::checkfield(int x, int y)
{
	index = -1;
	if (x < 0 || x > xs || y < 0 || y > ys)
	{
		cout << " This coordinates are out of range\n";
		return false;
	}

	if (turn)
	{
		for (auto &unit1 : A1war)
		{
			index++;
			if (unit1->checkobj(x, y))
			{
				cur = unit1;
				if (unit1->alive())
					return true;
				else
				{
					cout << " This is a dead body\n";
					return false;
				}
			}
		}

		for (auto &unit : A1bld)
		{
			if (unit->checkobj(x, y))
			{
				cout << " This is red building (do nothing in this version)\n";
				return false;
			}
		}
	}
	else
	{
		for (auto &unit2 : A2war)
		{
			index++;
			if (unit2->checkobj(x, y))
			{
				cur = unit2;
				if (unit2->alive())
					return true;
				else
				{
					cout << " This is a dead body\n";
					return false;
				}
			}
		}

		for (auto &unit : A2bld)
		{
			if (unit->checkobj(x, y))
			{
				cout << " This is green building (do nothing in this version)\n";
				return false;
			}
		}
	}
	return false;
}


void BF::makemap()
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
			mapBF[i][j] = info('B', '.');
	}

	if (!turn)
	{
		for (auto &unit : A1bld)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('R', 'H');

		for (auto &unit : A1war)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('R', 'o');

		for (auto &unit : A2bld)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('G', 'H');

		for (auto &unit : A2war)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('G', 'o');
	}
	else
	{
		for (auto &unit : A2bld)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('G', 'H');

		for (auto &unit : A2war)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('G', 'o');

		for (auto &unit : A1bld)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('R', 'H');
	
		for (auto &unit : A1war)
			mapBF[unit->Get_X()][unit->Get_Y()] = info('R', 'o');
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


bool BF::play()
{
	vector <char> dir = { 'u','d','l','r' };
	int cho;
	if (turn)
		cout << " RED ARMY TURN\n";
	else
		cout << " GREEN ARMY TURN\n";
	char a, b, mov;
	int x, y;
	do
	{
		cout << " input coordinates of object (separated by space) [q to exit]: ";
		cin >> a;
		if (a == 'q')
			return false;
		cin >> b;
		x = (int)a - '0';
		y = (int)b - '0';
	} while (!checkfield(x, y));

	War *att = cur;
	do {
		cout << " 1) Move warrior\n";
		cout << " 2) Attack enemy\n";
		cout << " Command: ";
		cin >> cho;
	} while (cho != 1 && cho != 2);
	
	if (cho == 1)
	{
		if (x == 0)
			dir.erase(find(dir.begin(), dir.end(), 'l'));
		if (x == xs)
			dir.erase(find(dir.begin(), dir.end(), 'r'));
		if (y == 0)
			dir.erase(find(dir.begin(), dir.end(), 'u'));
		if (y == ys)
			dir.erase(find(dir.begin(), dir.end(), 'd'));
		
			cout << " Choose direction (";
			for (int i = 0; i < dir.size(); i++)
				cout << " " << dir[i];
			cout << " ): ";
			cin >> mov;
		

			cur->move(mov);
			turn = !turn;
			makemap();		
	}
	else
	{
		turn = !turn;
		if (checkfield(x, y))
		{
			if (att->damg(cur))
			{
				if (turn)
					A1war.erase(index);
				else
					A2war.erase(index);
				delete cur;
			}
			makemap();
		}
		else
			cout << " No enemy here\n";	
	}

	if (A1war.size() == 0)
	{
		cout << " All red warriors are dead\n";
		for (auto &unit : A1bld)
			delete (unit);
		A1bld.~List();
		cout << " [GREAM TEAM WIN]\n";
		return false;
	}
	else if (A2war.size() == 0)
	{
		cout << " All green warriors are dead\n";
		for (auto &unit : A2bld)
			delete (unit);
		A2bld.~List();
		cout << " [RED TEAM WIN]\n";
		return false;
	}
	else
		return true;
}