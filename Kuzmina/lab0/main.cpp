#include <iostream>
#include <cstdlib>
#include "list.cpp"

using namespace std;

int main()
{
    List <int> lst;
    cout << "Введите размер списка " << endl;
    int size, enter,pos, answer = 0;
    cin >> size;
    for(int i=0;i<size;i++)
    {
        cout << "Введите  "<<i+1<<" число: ";
        cin >> enter;
        lst.Add_end(enter);
        cout <<endl;
    }
    cout<<"Вывод первого символа при помощи оператора [] : "<<lst[1]<<endl;
    cout<<"Вывод первого символа при помощи оператора -> : "<<lst.begin()->info<<endl;
    while (answer != 7){
        cout<<"Выберете пункт (от 1 до 7):"<<endl<<"1.Добавить число в начало списка\n2.Добавить число в конец списка\n3.Добавить по номеру\n4.Удалить число из начала списка(если не остался один элемент)\n5.Удалить число из конца списка(если не остался один элемент)\n6.Удалить число по номеру(если не остался один элемент)\n7.Завершить редактирование списка\n";
        cin>>answer;
        if(answer == 1){ cout << "Введите число: "; cin >> enter; lst.Add_begin(enter); lst.Show();}
        if(answer == 2){ cout << "Введите число: "; cin >> enter; lst.Add_end(enter); lst.Show();}
        if(answer == 3){ cout << "Введите число: "; cin >> enter; cout << "Введите позицию(не начало и не конец): "; cin >> pos; lst.Add_pos(enter,pos); lst.Show();}
        if(answer == 4){lst.Del_begin(); lst.Show();}
        if(answer == 5){ lst.Del_end(); lst.Show();}
        if(answer == 6){ cout << "Введите позицию(не начало и не конец): "; cin >> pos; lst.Del_pos(pos); lst.Show();}
    }
    answer = 0;
    List <int> :: Iterator it;
    while (answer != 3){
        cout<<"Выберете пункт (от 1 до 3):"<<endl<<"1. operator + (int)\n2. operator - (int))\n3. Завершить работу со списком\n";
        cin>>answer;
        if(answer == 1){
            cout << "Введите число, на которое хотите увеличить: ";
            cin >> enter;
            for(it=lst.begin();it!=lst.end();it++)
            {
                for(int i = 0; i<enter; i++)
                    (*it)++;
            }
        lst.Show();
        }
        if(answer == 2){
            cout << "Введите число, на которое хотите уменьшить: ";
            cin >> enter;
            for(it=lst.begin();it!=lst.end();it++)
            {
                for(int i = 0; i<enter; i++)
                    (*it)--;
            }
            lst.Show();
        }
    }
    lst.~List();
    return 0;
}

