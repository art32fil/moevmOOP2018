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
		List<obj> red, green; //àðìèÿ
		std::weak_ptr<Crown> crown_red,crown_green;
	public:
//		Pole(const int& x, const int& y, const List<obj>& r ,const List<obj>& gr): //êîíñòðóêòîð
//		maxx(x), maxy(y), red(r), green(gr)
//		{ }	
		Pole()
		{
				
		}
		//äåêñòðóêòîð
		~Pole()
		{
			red.~List();
			green.~List();
		}
		bool fromfile ( std::ifstream &f)//äëÿ ÷òåíèÿ èç ôàéëà
		{
			int kol;
			if (!f.is_open()) return false; // åñëè ôàéë íå îòêðûò
			f >> maxx;
			f >> maxy;
			std::cout<<"Ðàçìåð ïîëÿ: "<<maxx<<" "<<maxy<< std::endl;
			f >> kol; //êîë-âî áîéöîâ â êðàñíîé àðìèè
			std::shared_ptr< Crown > c_red = std::make_shared<Crown>(1);//ñîçäàåì îáúåêò 
			//crown_red
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f,c_red);//ñîçäà¸ì îáúåêò è ïåðåäàåì â êîíñòðóêòîð óêàçàòåëü íà ôàéë, è óêàçàòåëü íà êðàñíóþ êîðîíó
				red.AddEnd(*r);//äîáàâëÿåì îáúåêò â êðàñíóþ àðìèþ
				delete r;
			}
			crown_red=c_red;//ïðèñâàèâàåì óìíûé óêàçàòåëü íà êðàñíóþ êîðîíó(ñëàáàÿ ñâÿçü)
			f >> kol; //êîë-âî áîéöîâ â çåëåíîé àðìèè
			std::shared_ptr< Crown > c_green = std::make_shared<Crown>(2);//ñîçäàåì îáúåêò 
			for (int i=0; i<kol; i++)
			{
				obj *r = new obj(f,c_green);//ñîçäà¸ì îáúåêò è ïåðåäàåì â êîíñòðóêòîð óêàçàòåëü íà ôàéë è óêàçàòåëü íà çåëåíóþ êîðîíó
				green.AddEnd(*r);//äîáàâëÿåì îáúåêò â çåëåíóþ àðìèþ
				delete r;
				//if (r.file(f))//åñëè ÷òåíèå èç ôàéëà ïðîøëî óñïåøíî, 
				//	green.PushBack(r);//òî äîáàâëÿåì îáúêò â çåëåíóþ àðìèþ
			}
			crown_green=c_green;//ïðèñâàèâàåì óìíûé óêàçàòåëü íà êðàñíóþ êîðîíó(ñëàáàÿ ñâÿçü)
		}
		int prov(const int& x, const int& y) //ïðîâåðêà íà íàëè÷èå îáúåêòà èç òîé èëè èíîé àðìèè
		{
			List<obj>::Iterator p;
			if ((x>maxx) || (y>maxy) || (x<0) || (y<0)) return -1; //åñëè âíå ïîëÿ
			for(p=red.Begin(); p!=red.End(); p++)
			{
					 //âîçâðàùàåò ýëåìåíò íàøåãî ñïèñêà ïî èòåðàòîðó >>
				if ((*p).issure(x,y)) return 1; //äëÿ íàëè÷èÿ èç êðàñíîé àðìèè âîçâðàùàåì 1
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y)) return 2; //äëÿ íàëè÷èÿ èç çåëåíîé àðìèè âîçâðàùàåì 2
			}
			return 0; //åñëè îáúåêòà íåò
		}
		int damage (const int& x, const int& y,const int& d) //ôóíêöèÿ, êîòîðàÿ íàíîñèò óðîí(îáúåêò îáÿçàòåëüíî äîëæåí áûòü)
		{
			int h;
			List<obj>::Iterator p;
			for(p=red.Begin(); p!=red.End(); p++)
			{
				if ((*p).issure(x,y)) 
				{
					h=(*p).damage(d);//íàíîñèì óðîí è ñîõðàíÿåì òåêóùåå çäîðîâüå â ïåðåìåííóþ h
					if (h>0)
						return h; //äëÿ íàëè÷èÿ èç êðàñíîé àðìèè âîçâðàùàåì çäîðîâüå
					else
					{
						red.Delete(p);
						return 0;              //âîçâðàùàåì 0 åñëè áîåö óáèò
					}	
					
				}
			}
			for(p=green.Begin(); p!=green.End(); p++)
			{
				if ((*p).issure(x,y))  
				{
					h=(*p).damage(d); //íàíîñèì óðîí è ñîõðàíÿåì òåêóùåå çäîðîâüå â ïåðåìåííóþ h
					if (h>0)
						return h; //äëÿ íàëè÷èÿ èç çåëåíûé àðìèè âîçâðàùàåì çäîðîâüå
					else
					{
						green.Delete(p);
						return 0;              //âîçâðàùàåì 0 åñëè áîåö óáèò
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
				temp=*p; //âîçâðàùàåò ýëåìåíò íàøåãî ñïèñêà ïî èòåðàòîðó >>
				if (temp.issure(x,y)) return *p; //äëÿ íàëè÷èÿ èç êðàñíîé àðìèè âîçâðàùàåì 1
			}
			
		}*/
		void showPole() //âûâîä
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
