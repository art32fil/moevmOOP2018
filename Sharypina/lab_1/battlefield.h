#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H


#include <vector>
#include "object.h"
#include "list.h"
#include "iter.h"

struct Size
{
  int size_x;
  int size_y;

  Size(int x, int y): size_x(x), size_y(y)
  {
    std::cout<<"size_x = "<<size_x<<std::endl;
    std::cout<<"size_y = "<<size_y<<std::endl;
  }
  Size(){}
};

std::ifstream &operator>>(std::ifstream &fin, Size &size)
{
  fin>>size.size_x>>size.size_y;
  return fin;
}

//----------------------------------------------

class Battlefield
{

private:
  Size size;
  List<Object> first_army;
  List<Object> second_army;
  std::vector<std::vector<char>> pattern;

public:
  Battlefield(std::ifstream &fin)
  {
    std::cout<<"Field:"<<std::endl;
    init_field(fin);
    std::cout<<"Field."<<std::endl;
  }
  //----------------------------------------------

  ~Battlefield()
  {
  //std::cout<<"~Field"<<std::endl;
  //  std::cout<<"~Field."<<std::endl;
  }
  //----------------------------------------------

  Size &get_size() {return size;}
  //----------------------------------------------

  void init_field(std::ifstream &fin)
  {
    fin>>size; //считываем размерность поля

    //инициализируем паттерн
    std::vector<char> tmp(size.size_x, '.'); //вспомогательный вектор
    for (int i=0; i<size.size_y; i++)
      pattern.push_back(tmp); //заполняем матрицу-паттерн


    int num; //количество объектов в первой армии
    fin>>num;

    Coordinates coords;
    int hpoints;

    for(int i=0; i<num; i++) //считываем объекты первой армии
    {
      fin>>coords>>hpoints;
      Object obj(coords, hpoints);
      first_army.add_tail(obj); //добавляем в контейнер
    }

    fin>>num;

    for(int i=0; i<num; i++) //считываем объекты первой армии
    {
      fin>>coords>>hpoints;
      Object obj(coords, hpoints);
      second_army.add_tail(obj); //добавляем в контейнер
    }



  /*  Object obj; //вспомогательный объект

    for(int i=0; i<num; i++) //считываем объекты первой армии
    {
      fin>>obj;
      first_army.add_tail(obj); //добавляем в контейнер
    }

    fin>>num;

    for(int i=0; i<num; i++) //считываем объекты второй армии
    {
      fin>>obj;
      second_army.add_tail(obj); //добавляем в контейнер
    } */

    //заполняем паттерн
  /*  for(Elem<Object> elem: first_army)
    {
        pattern[elem.get_value().get_coord().y][elem.get_value().get_coord().x]='o';
    }

    for(Elem<Object> elem: second_army)
    {
        pattern[elem.get_value().get_coord().y][elem.get_value().get_coord().x]='0';
    } */

    for(auto &obj: first_army)
    {
        pattern[obj.get_coord().y][obj.get_coord().x]='o';
    }

    for(auto &obj: second_army)
    {
      pattern[obj.get_coord().y][obj.get_coord().x]='0';
    }
  }

//----------------------------------------------

  void update_pattern()
  {
    //проходим по первому контейнеру-армии
/*    for(Elem<Object> &elem: first_army)
    {
      if (elem.get_value().get_hp()<=0) //если нет hp, то отмечаем крестиком
        pattern[elem.get_value().get_coord().y][elem.get_value().get_coord().x]='x';
    }

    //проходим по второму контейнеру-армии
    for(Elem<Object> &elem: second_army)
    {
      if(elem.get_value().get_hp()<=0) //если нет hp, то отмечаем крестиком
        pattern[elem.get_value().get_coord().y][elem.get_value().get_coord().x]='X';
    } */
    for(auto &obj: first_army)
        {
          if (obj.get_hp()<=0) //если нет hp, то отмечаем крестиком
            pattern[obj.get_coord().x][obj.get_coord().y]='x';
        }

        //проходим по второму контейнеру-армии
        for(auto &obj: second_army)
        {
          if(obj.get_hp()<=0) //если нет hp, то отмечаем крестиком
            pattern[obj.get_coord().x][obj.get_coord().y]='X';
        }

  }
  //----------------------------------------------
  void print_field()
  {
    std::cout<<std::endl;
    std
    ::cout<<"  ";
    for(int i=0; i<size.size_x; i++)
      std::cout<<i<<" ";
    std::cout<<std::endl;
    std::cout<<" +";
    for(int i=0; i<size.size_x; i++)
      std::cout<<"- ";
    std::cout<<"+";
    std::cout<<std::endl;

    for(int i=0; i<size.size_y; i++)
    {
      std::cout<<i<<"|";
      for(int j=0; j<size.size_x; j++)
      {
        std::cout<<pattern[i][j]<<" ";
      }
      std::cout<<"|"<<std::endl;
    }

    std::cout<<" +";
    for(int i=0; i<size.size_x; i++)
      std::cout<<"- ";
    std::cout<<"+";
    std::cout<<std::endl;
    std::cout<<std::endl;

  }
  //----------------------------------------------

 Object* check_object(Coordinates coord, int &pos)
 {

   Object* cur;
   if(coord.x<0 || coord.x>=size.size_x ||coord.y<0 ||coord.y>=size.size_y)
  {
    pos= -1; //если выходит за предлы поля боя
    return nullptr;
  }
    for(auto &obj: first_army)
    {
      cur=obj.check_position(coord);
      if(cur)
        {
          pos=1; //если объект первой армии
          return cur;
        }
    }

    for (auto &obj: second_army)
    {
      cur=obj.check_position(coord);
      if(cur)
        {
          pos=2; //если объект второй армии
          return cur;
        }
    }

    pos = 0; //если пустая позиция
    return nullptr;
  }
};



#endif
