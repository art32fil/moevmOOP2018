#ifndef warriorH
#define warriorH
#include "List.h"
#include "color.h"
#include "Crown.h"
#include "building.h"
#include <iostream>
#include <fstream>
#include <memory>

class warrior : public obj
{
	protected:
		int dmg;//сила удара
	public:
	    warrior():obj()
		{
			dmg=0;
			std::cout<< "Воин: сила удара = "<<dmg<<std::endl;
		}
		warrior(std::ifstream &f,std::shared_ptr< Crown > &cr):obj(f,cr) //конструктор
		{
			f >> dmg;
			std::cout<<"Воин: сила удара = "<<dmg<<std::endl;
		}	
		warrior(const warrior &b):obj(b.x,b.y,b.heal,b.crown)//конструктор копирования
		{
			dmg=b.dmg;
			std::cout<<"Воин: сила удара = "<<dmg<<std::endl;
		}
		/*warrior(const int& a, const int& b, const int& h,const int& d):obj(a,b,h) //конструктор
		{
			dmg=d;
			std::cout<<"Воин: сила удара = "<<dmg<<std::endl;
		}*/
		~warrior() //декструкор
		{
			std::cout<<"~Воин: сила удара = "<<dmg<<std::endl;
		}
		void left()	
		{
			x=x-1;
		}
		void right()	
		{
			x=x+1;
		}
		void down()	//вниз
		{
			y=y+1;
		}
		void up()	//вверх
		{
			y=y-1;
		}
		int attack(warrior &w)//функция для атаки, которая принимает адрес воина,которого мы атакуем
		{
			return w.damage(dmg);
		}
		int attack(building &w)//функция для атаки, которая принимает адрес здания,которое мы атакуем
		{
			return w.damage(dmg);
		}
};


#endif 	
