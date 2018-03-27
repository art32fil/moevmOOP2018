#ifndef PoleH
#define PoleH
#include "List.h"
#include "color.h"
#include <iostream>
#include <fstream>


class Pole{
	private:
		int maxx, maxy;
		List<obj> red, green; //армия
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
			red.~List();
			green.~List();
		}
		bool fromfile ( std::ifstream &f)//для чтения из файла
		{
			int kol;
			if (!f.is_open()) return false; // если файл не открыт
			f >> maxx;
			f >> maxy;
			std::cout<<"Размер поля: "<<maxx<<" "<<maxy<< std::endl;
			f >> kol; //кол-во бойцов в красной армии
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f);//создаём объект и передаем в конструктор указатель на файл
				red.PushBack(*r);//добавляем объект в красную армию
				delete r;
			}
			f >> kol; //кол-во бойцов в зеленой армии
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f);//создаём объект и передаем в конструктор указатель на файл
				green.PushBack(*r);//добавляем объект в красную армию
				delete r;
				//if (r.file(f))//если чтение из файла прошло успешно, 
				//	green.PushBack(r);//то добавляем объкт в зеленую армию
			}
		}
		int prov(const int& x, const int& y) //проверка на наличие объекта из той или иной армии
		{
			List<obj>::Iterator p;
			if ((x>maxx) || (y>maxy) || (x<0) || (y<0)) return -1; //если вне поля
			for(p=red.Begin(); p!=red.End(); p++)
			{
					 //возвращает элемент нашего списка по итератору >>
				if ((*p).issure(x,y)) return 1; //для наличия из красной армии возвращаем 1
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y)) return 2; //для наличия из зеленой армии возвращаем 2
			}
			return 0; //если объекта нет
		}
		int damage (const int& x, const int& y,const int& d) //функция, которая наносит урон(объект обязательно должен быть)
		{
			int h;
			List<obj>::Iterator p;
			for(p=red.Begin(); p!=red.End(); p++)
			{
				if ((*p).issure(x,y)) 
				{
					h=(*p).damage(d);//наносим урон и сохраняем текущее здоровье в переменную h
					if (h>0)
						return h; //для наличия из красной армии возвращаем здоровье
					else
					{
						red.Delete(p);
						return 0;              //возвращаем 0 если боец убит
					}	
					
				}
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y))  
				{
					h=(*p).damage(d); //наносим урон и сохраняем текущее здоровье в переменную h
					if (h>0)
						return h; //для наличия из зеленый армии возвращаем здоровье
					else
					{
						red.Delete(p);
						return 0;              //возвращаем 0 если боец убит
					}	
					
				}
			}
		}
		/*obj* provred (const int& x, const int& y)
		{
			List<obj>::Iterator p;
			obj temp;
			for(p=red.Begin(); p!=red.End(); p++)
			{
				temp=*p; //возвращает элемент нашего списка по итератору >>
				if (temp.issure(x,y)) return *p; //для наличия из красной армии возвращаем 1
			}
			
		}*/
		void showPole() //вывод
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
		}
};


#endif 	
