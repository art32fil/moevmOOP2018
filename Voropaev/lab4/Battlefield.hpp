#pragma once
#include "list.hpp"
#include "iterator.hpp"
#include "Object.hpp"
#include "Crown.hpp"
#include "Warrior.hpp"
#include "Building.hpp"
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include  <utility>
#include <typeinfo>
using namespace std;
struct Elem_for_print{
        bool colour; //true == green; false == red
        char l_d_e; //live_or_die_or_exist
        Elem_for_print(char lde = '.') : l_d_e(lde){} //создаем элемент
};

struct Size{
    size_t x_size;
    size_t y_size;
    Size(size_t arg_x, size_t arg_y) : x_size(arg_x), y_size(arg_y){
        cout << "\tx = " << x_size << endl
                  << "\ty = " << y_size << endl
                  << "\033[1;32m Size() \033[0m" << endl << endl << endl;
    }
    Size(){ }
};

class Battlefield {
    friend class Object;//делаем Object дружественным классом
    Size size; 
    List<Object*> red_army; //армия красных
    weak_ptr<Crown> crown_red;
    List<Object*> green_army;//армия зеленых
    weak_ptr<Crown> crown_green;
    List<Warrior*> warrior_red;
    List<Warrior*> warrior_green;
    List<Building*> building_red;
    List<Building*> building_green;
public:
    const Size         &get_size()    const { return size; }       //возвращает размер поля
    //const List<Object> &get_red_arm() const { return red_army; }   //возвращает красную армию
   // const List<Object> &get_gr_arm()  const { return green_army; } //возвращает зеленую армию
   // List<Object>       &get_red_arm()       { return red_army; }   //возвращает красную армию
   // List<Object>       &get_gr_arm()        { return green_army; } //возвращает зеленую армию
	const List<Warrior*> &get_red_warr() const { return warrior_red;   }
    const List<Warrior*> &get_gr_warr()  const { return warrior_green; }
    List<Warrior*>       &get_red_warr()       { return warrior_red;   }
    List<Warrior*>       &get_gr_warr()        { return warrior_green; }

    const List<Building*> &get_red_build() const { return building_red;   }
    const List<Building*> &get_gr_build()  const { return building_green; }
    List<Building*>       &get_red_build()       { return building_red;   }
    List<Building*>       &get_gr_build()        { return building_green; }

    Battlefield(){}
    Battlefield(size_t arg_x, size_t arg_y) : size(arg_x, arg_y){
        cout << "\tx = " << size.x_size << endl
                  << "\ty = " << size.y_size << endl
                  << "\033[1;32m Battlefield(size_t, size_t) \033[0m" << endl << endl << endl;
    }
    ~Battlefield (){
		for(auto &elem: warrior_red){
            delete elem.get_Info();
            elem.get_Info() = nullptr;
        }
        for(auto &elem : warrior_green){
            delete elem.get_Info();
            elem.get_Info() = nullptr;
        }
        for(auto &elem : building_red){
            delete elem.get_Info();
            elem.get_Info() = nullptr;
        }
        for(auto &elem : building_green){
            delete elem.get_Info();
            elem.get_Info() = nullptr;
        }
        cout << "\tx = " << size.x_size << endl
                  << "\ty = " << size.y_size << endl
                  << "\033[1;31m ~Battlefield() \033[0m" << endl << endl << endl;
    }

    void Draw_battlefield(); //функция для отрисовки поля
    void Enter(ifstream &in);  //ввод из файла
    size_t find_pos(size_t const &pos); //находит позицию на поле
    pair<int, Object*> check_colour_on_postion(Object *arm);//проверяет цвет армии на данной позиции
	pair<int, Warrior*> check_colour_on_position(Warrior *arm);
	Object *check_position(Object*);
};

ifstream &operator>> (ifstream &fin, Size &sz){
    fin >> sz.x_size >> sz.y_size;
    return fin;
}

/*ifstream &operator>> (ifstream &fin, Object &obj){
    fin >> obj.get_coords().x >> obj.get_coords().y >> obj.get_hp();
    return fin;
}*/
template <typename T>
void fld(List<T*> &army, Elem_for_print *&arr, bool clr, Size const &size) {
    for(auto &obj : army){
         T *elem = obj.get_Info();
        if ( elem->get_hp() <= 0) {
            arr[ elem->get_coords().x +
                    elem->get_coords().y*size.y_size].l_d_e = 'x';
        }else{
            arr[ elem->get_coords().x +
                    elem->get_coords().y*size.y_size].l_d_e = elem->type();
            }
        arr[elem->get_coords().x +
                elem->get_coords().y*size.y_size].colour = clr;
    }
}

template <typename T>
void fld_build(List<T*> &army, Elem_for_print *&arr, bool clr, Size const &size) {
    for(auto &obj : army){
         T *elem = obj.get_Info();
        if ( elem->get_hp() <= 0){
            for(auto &build : elem->get_building())
                arr[ build.x +
                    build.y*size.y_size].l_d_e = 'x';
        }else{
            for(auto &build : elem->get_building())
                arr[ build.x +
                    build.y*size.y_size].l_d_e = elem->type();
            }
        for(auto &build : elem->get_building())
            arr[build.x +
                build.y*size.y_size].colour = clr;
    }
}

void Battlefield::Draw_battlefield(){
    Elem_for_print *arr = new Elem_for_print[size.x_size*size.y_size];

    // fld<Object>(red_army, arr, false, size);
    // fld<Object>(green_army, arr, true, size);
    fld<Building>(building_red, arr, false, size);
    fld<Building>(building_green, arr, true, size);
    fld_build<Building>(building_red, arr, false, size);
    fld_build<Building>(building_green, arr, true, size);
    fld<Warrior>(warrior_red, arr, false, size);
    fld<Warrior>(warrior_green, arr, true, size);

    cout << '\n';
    cout << "   ";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << i << ' ';
    }
    cout << "\n +";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << "--";
    }
    cout << "-+\n";
    for (size_t i = 0; i < size.y_size; i++) {
        cout << i << '|';
        for (size_t j = 0; j < size.x_size; j++) {
            if( arr[i*size.x_size + j].l_d_e == '.')
                cout << ' ' << arr[i*size.x_size + j].l_d_e ;
            else if(arr[i*size.x_size + j].colour)
                cout << "\033[1;32m " << arr[i*size.x_size + j].l_d_e << "\033[0m";
            else
                cout << "\033[1;31m " << arr[i*size.x_size + j].l_d_e << "\033[0m";
        }
        cout << " |\n";
    }
    cout << " +";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << "--";
    }
    cout << "-+\n";
    delete []arr;
}

template <typename T>
void read(istream &in, string type, List<T*> &army, shared_ptr<Crown> &crown){
    size_t q = 0;
    string str;
    in >> str;
    if(str == type){
        in >> q;
        T *obj;
        for (size_t i = 0; i < q; i++) {
            obj = new T(crown);
            in >> *obj;
            army.Add_to_Head(obj);
        }
    }
}

void Battlefield::Enter(ifstream &fin){ //ввод из файла
    string str;
    shared_ptr<Crown> cr_r(new Crown("red"));
    crown_red = cr_r;
    shared_ptr<Crown> cr_gr(new Crown("green"));
    crown_green = cr_gr;

    fin >> str;
    if(str == "field")
        fin >> size;
    str.clear();
//---------------------------------------
    // read<Object>(fin, "Object-red", red_army, cr_r);
    // read<Object>(fin, "Object-green", green_army, cr_gr);

    read<Warrior>(fin, "Warrior-red", warrior_red, cr_r);
    read<Warrior>(fin, "Warrior-green", warrior_green, cr_gr);

    read<Building>(fin, "Building-red", building_red, cr_r);
    read<Building>(fin, "Building-green", building_green, cr_gr);

    // cout << '\n'<< "Destroying interim object from Enter : ";
    cout << '\n';
}

pair<int, Object*> Battlefield::check_colour_on_postion(Object *arm){ //1 - красная армия, 2 - зеленеая
        for(auto &obj: this->red_army)
            if(arm == obj.get_Info())
                return {1, obj.get_Info()};

        for(auto &obj: this->green_army)
            if(arm == obj.get_Info())
                return {2, obj.get_Info()};

        return {3, arm};
}

bool operator== (vector<Position> const v, Position const tmp){
    for(auto &el : v)
        if(el == tmp)
            return true;
    return false;
}

pair<int, Warrior*> Battlefield::check_colour_on_position(Warrior *arm){
        for(auto &obj: this->warrior_red){
            //cout << obj.get_Info()->get_coords() << '\n';
            if(arm->get_coords() == obj.get_Info()->get_coords())
                return {1, obj.get_Info()};
            }

        for(auto &obj: this->warrior_green)
            if(arm->get_coords() == obj.get_Info()->get_coords())
                return {2, obj.get_Info()};

        return {3, arm};
}

Object* Battlefield::check_position(Object* arm){
    if(arm->get_crown()->get_color() == "green"){
        for(auto &obj: this->warrior_red)
            if(arm->get_coords() == obj.get_Info()->get_coords())
                return obj.get_Info();
        for(auto &obj: this->building_red)
            if(arm->get_coords() == obj.get_Info()->get_coords()
             || obj.get_Info()->get_building() == arm->get_coords())
                return obj.get_Info();
        }
    if(arm->get_crown()->get_color() == "red"){
        for(auto &obj: this->warrior_green)
            if(arm->get_coords() == obj.get_Info()->get_coords())
                return obj.get_Info();
        for(auto &obj: this->building_green)
            if(arm->get_coords() == obj.get_Info()->get_coords()
            || obj.get_Info()->get_building() == arm->get_coords())
                return obj.get_Info();
        }

        return nullptr;
}
