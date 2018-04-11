#ifndef PoleH
#define PoleH
#include "List.h"
#include "color.h"
#include "Crown.h"
#include <iostream>
#include <fstream>
#include <memory>


class Pole{
	private:
		int maxx, maxy;
		List<obj> red, green; //�����
		std::weak_ptr<Crown> crown_red,crown_green;
	public:
//		Pole(const int& x, const int& y, const List<obj>& r ,const List<obj>& gr): //�����������
//		maxx(x), maxy(y), red(r), green(gr)
//		{ }	
		Pole()
		{
				
		}
		//�����������
		~Pole()
		{
			red.~List();
			green.~List();
		}
		bool fromfile ( std::ifstream &f)//��� ������ �� �����
		{
			int kol;
			if (!f.is_open()) return false; // ���� ���� �� ������
			f >> maxx;
			f >> maxy;
			std::cout<<"������ ����: "<<maxx<<" "<<maxy<< std::endl;
			f >> kol; //���-�� ������ � ������� �����
			std::shared_ptr< Crown > c_red = std::make_shared<Crown>(1);//������� ������ 
			//crown_red
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f,c_red);//������ ������ � �������� � ����������� ��������� �� ����, � ��������� �� ������� ������
				red.PushBack(*r);//��������� ������ � ������� �����
				delete r;
			}
			crown_red=c_red;//����������� ����� ��������� �� ������� ������(������ �����)
			f >> kol; //���-�� ������ � ������� �����
			std::shared_ptr< Crown > c_green = std::make_shared<Crown>(2);//������� ������ 
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f,c_green);//������ ������ � �������� � ����������� ��������� �� ���� � ��������� �� ������� ������
				green.PushBack(*r);//��������� ������ � ������� �����
				delete r;
				//if (r.file(f))//���� ������ �� ����� ������ �������, 
				//	green.PushBack(r);//�� ��������� ����� � ������� �����
			}
			crown_green=c_green;//����������� ����� ��������� �� ������� ������(������ �����)
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
		/*obj* provred (const int& x, const int& y)
		{
			List<obj>::Iterator p;
			obj temp;
			for(p=red.Begin(); p!=red.End(); p++)
			{
				temp=*p; //���������� ������� ������ ������ �� ��������� >>
				if (temp.issure(x,y)) return *p; //��� ������� �� ������� ����� ���������� 1
			}
			
		}*/
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
		
		friend std::ostream& operator << (std::ostream& ostr,Pole& pol)
		{
			ostr << "  ";
			int o;
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
					o=pol.prov(i,j);
					if (o==0) ostr<<".";
					if (o==1) 
					{
						SetColor(Red , 0);
						ostr<<"o";	
						SetColor(White , Black);
					}
					
					if (o==2)
					{
						SetColor(Green , 0);
						ostr<<"o";	
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
