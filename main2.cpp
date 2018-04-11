#include <iostream>

#include <cstdlib>

#include <ctime>

#include "List.h"

#include "obj.h"

#include "Pole.h"

using std::cout;

using std::cin;

using std::endl;

typedef List<int> L;

int main()

{

setlocale(LC_ALL, "Russian");

std::ifstream fin("1.txt");

int x,y,temp, damag;

Pole map;

map.fromfile(fin); 

map.showPole();

x=y=-1;

std::cout<<"������ ���������� ���� (����� ������)(q ��� ������) \n";

std::cin>>x>>y;

while(y!=-1)

{

temp=map.prov(x, y);

if(temp==0) std::cout<< "� ��������� ����� ���� ��� ����� \n";

if(temp==1) std::cout<< "� ��������� ����� ���� ��������� ���� ������� ����� \n";

if(temp==2) std::cout<< "� ��������� ����� ���� ��������� ���� ������� ����� \n";

if(temp==-1) std::cout<< "��������� ����� ��������� ��� ���� \n";

if ((temp!=-1) && (temp!=0))

{

std::cout<<"������� ����: ";

std::cin>>damag;

std::cout<<"\n���������� ���� ��������: ";

std::cout<<map.damage(x,y,damag);

std::cout<<std::endl;

map.showPole();

}

x=y=-1;

std::cout<<"������ ���������� ���� (����� ������)(q ��� ������) \n ";

std::cin>>x>>y;

}

}
