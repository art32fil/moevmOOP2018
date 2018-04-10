#ifndef objH
#define objH
#include <iostream>
#include <fstream>

class obj {
	private:
		int x, y, heal; //кооординаты и кол-во очков
		
	public:	
		obj (const int& a, const int& b, const int& h) //конструктор
		{
			x=a;
			y=b;
			heal=h;
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<< std::endl;
		}
		obj (std::ifstream &f) //конструктор
		{
			if (!f.is_open()) exit(1); // если файл не открыт
			f >> x;
			f >> y;
			f >> heal;
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<< std::endl;
		}
		obj() 
		{
			x=-1;
			y=-1;
			heal=-1;
			std::cout<<"Объект: х="<<x<<" у="<<y<<" hp="<<heal<< std::endl;
		}
		~obj() //декструкор
		{
			std::cout<<"~Объект: х="<<x<<" у="<<y<<" hp="<<heal<< std::endl;
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
};

#endif 
