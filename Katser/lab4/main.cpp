#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "obj.h"
#include "Pole.h"
#include "building.h"
#include "warrior.h"


using std::cout;
using std::cin;
using std::endl;


int main()
{
setlocale(LC_ALL, "Russian");
std::ifstream fin("1.txt");	
int x,y,temp,damag,v,RED=1,GREEN=2;
Pole map;
warrior *w;
map.fromfile(fin); //читаем из файла
std::cout<<map; //выводим на экран поле
x=y=-1;
std::cout<<"Введите координаты цели(через пробел)(q для выхода)  \n";
std::cin>>x>>y;
while(y!=-1)
{
	w=map.prov_warr(x, y,RED);//возвращаем указатель, 0-нет бойца, 1- если армия красного,
	// 2-зеленая, 
	if(w==NULL) std::cout<< "В выбранной точке поля нет бойцов красной армии\n";
	else 
	{
		std::cout<< "В выбранной точке поля находится боец красной армии x="<<x<<"y="<<y<<" \n";
		while(w)
		{
			std::cout<< "1: Идти влево \n";
			std::cout<< "2: Идти вправо \n";
			std::cout<< "3: Идти вверх \n";
			std::cout<< "4: Идти вниз \n";
			if (map.prov(w->koor_x(),w->koor_y(),GREEN)!=0)
				std::cout<< "5: Бить \n";
			std::cout<< "0: Закончить \n";
			std::cin>>v;
			
			if (v==1)
			{
				if(map.prov_xy(w->koor_x()-1,w->koor_y()))
					w->left();
				else
				std::cout<<"Идти влево невозможно \n";
			}	
			if (v==2)
			{
				if(map.prov_xy(w->koor_x()+1,w->koor_y()))
					w->right();
				else
				std::cout<<"Идти вправо невозможно \n";
			}	
			if (v==3)
			{
				if(map.prov_xy(w->koor_x(),w->koor_y()-1))
					w->up();
				else
				std::cout<<"Идти вверх невозможно \n";
			}	
			if (v==4)
			{
				if(map.prov_xy(w->koor_x(),w->koor_y()+1))
					w->down();
				else
				std::cout<<"Идти вниз невозможно \n";
			}	
			if (v==5)
			{
				if(map.prov(w->koor_x(),w->koor_y(),GREEN)!=0)
					map.damage(*w);
				else
				std::cout<<"Бить некого \n";
			}	
			if (v==0)
				w=NULL;
			std::cout<<map;
		}
	} 
	w=map.prov_warr(x, y,GREEN);//возвращаем указатель, 0-нет бойца, 1- если армия красного,
	// 2-зеленая, 
	if(w==NULL) std::cout<< "В выбранной точке поля нет бойцов зеленой армии\n";
	else 
	{
		std::cout<< "В выбранной точке поля находится боец зеленой армии x="<<x<<"y="<<y<<" \n";
		while(w)
		{
			std::cout<< "1: Идти влево \n";
			std::cout<< "2: Идти вправо \n";
			std::cout<< "3: Идти вверх \n";
			std::cout<< "4: Идти вниз \n";
			if (map.prov(w->koor_x(),w->koor_y(),RED)!=0)
				std::cout<< "5: Бить \n";
			std::cout<< "0: Закончить \n";
			std::cin>>v;
			
			if (v==1)
			{
				if(map.prov_xy(w->koor_x()-1,w->koor_y()))
					w->left();
				else
				std::cout<<"Идти влево невозможно \n";
			}	
			if (v==2)
			{
				if(map.prov_xy(w->koor_x()+1,w->koor_y()))
					w->right();
				else
				std::cout<<"Идти вправо невозможно \n";
			}	
			if (v==3)
			{
				if(map.prov_xy(w->koor_x(),w->koor_y()-1))
					w->up();
				else
				std::cout<<"Идти вверх невозможно \n";
			}	
			if (v==4)
			{
				if(map.prov_xy(w->koor_x(),w->koor_y()+1))
					w->down();
				else
				std::cout<<"Идти вниз невозможно \n";
			}	
			if (v==5)
			{
				if(map.prov(w->koor_x(),w->koor_y(),RED)!=0)
					map.damage(*w);
				else
				std::cout<<"Бить некого \n";
			}	
			if (v==0)
				w=NULL;
			std::cout<<map;
		}
	}
	
	//if(temp==-1) std::cout<< "Выбранная точка находится вне поля \n";
	
	/*if ((temp!=-1) && (temp!=0))
	{
		std::cout<<"Введите урон: ";
		std::cin>>damag;
		std::cout<<"\nОставшиеся очки здоровья: ";
		std::cout<<map.damage(x,y,damag);
		
		std::cout<<std::endl;
		//map.showPole();
		std::cout<<map;
	}*/
	 
	x=y=-1;
	std::cout<<"Введите координаты цели(через пробел)(q для выхода) \n ";
	std::cin>>x>>y;
}



std::cin>>damag;
}
