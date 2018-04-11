#ifndef PoleH
#define PoleH
#include "List.h"
#include "color.h"
#include "obj.h"
#include <iostream>
#include <fstream>


class Pole{
	private:
		int maxx, maxy;
		List<obj> red, green; //�����
	public:

		Pole()
		{	
		}
		//�����������
		~Pole()
		{
			red.~List();
			green.~List();
		}
		bool fromfile ( std::ifstream &f)//�� �����
		{
			int kol;
			if (!f.is_open()) return false; 
			f >> maxx;
			f >> maxy;
			std::cout<<"������ ����: "<<maxx<<" "<<maxy<< std::endl;
			f >> kol; //���-�� ������ � ������� �����
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f);//������ ������ � �������� � ����������� ��������� �� ����
				red.AddEnd(*r);//��������� ������ � ������� �����
				delete r;
			}
			f >> kol; //���-�� ������ � ������� �����
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f);//������ ������ � �������� � ����������� ��������� �� ����
				green.AddEnd(*r);//��������� ������ � ������� �����
				delete r;
			}
		}
		int prov(const int& x, const int& y) //�������� �� ������� ������� �� ��� ��� ���� �����
		{
			List<obj>::Iterator p;
			if ((x>maxx) || (y>maxy) || (x<0) || (y<0)) return -1; //���� ��� ����
			for(p=red.Begin(); p!=red.End(); p++)
			{
					 //���������� ������� ������ ������ �� ��������� >>
				if ((*p).issure(x,y)) return 1; //��� ������� �� ������� ����� ���������� 1
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y)) return 2; //��� ������� �� ������� ����� ���������� 2
			}
			return 0; //���� ������� ���
		}
		int damage (const int& x, const int& y,const int& d) //�������, ������� ������� ����(������ ����������� ������ ����)
		{
			int h;
			List<obj>::Iterator p;
			for(p=red.Begin(); p!=red.End(); p++)
			{
				if ((*p).issure(x,y)) 
				{
					h=(*p).damage(d);//������� ���� � ��������� ������� �������� � ���������� h
					if (h>0)
						return h; //��� ������� �� ������� ����� ���������� ��������
					else
					{
						red.Delete(p);
						return 0;              //���������� 0 ���� ���� ����
					}	
					
				}
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y))  
				{
					h=(*p).damage(d); //������� ���� � ��������� ������� �������� � ���������� h
					if (h>0)
						return h; //��� ������� �� ������� ����� ���������� ��������
					else
					{
						red.Delete(p);
						return 0;              //���������� 0 ���� ���� ����
					}	
					
				}
			}
		}
	
		void showPole() //�����
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
