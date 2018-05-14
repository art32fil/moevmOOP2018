#include <iostream>
#include <cstdlib>
#include "list.cpp"

using namespace std;

int main()
{
	List <int> list;
    cout << "Enter the size of the list (whole number): " << endl;
    int size, enter, position, pos, n = 0;
    cin >> size;
    for(int i = 0; i < size; i++)
    {
        cout << "Enter "<< i + 1 <<" number: ";
        cin >> enter;
        list.Supl_End(enter);
        cout << endl;
    }

	while (n != 7)
	{
		cout << "Please, choose the command (from 1 to 7): \n";
		cout << "1.Add number to the beginng of the list\n";
		cout << "2.Add number to the end of the list\n";
		cout << "3.Add by the position\n";
		cout << "4.Delete number from beginnig of the list (if there are more than one element in the list)\n";
		cout << "5.Delete number from the end of the list (if there are more than one element in the list)\n";
		cout << "6.Delete by the position\n";
		cout << "7.Finish redacting the list\n";
		cin >> n;
		switch (n)
		{
		case 1:
			cout << "Enter number: "; cin >> enter;
			list.Supl_Begin(enter);
			list.Print();
			break;
		case 2:
			cout << "Enter number: "; cin >> enter;
			list.Supl_End(enter);
			list.Print();
			break;
		case 3:
			cout << "Enter number: "; cin >> enter;
			cout << "Enter position (not the beginnig and not the end): "; cin >> position;
			list.Supl_Pos(enter, position);
			list.Print();
			break;
		case 4:
			list.Erase_Begin();
			list.Print();
			break;
		case 5:
			list.Erase_End();
			list.Print();
			break;
		case 6:
			cout << "Enter position (not the beginnig and not the end) "; cin >> position;
			list.Erase_Pos(position);
			list.Print();
			break;
		case 7:
			break;
		default:
			cout << "Wrong enter. Try again" << endl;
			break;
		}
    }

	cout << "\nEnter position of the number that you would like to print with operator []: " << endl;
	cin >> pos;
	cout << "Number with position " << pos << " printed with operator [] is: " << list[pos] << endl;
	int first = list.begin()->info;
	cout << "Number with the first position printed with operator -> is: " << first << endl << endl;


    n = 0;
    List <int> :: Iterator iter;
    while (n != 3)
	{
		cout << "Please, choose the command (from 1 to 3):" << endl;
		cout << "1. operator + (int)" << endl;
		cout << "2. operator - (int)" << endl;
		cout << "3.Finish work with the list" << endl;
        cin >> n;
        if (n == 1)
		{
            cout << "Enter number on wich you want to increase: ";
            cin >> enter;
            for(iter = list.begin(); iter != list.end(); iter++)
            {
                for(int i = 0; i < enter; i++)
                    (*iter)++;
            }
			list.Print();
		}
        
        if (n == 2)
		{
            cout << "Enter number on wich you want to decrease: ";
            cin >> enter;
            for(iter = list.begin(); iter != list.end(); iter++)
            {
                for(int i = 0; i < enter; i++)
                    (*iter)--;
            }
            list.Print();
        }
        if(n == 4){}
    }
    list.~List();
    return 0;
}
