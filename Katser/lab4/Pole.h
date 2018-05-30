#ifndef PoleH
#define PoleH
#include "List.h"
#include "color.h"
#include "Crown.h"
#include "building.h"
#include "warrior.h"
#include <iostream>
#include <fstream>
#include <memory>


class Pole{
	private:
		enum { RED = 1, GREEN=2 };
		int maxx, maxy;
		List<warrior> warr; //армия
		List<building> build;
		std::weak_ptr<Crown> crown_red,crown_green;
	public:
//		Pole(const int& x, const int& y, const List<obj>& r ,const List<obj>& gr): //конструктор
//		maxx(x), maxy(y), red(r), green(gr)
//		{ }	
		Pole()
		{
				
		}
		//декструктор
		~Pole()
		{
			
		}
		bool fromfile ( std::ifstream &f)//для чтения из файла
		{
			int kol;
			char ob;
			if (!f.is_open()) return false; // если файл не открыт
			f >> maxx;
			f >> maxy;
			std::cout<<"Размер поля: "<<maxx<<" "<<maxy<< std::endl;
			f >> kol; //кол-во бойцов в красной армии
			std::shared_ptr< Crown > c_red = std::make_shared<Crown>(RED);//создаем объект 
			//crown_red
			for (int i=0; i<kol; i++)
			{
				f >> ob;
				if(ob=='w')
				{
					warrior *r = new warrior(f,c_red);//создаём объект и передаем в конструктор указатель на файл и указатель на красную корону
					warr.PushBack(*r);//добавляем объект в воинов
					delete r;
				}
				else if(ob=='b')
				{
					building *r = new building(f,c_red);//создаём объект и передаем в конструктор указатель на файл и указатель на красную корону
					build.PushBack(*r);//добавляем объект в здания
					delete r;
				}
				else exit(1);//если не встретил символы w или b, то выполняем выход из программы
			}
			crown_red=c_red;//присваиваем умный указатель на красную корону(слабая связь)
			f >> kol; //кол-во бойцов в зеленой армии
			std::shared_ptr< Crown > c_green = std::make_shared<Crown>(GREEN);//создаем объект 
			for (int i=0; i<kol; i++)
			{
				f>>ob;
				if(ob=='w')
				{
					warrior *r = new warrior(f,c_green);//создаём объект и передаем в конструктор указатель на файл и указатель на зеленую корону
					warr.PushBack(*r);//добавляем объект в воинов
					delete r;
				}
				else if(ob=='b')
				{
					building *r = new building(f,c_green);//создаём объект и передаем в конструктор указатель на файл и указатель на зеленую корону
					build.PushBack(*r);//добавляем объект в здания
					delete r;
				}
				else exit(1);//если не встретил символы w или b, то выполняем выход из программы
			}
			crown_green=c_green;//присваиваем умный указатель на зеленую корону(слабая связь)
		}
		bool prov_xy(const int& x, const int& y)//проверка на наличие координаты в поле
		{
			if((x>maxx) || (y>maxy) || (x<0) || (y<0)) 
				return false;
			return true;
		}
		int prov(const int& x, const int& y,const int& color) //проверка на наличие объекта по цвету
		{
			if ((x>maxx) || (y>maxy) || (x<0) || (y<0)) return -1; //если вне поля
			
			for(List<warrior>::Iterator p=warr.Begin(); p!=warr.End(); p++)
			{
					 //возвращает элемент нашего списка по итератору >>
				if ((*p).issure(x,y)) 
				{
					if ( (*p).color() ==color )
						return 1; //для наличия воина 1
				}
			}
			
			for(List<building>::Iterator p=build.Begin(); p!=build.End(); p++)
			{
				if ((*p).issure(x,y)) 
				{
					if (( (*p).color() )==color )
						return 10; //для наличия здания 10
				}
			}
			return 0; //если объекта нет
		}
		
		//int damage(const warrior& w1,const warrior& w2) //воин 1 бьет воина 2
		//{
		//	return w1.attack(w2);
		//}
		
		int damage(warrior& w1) //воин 1 бьет объект
		{
			int h, x1, y1,col;
			
			x1=w1.koor_x();
			y1=w1.koor_y();
			col= w1.color();					
			for(List<warrior>::Iterator p=warr.Begin(); p!=warr.End(); p++) //проверяем всех воинов
			{
				if ( ( (*p).issure(x1,y1) ) && ( col!=(*p).color() ) ) //ищем воина на техже координатах и другово цвета
				{
					h=w1.attack((*p));//наносим урон и сохраняем текущее здоровье в переменную h
					if (h>0)
						return h; //возвращаем здоровье
					else
					{
						warr.Delete(p);
						return 0;              //возвращаем 0 если боец убит
					}		
				}
			}
			
			for(List<building>::Iterator p=build.Begin(); p!=build.End(); p++) //проверяем все здания
			{
				if ( ( (*p).issure(x1,y1) ) && ( col!=(*p).color() ) ) //ищем здание на техже координатах и другово цвета
				{
					h=w1.attack((*p));//наносим урон и сохраняем текущее здоровье в переменную h
					if (h>0)
						return h; //возвращаем здоровье
					else
					{
						build.Delete(p);
						return 0;              //возвращаем 0 если боец убит
					}		
				}
			}
		}
		
		warrior* prov_warr(const int& x, const int& y)//возвращает адрес воина по координатам либо 0 если нет
		{
			for(List<warrior>::Iterator p=warr.Begin(); p!=warr.End(); p++)
			{
				if ((*p).issure(x,y)) return &(*p); //для наличия воина возвращаем адрес
			}
			return NULL;
		}
		warrior* prov_warr(const int& x, const int& y,int &color)//возвращает адрес воина по координатам и цвету короны либо 0 если нет
		{
			for(List<warrior>::Iterator p=warr.Begin(); p!=warr.End(); p++)
			{
				if ((*p).issure(x,y)&&( (*p).color()==color )) return &(*p); //для наличия воина возвращаем адрес
			}
			return NULL;
		}
		/* void showPole() //вывод
		{
			std::cout << "  ";
			int o;
			for(int a=0; a<maxy; a++)
			{
				std::cout<< a;
			} 
			std::cout << std::endl<< " +";
			for(int a=0; a<maxy; a++)
			{
				std::cout << "-" ;
			} 
			std::cout << "+" << std::endl;
			for  (int j=0; j<maxy; j++)
			{
				std::cout<< j <<"|";
				for(int i=0; i<maxx; i++)
				{
					o=prov(i,j);
					if (o==0) std::cout<<".";
					if (o==1) 
					{
						SetColor(Red , 0);
						std::cout<<"o";	
						SetColor(White , Black);
					}
					
					if (o==2)
					{
						SetColor(Green , 0);
						std::cout<<"o";	
						SetColor(White , Black);
					} 
				}
				std::cout<< "|"<<std::endl;
			}
			std::cout << " +";
			for(int a=0; a<maxy; a++)
			{
				std::cout << "-" ;
			} 
			std::cout << "+" << std::endl;
		}*/
		
		friend std::ostream& operator << (std::ostream& ostr,Pole& pol)
		{
			ostr << "  ";
			int pr_red,pr_green;
			for(int a=0; a<pol.maxy; a++)
			{
				ostr<< a;
			} 
			ostr << std::endl<< " +";
			for(int a=0; a<pol.maxy; a++)
			{
				ostr << "-" ;
			} 
			ostr << "+" << std::endl;
			for  (int j=0; j<pol.maxy; j++)
			{
				ostr<< j <<"|";
				for(int i=0; i<pol.maxx; i++)
				{
					pr_red=pol.prov(i,j,RED);
					pr_green=pol.prov(i,j,GREEN);
					
					if ((pr_red!=0)&&(pr_green!=0))
					{
						SetColor(Blue , 0);
						ostr<<"A";
						SetColor(White , Black);
					}
					else if ((pr_red==0)&&(pr_green==0)) 
						ostr<<".";
					else if (pr_red==1) 
					{
						SetColor(Red , 0);
						ostr<<"w";	
						SetColor(White , Black);
					}
					else if (pr_red==10) 
					{
						SetColor(Red , 0);
						ostr<<"b";	
						SetColor(White , Black);
					}
					else if (pr_green==1)
					{
						SetColor(Green , 0);
						ostr<<"w";	
						SetColor(White , Black);
					}
					else if (pr_green==10)
					{
						SetColor(Green , 0);
						ostr<<"b";	
						SetColor(White , Black);
					} 
				}
				ostr<< "|"<<std::endl;
			}
			ostr << " +";
			for(int a=0; a<pol.maxy; a++)
			{
				ostr << "-" ;
			} 
			ostr << "+" << std::endl;
			return ostr;
		}
};


#endif 	
