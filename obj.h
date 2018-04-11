#ifndef objH
#define objH
#include <iostream>
#include <fstream>

class obj {
	private:
		int x, y, heal; //����������� � ���-�� �����
		
	public:	
		obj (const int& a, const int& b, const int& h) //�����������
		{
			x=a;
			y=b;
			heal=h;
			std::cout<<"������: �="<<x<<" �="<<y<<" hp="<<heal<< std::endl;
		}
		obj (std::ifstream &f) //�����������
		{
			if (!f.is_open()) exit(1); // ���� ���� �� ������
			f >> x;
			f >> y;
			f >> heal;
			std::cout<<"������: �="<<x<<" �="<<y<<" hp="<<heal<< std::endl;
		}
		obj() 
		{
			x=-1;
			y=-1;
			heal=-1;
			std::cout<<"������: �="<<x<<" �="<<y<<" hp="<<heal<< std::endl;
		}
		~obj() //����������
		{
			std::cout<<"~������: �="<<x<<" �="<<y<<" hp="<<heal<< std::endl;
		}	 
	int damage (const int& d) //�������, ������� ������� ����
		{
			//std::cout<<heal<<" ����" <<d<<"\n";
			heal=heal-d;
			return heal;
		}
	bool issure(const int& x1, const int& y1) //�������, ������� ��������� ������� ������� �� �����������
		{
			if ((x1==x) && (y1==y)) 
				return true;
			else
				return false; 
		}
	bool file(std::ifstream &f) //��� ���������� �� �����
		{
			if (!f.is_open()) return false; // ���� ���� �� ������
			f >> x;
			f >> y;
			f >> heal;
			//std::cout<<"������: �="<<x<<" �="<<y<<" hp="<<heal<< std::endl;
			return true; //��������� �� ����
		}
	void show() //�����
	{
		std::cout << "���������� x= " << x << std::endl;
		std::cout << "���������� y= " << y << std::endl;
		std::cout << "���������� �����/�������� heal= " << heal << std::endl;
		
	}
};

#endif 
