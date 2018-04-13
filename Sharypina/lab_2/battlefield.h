#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H


#include <vector>
#include <memory>
#include "object.h"
#include "list.h"
#include "iter.h"
//----------------------------------------------

enum Color { white, green, red };


struct Position {
  Color color;
  char status;

  Position(Color clr, char sym) : color(clr), status(sym) {}
};

//----------------------------------------------

struct Size {
  int size_x;
  int size_y;

  Size(int x, int y): size_x(x), size_y(y) {
    std::cout << "size_x = " << size_x << std::endl;
    std::cout << "size_y = " << size_y << std::endl;
  }

  Size(){}
};

std::ifstream &operator>>(std::ifstream &fin, Size &size) {
  fin >> size.size_x >> size.size_y;
  return fin;
}

//----------------------------------------------

class Battlefield {

private:
  Size size;

  List<Object> first_army;
  std::weak_ptr<Crown> first_crown;

  List<Object> second_army;
  std::weak_ptr<Crown> second_crown;

  //std::vector<std::vector<char>> pattern;
  std::vector<std::vector<Position>> pattern;

public:
  Battlefield(std::ifstream &fin) {
    std::cout << "Field:" << std::endl;
    init_field(fin);
    std::cout << "Field." << std::endl;
  }
  //----------------------------------------------

  ~Battlefield() {
  //std::cout<<"~Field"<<std::endl;
  //  std::cout<<"~Field."<<std::endl;
}
  //----------------------------------------------

  Size &get_size() {
    return size;
  }
  //---------------------------------------------
  void init_field(std::ifstream &fin) {

    fin >> size; //считываем размерность поля

    //инициализируем паттерн
    Position tmp_pos(white, '.');
    std::vector<Position> tmp(size.size_x, tmp_pos);
    for (auto i = 0; i < size.size_y; i++) {
      pattern.push_back(tmp);
    }

    //корона зеленой армии
    auto tmp_first = std::make_shared<Crown>("green");
    first_crown = tmp_first;

    int num;
    fin >> num; //количество объектов первой армии

    Coordinates coords;
    int hpoints;

    for(int i = 0; i < num; i++) {
      //считываем объекты первой армии
      fin >> coords >> hpoints;
      Object obj(coords, hpoints, tmp_first);
      first_army.add_tail(obj); //добавляем в контейнер
    }

    auto tmp_second = std::make_shared<Crown>("red");
    second_crown = tmp_second;
    fin >> num; //количество объектов второй армии

    for(int i = 0; i < num; i++) {
     //считываем объекты первой армии
     fin >> coords >> hpoints;
     Object obj(coords, hpoints, tmp_second);
     second_army.add_tail(obj); //добавляем в контейнер
    }

  for (auto &obj: first_army) {
    pattern[obj.get_coord().x][obj.get_coord().y].color = green;
    pattern[obj.get_coord().x][obj.get_coord().y].status = 'o';
  }

  for (auto &obj: second_army) {
    pattern[obj.get_coord().x][obj.get_coord().y].color = red;
    pattern[obj.get_coord().x][obj.get_coord().y].status = 'o';
  }

}

//----------------------------------------------

  void update_pattern() {

    //проходим по первому контейнеру-армии
    for (auto &obj: first_army) {
        if (obj.get_hp() <= 0) { //если нет hp, то отмечаем крестиком
          pattern[obj.get_coord().x][obj.get_coord().y].status='x';
        }
    }

    //проходим по второму контейнеру-армии
    for (auto &obj2: second_army) {
        if (obj2.get_hp() <= 0) { //если нет hp, то отмечаем крестиком
          pattern[obj2.get_coord().x][obj2.get_coord().y].status='x';
        }
    }

  }

  //----------------------------------------------

  void print_field() {
    std::cout << std::endl;
    std::cout << "  ";
    for(int i = 0; i < size.size_x; i++)
      std::cout << i << " ";
    std::cout << std::endl;
    std::cout << " +";
    for(int i = 0; i < size.size_x; i++)
      std::cout << "- ";
    std::cout << "+";
    std::cout << std::endl;

    Coordinates coord;
    for (coord.y = 0; coord.y < size.size_y; coord.y++) {
      std::cout << coord.y << "|";
      for (coord.x = 0; coord.x < size.size_x; coord.x++) {
        if (pattern[coord.x][coord.y].color == green) {
          std::cout << "\033[1;32m" << pattern[coord.x][coord.y].status << "\033[0m" << " ";
        }
        else if (pattern[coord.x][coord.y].color == red) {
          std::cout << "\033[1;31m" << pattern[coord.x][coord.y].status << "\033[0m" << " ";
        }
        else std::cout << pattern[coord.x][coord.y].status << " ";
      }
      std::cout << "|" << std::endl;
    }

    std::cout << " +";
    for(int i = 0; i < size.size_x; i++)
      std::cout << "- ";
    std::cout << "+";
    std::cout << std::endl;
    std::cout << std::endl;

  }
  //----------------------------------------------

 Object* check_object(Coordinates coord, int &pos) {

   Object* cur;
   if(coord.x < 0 || coord.x >= size.size_x ||coord.y < 0 ||coord.y >= size.size_y) {
    pos = -1; //если выходит за предлы поля боя
    return nullptr;
  }
    for(auto &obj: first_army) {
      cur = obj.check_position(coord);
      if(cur) {
          pos = 1; //если объект первой армии
          return cur;
        }
    }

    for (auto &obj: second_army) {
      cur = obj.check_position(coord);
      if(cur) {
          pos = 2; //если объект второй армии
          return cur;
        }
    }

    pos = 0; //если пустая позиция
    return nullptr;
  }
  //----------------------------------------------

  void delete_object(int army, int id) {

    int num = 0;
    if (army == green) {
      for (auto &obj: first_army) {
        if (obj.get_id() == id) {
          first_army.delete_num(num);
          return;
        }
        num++;
      }
    }
    else {
      for(auto &obj2: second_army) {
        if (obj2.get_id() == id) {
          second_army.delete_num(num);
          return;
        }
        num++;
      }
    }
  }

//---------------------------------------------------

Color winner(){
  if (first_crown.expired()) return red;
  else if (second_crown.expired()) return green;
  else return white;
}

};

std::ostream& operator<<(std::ostream& out, Battlefield& field) {
  field.print_field();
  return out;
}

std::istream& operator>>(std::istream& in, Battlefield& field) {
  in >> field.get_size().size_x >> field.get_size().size_y;
  return in;
}

#endif
