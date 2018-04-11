#ifndef objH
#define objH
#include "Crown.h"
#include <iostream>
#include <fstream>
#include <memory>

class obj {
	private:
		int x, y, heal,id; //кооординаты и кол-во очков
		std::shared_ptr< Crown > crown;
	public:	
		static int count;
		obj (const int& a, const int& b, const int& h) //конструктор
		{
			x=a;
			y=b;
			heal=h;
			id=count++;
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<<" id="<<id<< std::endl;
		}
		obj (std::ifstream &f,std::shared_ptr< Crown > &cr) //конструктор
		{
			if (!f.is_open()) exit(1); // если файл не открыт
			f >> x;
			f >> y;
			f >> heal;
			crown=cr;
			id=count++;
			int temp=crown->getcolor();
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<<" id="<< id <<" id_crown="<<temp<< std::endl;
		}
		obj() 
		{
			x=-1;
			y=-1;
			heal=-1;
			id=count++;
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<<" id="<<id<< std::endl;
		}
		obj(const obj &a) //конструктор копирования
		{
			x=a.x;
			y=a.y;
			heal=a.heal;
			crown=a.crown;
			id=count++;
			int temp=crown->getcolor();
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<<" id="<<id<<" id_crown="<<temp<< std::endl;
		}
		~obj() //декструкор
		{
			int temp=crown->getcolor();
			std::cout<<"~Объект: х="<<x<<" у="<<y<<" hp="<<heal<<" id="<<id<<" id_crown="<<temp<< std::endl;
			//count--;
		}	 
	int damage (const int& d) //функция, которая наносит урон
		{
			//std::cout<<heal<<" урон" <<d<<"\n";
			heal=heal-d;
			return heal;
		}
	bool issure(const int& x1, const int& y1) //функция, которая проверяет наличие объекта на координатах
		{
			if ((x1==x) && (y1==y)) 
				return true;
			else
				return false; 
		}
	bool file(std::ifstream &f) //для считывания из файла
		{
			if (!f.is_open()) return false; // если файл не открыт
			f >> x;
			f >> y;
			f >> heal;
			//std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<< std::endl;
			return true; //указатель на себя
		}
	void show() //вывод
	{
		std::cout << "Координаты x= " << x << std::endl;
		std::cout << "Координаты y= " << y << std::endl;
		std::cout << "Количество очков/здоровье heal= " << heal << std::endl;
		
	}
	friend std::ostream& operator << (std::ostream& ostr,obj& o)
	{
		int temp=(o.crown)->getcolor();
		ostr<<"Объект: х="<<o.x<<" у="<<o.y<<" hp="<<o.heal<<" id="<<o.id<<" id_crown="<<temp<< std::endl;
		return ostr;
	}
};
int obj::count=0;
#endif 
