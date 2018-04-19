#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP
#include "../vector/my_vector.hpp"
#include "../vector/iterator.hpp"
#include "Object.hpp"
#include "Warrior.hpp"
#include "Building.hpp"
#include "Crown.hpp"
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <utility>

struct Elem_for_print{
        bool colour; //true == green; false == red
        char l_d_e; //live_or_die_or_exist
        Elem_for_print(char lde = '.') : l_d_e(lde){}
};

struct Size{
    size_t x_size;
    size_t y_size;
    Size(size_t arg_x, size_t arg_y) : x_size(arg_x), y_size(arg_y){
        std::cout << "\tx = " << x_size << std::endl
                  << "\ty = " << y_size << std::endl
                  << "\033[1;32m Size() \033[0m" << std::endl << std::endl << std::endl;
    }
    Size(){}
};

// template <typename T>
class Battlefield {
    friend class Object;
    Size size;

    std::weak_ptr<Crown> crown_red;
    std::weak_ptr<Crown> crown_green;

    List<Object*> red_army;
    List<Object*> green_army;

    List<Warrior*> warr_red_army;
    List<Warrior*> warr_green_army;

    List<Building*> build_red_army;
    List<Building*> build_green_army;

public:
    const Size          &get_size()    const { return size; }
    const List<Object*> &get_red_arm() const { return red_army; }
    const List<Object*> &get_gr_arm()  const { return green_army; }
    List<Object*>       &get_red_arm()       { return red_army; }
    List<Object*>       &get_gr_arm()        { return green_army; }

    Battlefield(){}
    Battlefield(size_t arg_x, size_t arg_y) : size(arg_x, arg_y){
        std::cout << "\tx = " << size.x_size << std::endl
                  << "\ty = " << size.y_size << std::endl
                  << "\033[1;32m Battlefield(size_t, size_t) \033[0m"
                  << std::endl << std::endl << std::endl;
    }
    ~Battlefield(){
        std::cout << "\tx = " << size.x_size << std::endl
                  << "\ty = " << size.y_size << std::endl
                  << "\033[1;31m ~Battlefield() \033[0m"
                  << std::endl << std::endl << std::endl;
    }

    void Draw_battlefield();
    void Enter(istream &in);
    size_t find_pos(size_t const &pos);
    std::pair<int, Object*> check_colour_on_postion(Object* arm);
};

istream &operator>> (istream &fin, Size &sz){ //read from file
    fin >> sz.x_size >> sz.y_size;
    return fin;
}

template <typename T>
void fld(List<T*> &army, Elem_for_print *&arr, bool clr, Size const &size) {
    for(auto &obj : army){
         T *elem = obj.get_Info();
        if ( elem->get_hp() <= 0) {
            arr[ elem->get_coords().axis_x +
                    elem->get_coords().axis_y*size.y_size].l_d_e = 'x';
        }else{
            arr[ elem->get_coords().axis_x +
                    elem->get_coords().axis_y*size.y_size].l_d_e = elem->type();
            }
        arr[elem->get_coords().axis_x +
                elem->get_coords().axis_y*size.y_size].colour = clr;
    }
}

template <typename T>
void fld_build(List<T*> &army, Elem_for_print *&arr, bool clr, Size const &size) {
    for(auto &obj : army){
         T *elem = obj.get_Info();
        std::cout << elem->get_hp() << '\n';
        if ( elem->get_hp() <= 0){
            for(auto &build : elem->get_building())
                arr[ build.axis_x +
                    build.axis_y*size.y_size].l_d_e = 'x';
        }else{
            for(auto &build : elem->get_building())
                arr[ build.axis_x +
                    build.axis_y*size.y_size].l_d_e = elem->type();
            }
        for(auto &build : elem->get_building())
            arr[build.axis_x +
                build.axis_y*size.y_size].colour = clr;
    }
}

void Battlefield::Draw_battlefield(){
    Elem_for_print *arr = new Elem_for_print[size.x_size*size.y_size];

    fld<Object>(red_army, arr, false, size);
    fld<Object>(green_army, arr, true, size);

    fld<Warrior>(warr_red_army, arr, false, size);
    fld<Warrior>(warr_green_army, arr, true, size);

    fld<Building>(build_red_army, arr, false, size);
    fld<Building>(build_green_army, arr, true, size);
    fld_build<Building>(build_red_army, arr, false, size);
    fld_build<Building>(build_green_army, arr, true, size);

    std::cout << '\n';
    std::cout << "   ";
    for (size_t i = 0; i < size.x_size; i++) {
        std::cout << i << ' ';
    }
    std::cout << "\n +";
    for (size_t i = 0; i < size.x_size; i++) {
        std::cout << "--";
    }
    std::cout << "-+\n";
    for (size_t i = 0; i < size.y_size; i++) {
        std::cout << i << '|';
        for (size_t j = 0; j < size.x_size; j++) {
            if( arr[i*size.x_size + j].l_d_e == '.')
                std::cout << ' ' << arr[i*size.x_size + j].l_d_e ;
            else if(arr[i*size.x_size + j].colour)
                cout << "\033[1;32m " << arr[i*size.x_size + j].l_d_e << "\033[0m"; //green
            else
                cout << "\033[1;31m " << arr[i*size.x_size + j].l_d_e << "\033[0m";
        }
        std::cout << " |\n";
    }
    std::cout << " +";
    for (size_t i = 0; i < size.x_size; i++) {
        std::cout << "--";
    }
    std::cout << "-+\n";
    delete []arr;
}

template <typename T>
void read(istream &in, string type, List<T*> &army, std::shared_ptr<Crown> &crown){
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

void Battlefield::Enter(istream &in){
    string str;
    std::shared_ptr<Crown> cr_r(new Crown("red"));
    crown_red = cr_r;
    std::shared_ptr<Crown> cr_gr(new Crown("green"));
    crown_green = cr_gr;

    in >> str;
    if(str == "field")
        in >> size;
    str.clear();
//---------------------------------------
    read<Object>(in, "Object-red", red_army, cr_r);
    read<Object>(in, "Object-green", green_army, cr_gr);

    read<Warrior>(in, "Warrior-red", warr_red_army, cr_r);
    read<Warrior>(in, "Warrior-green", warr_green_army, cr_gr);

    read<Building>(in, "Building-red", build_red_army, cr_r);
    read<Building>(in, "Building-green", build_green_army, cr_gr);

    // std::cout << '\n'<< "Destroing interim object from Enter : ";
    std::cout << '\n';
}

std::pair<int, Object*> Battlefield::check_colour_on_postion(Object* arm){
        for(auto &obj: this->red_army)
            if(arm == obj.get_Info())
                return {1, obj.get_Info()};

        for(auto &obj: this->green_army)
            if(arm == obj.get_Info())
                return {2, obj.get_Info()};

        return {3, arm};
}

// const string get_color(Object const &clr) const{
//     if(ob->first == 1){
//         return "red";
//     }
//     else if(ob->first ==  2)
//         return "green"
//     else if(ob->first == 3){
//         std::cout << "It is object don't belong any army!" << '\n';
//         break;
//     }
// }


#endif //BATTLEFIELD_HPP
