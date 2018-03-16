#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP
#include "../my_vector/my_vector.hpp"
#include "../my_vector/iterator.hpp"
#include "Object.hpp"
#include <iostream>
#include <fstream>
#include  <utility>

struct Elem_for_print{
        bool colour; //true == green; false == red
        char l_d_e; //live_or_die_or_exist
        Elem_for_print(char lde = '.') : l_d_e(lde){}
};

struct Size{
    size_t x_size;
    size_t y_size;
    Size(size_t arg_x, size_t arg_y) : x_size(arg_x), y_size(arg_y){}
    Size(){}
};

class Battlefield {
    friend class Object;
    Size size;
    List<Object> red_army;
    List<Object> green_army;
public:
    Size         &get_size(){ return size; }
    //List<Object> &get_army_RED(){ return red_army; }
    //List<Object> &get_army_RED(){ return green_army; }
    Battlefield(){
        std::cout << "\tx = " << size.x_size << std::endl
                  << "\ty = " << size.y_size << std::endl
                  << "Battlefield()" << std::endl << std::endl;
    }
    Battlefield(size_t arg_x, size_t arg_y) : size(arg_x, arg_y){
        std::cout << "\tx = " << size.x_size << std::endl
                  << "\ty = " << size.y_size << std::endl
                  << "Battlefield(size_t, size_t)" << std::endl << std::endl;
    }
    ~Battlefield (){
        std::cout << "\tx = " << size.x_size << std::endl
                  << "\ty = " << size.y_size << std::endl
                  << "~Battlefield()" << std::endl << std::endl;
    }
    void Draw_battlefield();
    void Enter(ifstream &);
    std::pair<int, Object&> check_colour_of_army_on_postion(Object &arm);// How to do const??
};

istream &operator>> (ifstream &fin, Object &obj){
    fin >> obj.get_coords().axis_x >> obj.get_coords().axis_y >> obj.get_hp();
    return fin;
}

istream &operator>> (ifstream &fin, Size &sz){
    fin >> sz.x_size >> sz.y_size;
    return fin;
}


void Battlefield::Draw_battlefield(){
    Elem_for_print *arr = new Elem_for_print[size.x_size*size.y_size];
    for(auto &obj : red_army){
        arr[obj.get_Info().get_coords().axis_x +
                obj.get_Info().get_coords().axis_y*size.y_size].l_d_e = 'o';
        arr[obj.get_Info().get_coords().axis_x +
                obj.get_Info().get_coords().axis_y*size.y_size].colour = false;
    }
    for(auto &obj : green_army){
        arr[obj.get_Info().get_coords().axis_x +
                obj.get_Info().get_coords().axis_y*size.y_size].l_d_e = 'o';
        arr[obj.get_Info().get_coords().axis_x +
                obj.get_Info().get_coords().axis_y*size.y_size].colour = true;
    }
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
                cout << "\033[1;32m o\033[0m"; //green
            else
                cout << "\033[1;31m o\033[0m";
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

void Battlefield::Enter(ifstream &fin){
    size_t q = 0;
    Object obj;
    fin >> size;

    fin >> q;

    for (size_t i = 0; i < q; i++) {
        fin >> obj;
        red_army.Add_to_Head(obj);
    }

    fin >> q;
    for (size_t i = 0; i < q; i++) {
        fin >> obj;
        green_army.Add_to_Head(obj);
    }

}

std::pair<int, Object&> Battlefield::check_colour_of_army_on_postion(Object &arm){ // How to do const??
        std::pair<int, Object&> a(3, arm);
        for(auto &obj: this->red_army)
            if(arm == obj.get_Info()){
                a = {1, obj.get_Info()};
                return a/*(1, obj.get_Info())*/;
            }

        for(auto &obj: this->green_army)
            if(arm == obj.get_Info()){
                a = {2, obj.get_Info()};
                return a;
            }
        return a;
}

#endif //BATTLEFIELD_HPP
