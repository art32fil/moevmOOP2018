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

std::cout<<"ведите координаты цели (через пробел)(q для выхода) \n";

std::cin>>x>>y;

while(y!=-1)

{

temp=map.prov(x, y);

if(temp==0) std::cout<< "в выбранной точке поля нет боцов \n";

if(temp==1) std::cout<< "в выбранной точке поля находится боец красной армии \n";

if(temp==2) std::cout<< "в выбранной точке поля находится боец зеленой армии \n";

if(temp==-1) std::cout<< "выбранная точка находится вне поля \n";

if ((temp!=-1) && (temp!=0))

{

std::cout<<"Введите урон: ";

std::cin>>damag;

std::cout<<"\nОставшиеся очки здоровья: ";

std::cout<<map.damage(x,y,damag);

std::cout<<std::endl;

map.showPole();

}

x=y=-1;

std::cout<<"ведите координаты цели (через пробел)(q для выхода) \n ";

std::cin>>x>>y;

}

}
