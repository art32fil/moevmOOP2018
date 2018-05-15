#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <vector>
#include <memory>
#include "warrior.h"
#include "building.h"
#include "list.h"
#include "iter.h"
#include "features.h"


class Battlefield {

private:
  Size size;

  List<Object*> first_army;
  std::weak_ptr<Crown> first_crown;

  List<Object*> second_army;
  std::weak_ptr<Crown> second_crown;

  std::vector<std::vector<Position>> pattern;

public:
  Battlefield(std::ifstream &fin) {
    std::cout << "Field:" << std::endl;
    init_field(fin);
    std::cout << "Field." << std::endl;
  }

  //----------------------------------------------

  ~Battlefield() {
    std::cout<<"~Field:"<<std::endl;
    delete_everything();
    std::cout<<"~Field."<<std::endl;
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
    //считываем объекты первой армии
    read_army(fin, first_army, tmp_first);
    std::cout << "size (first_army) = " << first_army.size() << std::endl;
    //корона красной армии
    auto tmp_second = std::make_shared<Crown>("red");
    second_crown = tmp_second;
    //считываем объекты второй армии
    read_army(fin, second_army, tmp_second);

    //заполняем паттерн
    update_pattern();
}

//----------------------------------------------

void read_army(std::ifstream &fin, List<Object*>& army, std::shared_ptr<Crown> crown) {
  //считывание из файла объектов армии с заданной короной
 int num;
  fin >> num;
  char obj_type;
  Coordinates coords;
  int hp;
  for (int i = 0; i < num; i++) {
    fin >> obj_type;
    switch (obj_type) {
      case 'w': {
        int force;
        fin >> coords >> hp >> force;

        Warrior* war = new Warrior(coords, hp, crown, force);
        army.add_tail(war);
        break;
      }
      case 'b': {
        int num_extra; //количество дополнительных координат
        std::vector<Coordinates> extra_coords;
        Coordinates cur_extra; //координаты, считываемые в данный момент
        fin >> coords >> hp >> num_extra;
        extra_coords.push_back(coords);
        for (int i = 0; i < num_extra; i++) {
          fin >> cur_extra;
          extra_coords.push_back(cur_extra);
        }
        Building* build = new Building(coords, hp, crown, extra_coords);
        army.add_tail(build);
        break;
        }
        default: {
          std::cout << "wrong object type !!" << std::endl;
          break;
        }
      }
    }
  }

//----------------------------------------------

  void clear_pattern() {
    //очищает шаблон - поле
    for (int i = 0; i < size.size_x; i++) {
      for (int j = 0; j < size.size_y; j++) {
        pattern[i][j].status = '.';
        pattern[i][j].color = white;
      }
    }
  }

//----------------------------------------------

  void update_pattern() {
    //обновляет шаблон - поле для вывода в консоль
    clear_pattern();
    for (auto &obj: first_army) {
      char type = obj->get_type();
      if (type == 'w') {
        pattern[obj->get_coord().x][obj->get_coord().y].color = green;
        pattern[obj->get_coord().x][obj->get_coord().y].status = type;
      }
      else if (type == 'b') {
        Building* build = dynamic_cast<Building*>(obj);
        std::vector<Coordinates> coords = build->get_extra_coords();
        for (auto const& coord: coords) {
          pattern[coord.x][coord.y].color = green;
          pattern[coord.x][coord.y].status = type;
        }
      }
    }
    for (auto &obj: second_army) {
      char type = obj->get_type();
      if (type == 'w') {
        pattern[obj->get_coord().x][obj->get_coord().y].color = red;
        pattern[obj->get_coord().x][obj->get_coord().y].status = type;
      }
      else if (type == 'b') {
        Building* build = dynamic_cast<Building*>(obj);
        std::vector<Coordinates> coords = build->get_extra_coords();
        for (auto const& coord: coords) {
          pattern[coord.x][coord.y].color = red;
          pattern[coord.x][coord.y].status = type;
        }
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

 Object* check_object(Coordinates coord, std::string army_color) {
//проверка на принадлежность объекта с координатами coord армии цвета army_color
//возвращает указатель на этот объект, если он есть в данной армии
//иначе - возвращает nullptr
   Object* cur;
   if(coord.x < 0 || coord.x >= size.size_x ||coord.y < 0 ||coord.y >= size.size_y) {
  //  pos = -1; //если выходит за предлы поля боя
    return nullptr;
  }
  if (army_color == "green") {
    for(auto &obj: first_army) {
      cur = obj->check_position(coord);
      if (cur) {
          return cur;
        }
    }
  }
  else if (army_color == "red") {
    for (auto &obj: second_army) {
      cur = obj->check_position(coord);
      if(cur) {
          return cur;
        }
    }
  }
      return nullptr;
  }

  //----------------------------------------------

  void delete_object(int army, int id) {
    //удаляет объект армии по id
    int num = 0;
    if (army == green) {
      for (auto &obj: first_army) {
        if (obj->get_id() == id) {
          delete obj;
          obj = nullptr;
          first_army.delete_num(num);
          return;
        }
        num++;
      }
    }
    else {
      for (auto &obj2: second_army) {
        if (obj2->get_id() == id) {
          delete obj2;
          obj2 = nullptr;
          second_army.delete_num(num);
          return;
        }
        num++;
      }
    }
  }

//---------------------------------------------------

void check_hp() {
  //удаляет объекты с hp <= 0
  for (auto &obj: first_army) {
    if (obj->get_hp() <= 0) {
      delete_object(green, obj->get_id());
    }
  }
  for (auto &obj: second_army) {
    if (obj->get_hp() <= 0) {
      delete_object(red, obj->get_id());
    }
  }
}

//---------------------------------------------------

Color winner(){
  //определяет победителя
  if (first_crown.expired()) return red; //если на корону зеленых ничего не указывает, выигрывают красные
  else if (second_crown.expired()) return green; //и наоборот
  else return white; //обе короны живы, пока ничья
}

//---------------------------------------------------

void delete_everything() {
  //заканчивает игру, освобождает память
  for (auto& obj: first_army) {
    delete obj;
  }
  for (auto& obj: second_army) {
    delete obj;
  }

}
};

//---------------------------------------------------

std::ostream& operator<<(std::ostream& out, Battlefield& field) {
  field.print_field();
  return out;
}

//----------------------------------------------

std::istream& operator>>(std::istream& in, Battlefield& field) {
  in >> field.get_size().size_x >> field.get_size().size_y;
  return in;
}

#endif
