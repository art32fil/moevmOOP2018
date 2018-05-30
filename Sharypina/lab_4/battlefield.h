#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <vector>
#include <memory>
#include "warrior.h"
#include "building.h"
#include "swordsman.h"
#include "magician.h"
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
      case 'w': { //считываем воина
        int force;
        fin >> coords >> hp >> force;;

        Warrior* war = new Warrior(coords, hp, crown, force);
        army.add_tail(war);
        break;
      }
      case 'b': { //считываем здание
        int num_extra; //количество дополнительных координат
        std::vector<Coordinates> extra_coords;
        Coordinates cur_extra; //координаты, считываемые в данный момент
        char war_type;
        fin >> coords >> hp >> num_extra;
        extra_coords.push_back(coords);
        for (int i = 0; i < num_extra; i++) {
          fin >> cur_extra;
          extra_coords.push_back(cur_extra);
        }
        fin >> war_type; //тип объектов, которые порождаются зданием
        if (war_type == 'w') {
          Building<Warrior>* build = new Building<Warrior>(coords, hp, crown, extra_coords);
          army.add_tail(build);
        }
        else if (war_type == 's') {
          Building<Swordsman>* build = new Building<Swordsman>(coords, hp, crown, extra_coords);
          army.add_tail(build);
        }
        else if (war_type == 'm') {
          Building<Magician>* build = new Building<Magician>(coords, hp, crown, extra_coords);
          army.add_tail(build);
        }
        break;
        }
        case 's': { //считываем мечника
          int force;
          fin >> coords >> hp >> force;

          Swordsman* swrd = new Swordsman(coords, hp, crown, force);
          army.add_tail(swrd);
          break;
        }
        case 'm': { //считываем мага
          int force, range;
          fin >> coords >> hp >> force >> range;

          Magician* mag = new Magician(coords, hp, crown, force, range);
          army.add_tail(mag);
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

  void clear_pattern() { //очищает шаблон - поле
    for (int i = 0; i < size.size_x; i++) {
      for (int j = 0; j < size.size_y; j++) {
        pattern[i][j].status = '.';
        pattern[i][j].color = white;
      }
    }
  }

//----------------------------------------------

  void update_pattern() { //обновляет шаблон - поле для вывода в консоль
    clear_pattern();
    for (auto &obj: first_army) {
      char type = obj->get_type();
      if (type != 'b') {
        pattern[obj->get_coord().x][obj->get_coord().y].color = green;
        pattern[obj->get_coord().x][obj->get_coord().y].status = type;
      }
      else if (type == 'b') {
        std::vector<Coordinates> coords = obj->get_extra_coords();
        for (auto const& coord: coords) {
          pattern[coord.x][coord.y].color = green;
          pattern[coord.x][coord.y].status = type;
        }
      }
    }
    for (auto &obj: second_army) {
      char type = obj->get_type();
      if (type != 'b') {
        pattern[obj->get_coord().x][obj->get_coord().y].color = red;
        pattern[obj->get_coord().x][obj->get_coord().y].status = type;
      }
      else if (type == 'b') {
        std::vector<Coordinates> coords = obj->get_extra_coords();
        for (auto const& coord: coords) {
          pattern[coord.x][coord.y].color = red;
          pattern[coord.x][coord.y].status = type;
        }
      }
    }
  }

  //----------------------------------------------

  void print_field(std::ostream& out) { //печатает поле
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
  Object* check_object(const Coordinates& coord, const std::string army_color, const char type) {
  //перегрузка
  //проверка на принадлежность объекта типа type с координатами coord армии цвета attacked_army_color
  //если такой объект есть, возвращает указатель на него
  //иначе возвращает nullptr
    Object* cur;
    if(coord.x < 0 || coord.x >= size.size_x ||coord.y < 0 ||coord.y >= size.size_y) {
   //  pos = -1; //если выходит за предлы поля боя
     return nullptr;
   }
   if (army_color == "green") {
     for(auto &obj: first_army) {
       cur = obj->check_position(coord);
       if (cur) {
         if (cur->get_type() == type) return cur;
       }
     }
   }
   else if (army_color == "red") {
     for (auto &obj: second_army) {
       cur = obj->check_position(coord);
       if (cur) {
         if (cur->get_type() == type) return cur;
       }
     }
   }
   return nullptr;
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

  void delete_object(int army, int id) { //удаляет объект армии по id
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

void check_hp() { //убираем с поля убитых с hp <= 0
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

void check_coords_update(Object* obj) { //проверка на выход за пределы поля
  if (obj->get_coord().x < 0) obj->get_coord().x = 0;
  else if (obj->get_coord().x >= size.size_x) obj->get_coord().x = size.size_x - 1;
  else if (obj->get_coord().y < 0) obj->get_coord().y = 0;
  else if (obj->get_coord().y >= size.size_x) obj->get_coord().y = size.size_y - 1;
}

//---------------------------------------------------
//воин атакует того, с кем совпадает по координатам
//мечнник атакует самого слабого на соседней клетке
//маг атакует и самого слабого на соседней клетке и по лучу
//---------------------------------------------------

void fight(Object* cur_obj, const std::string cur_color) {
  //атака объектом cur_obj цвета cur_color
  std::string attacked_army_color; //цвет армии, которую атаковать потивоположен текущему
  if (cur_color == "green") attacked_army_color = "red";
  else attacked_army_color = "green";


  if (cur_obj->get_type() == 'm') { //только маг может атаковать по лучу
    int degrees; //угол, под которым произойдет удар
    std::cin >> degrees;
    attack_coordinates(attacked_army_color, cur_obj->attack(degrees), cur_obj->get_force());
    check_hp(); //проверяем, есть ли убитые
  }

  //далее для любого объекта типа воина выполняется атака самого слабого
  attack_weakest_object(attacked_army_color, cur_obj->attack(), cur_obj->get_force());
  check_hp(); //проверяем, есть ли убитые
}

//---------------------------------------------------
//атака самого слабого на соседней клетке
//если несколько с минимальным hp: как найти?
//пробегаемся п//проверка на принадлежность объекта с координатами coord армии цвета army_color
//возвращает указатель на этот объект, если он есть в данной армии
//иначе - возвращает nullptr
//сравниваем с минимальным hp
//если такое же хп, то закидываем в вектор
//если меньше, то очищаем вектор и закидываем новый объект.
//---------------------------------------------------

void attack_weakest_object(const std::string attacked_army_color, const std::vector<Coordinates> attacked_coords, int damage) {
  //атакуем самый слабый объект, находящийся рядом
  std::cout << "attack_weak" << std::endl;
  std::vector <Object*> weakest_obj; //нужно определить самого слабого на соседних клетках
  int lowest_hp = 100; //изначально самое маленькое hp = максимально возможному

    for (auto const& coord: attacked_coords) { //ищем слабых
      Object* obj = check_object(coord, attacked_army_color);
      if (obj) { //если объект есть на атакуемых координатах
        int obj_hp = obj->get_hp();
        if (obj_hp < lowest_hp) { //если встретился более слабый
          lowest_hp = obj_hp;
          weakest_obj.clear();
          weakest_obj.push_back(obj);
        }
        else if (obj_hp == lowest_hp) { //если встретился с там же низким hp
          weakest_obj.push_back(obj);
        }
      }
    }
    //слабый должен умереть
    for (auto& obj: weakest_obj) {
      obj->damage(damage);
    }
}

//---------------------------------------------------

void attack_coordinates(const std::string attacked_army_color, const std::vector<Coordinates> attacked_coords, int damage) {
  //атака по набору координат, находящихся под боем
  //анализирует, на каких координатах противник
  std::cout << "attack_coords" << std::endl;
  for (auto const& coord: attacked_coords) {
    Object* obj = check_object(coord, attacked_army_color);
    if (obj) { //если объект есть на атакуемых координатах
      obj->damage(damage);
    }
  }
}

//---------------------------------------------------

Color winner(){
  //определяет победителя
  if (first_crown.expired()) {
    std::cout << "Red army won !!" << std::endl;
    return red;
  } //если на корону зеленых ничего не указывает, выигрывают красные
  else if (second_crown.expired()) {
    std::cout << "Green army won !!" << std::endl;
    return green; //и наоборот
  }
  else return white; //обе короны живы, пока ничья
}

//---------------------------------------------------

void delete_everything() { //заканчивает игру, освобождает память
  for (auto& obj: first_army) {
    delete obj;
  }
  for (auto& obj: second_army) {
    delete obj;
  }
}

//---------------------------------------------------

void read_coordinates(std::istream& in) { //считывание координат
  in >> size.size_x >> size.size_y;
}

//---------------------------------------------------

void add_new_object(Object* obj, std::string color) {
//добавление нового объекта при порождении зданием
  if (color == "green") {
    first_army.add_tail(obj);
  }
  else {
    second_army.add_tail(obj);
  }
}

};

//---------------------------------------------------

std::ostream& operator<<(std::ostream& out, Battlefield& field) {
  field.print_field(out);
  return out;
}

//----------------------------------------------

std::istream& operator>>(std::istream& in, Battlefield& field) {
  field.read_coordinates(in);
  return in;
}

#endif
