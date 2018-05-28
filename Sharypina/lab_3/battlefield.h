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

  void print_field(std::ostream& out) {
    out << std::endl;
    out << "  ";
    for(int i = 0; i < size.size_x; i++)
      out << i << " ";
    out << std::endl;
    out << " +";
    for(int i = 0; i < size.size_x; i++)
      std::cout << "- ";
    out << "+";
    out << std::endl;

    Coordinates coord;
    for (coord.y = 0; coord.y < size.size_y; coord.y++) {
      out << coord.y << "|";
      for (coord.x = 0; coord.x < size.size_x; coord.x++) {
        if (pattern[coord.x][coord.y].color == green) {
          out << "\033[1;32m" << pattern[coord.x][coord.y].status << "\033[0m" << " ";
        }
        else if (pattern[coord.x][coord.y].color == red) {
          out << "\033[1;31m" << pattern[coord.x][coord.y].status << "\033[0m" << " ";
        }
        else out << pattern[coord.x][coord.y].status << " ";
      }
      out << "|" << std::endl;
    }

    out << " +";
    for(int i = 0; i < size.size_x; i++)
      out << "- ";
    out << "+";
    out << std::endl;
    out << std::endl;
  }

  //----------------------------------------------

 Object* check_object(const Coordinates& coord, const std::string army_color) {
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
  for (auto const &obj: first_army) {
    if (obj->get_hp() <= 0) {
      delete_object(green, obj->get_id());
    }
  }
  for (auto const &obj: second_army) {
    if (obj->get_hp() <= 0) {
      delete_object(red, obj->get_id());
    }
  }
}
//---------------------------------------------------
void check_coords_update(Object* obj) {
  //проверка на выход за пределы поля
  if (obj->get_coord().x < 0) obj->get_coord().x = 0;
  else if (obj->get_coord().x >= size.size_x) obj->get_coord().x = size.size_x - 1;
  else if (obj->get_coord().y < 0) obj->get_coord().y = 0;
  else if (obj->get_coord().y >= size.size_x) obj->get_coord().y = size.size_y - 1;
}

//---------------------------------------------------
//---------------------------------------------------
void fight(Object* cur_obj, const std::string cur_color) {
  std::vector<Coordinates> attacked_coords = cur_obj->attack();
  std::string attacked_army_color; //цвет армии, которую атаковать потивоположен текущему
  if (cur_color == "green") attacked_army_color = "red";
  else attacked_army_color = "green";

  std::vector<Object*> remem_building;
      for (auto const& coord: attacked_coords) {
        Object* obj = check_object(coord, attacked_army_color);
        if (obj->get_type() == 'b') {
          bool already_seen = false;
          for (auto const& elem: remem_building) {
            if (elem == obj) {
              already_seen = true;
              break;
            }
          }
          if (already_seen == false) {
            obj->damage(cur_obj->get_force());
            remem_building.push_back(obj);
          }
          else already_seen = false;
        }
        else {
          obj->damage(cur_obj->get_force());
        }
      }
}
//---------------------------------------------------

Color winner(){
  //определяет победителя
  if (first_crown.expired()) {
    std::cout << "Red army won!" << std::endl;
    return red;
  } //если на корону зеленых ничего не указывает, выигрывают красные
  else if (second_crown.expired()) {
    std::cout << "Green army won!" << std::endl;
    return green; //и наоборот
  }
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

void read_coordinates(std::istream& in) {
  in >> size.size_x >> size.size_y;
}

};

//---------------------------------------------------

std::ostream& operator<<(std::ostream& out, Battlefield& field) {
  field.print_field(out);
  return out;
}

//----------------------------------------------

std::istream& operator>>(std::istream& in, Battlefield& field) {
  //in >> field.get_size().size_x >> field.get_size().size_y;
  field.read_coordinates(in);
  return in;
}

#endif
