#pragma once
#include "list.hpp"
#include "iterator.hpp"
#include "Object.hpp"
#include <iostream>
#include <fstream>
#include  <utility>
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
    List<Object> red_army; //армия красных
    List<Object> green_army;//армия зеленых
public:
    const Size         &get_size()    const { return size; }       //возвращает размер поля
    const List<Object> &get_red_arm() const { return red_army; }   //возвращает красную армию
    const List<Object> &get_gr_arm()  const { return green_army; } //возвращает зеленую армию
    List<Object>       &get_red_arm()       { return red_army; }   //возвращает красную армию
    List<Object>       &get_gr_arm()        { return green_army; } //возвращает зеленую армию
    Battlefield(){}
    Battlefield(size_t arg_x, size_t arg_y) : size(arg_x, arg_y){
        cout << "\tx = " << size.x_size << endl
                  << "\ty = " << size.y_size << endl
                  << "\033[1;32m Battlefield(size_t, size_t) \033[0m" << endl << endl << endl;
    }
    ~Battlefield (){
        cout << "\tx = " << size.x_size << endl
                  << "\ty = " << size.y_size << endl
                  << "\033[1;31m ~Battlefield() \033[0m" << endl << endl << endl;
    }

    void Draw_battlefield(); //функция для отрисовки поля
    void Enter(ifstream &);  //ввод из файла
   // size_t find_pos(size_t const &pos); //находит позицию на поле
    pair<int, Object&> check_colour_on_postion(Object &arm);//проверяет цвет армии на данной позиции
};

ifstream &operator>> (ifstream &fin, Size &sz){
    fin >> sz.x_size >> sz.y_size;
    return fin;
}

ifstream &operator>> (ifstream &fin, Object &obj){
    fin >> obj.get_coords().x >> obj.get_coords().y >> obj.get_hp();
    return fin;
}


void Battlefield::Draw_battlefield(){
    Elem_for_print *arr = new Elem_for_print[size.x_size*size.y_size];//создает массив, который используется для отрисовки поля 
    for(auto &obj : red_army){ //для красной армии
        if (obj.get_Info().get_hp() <= 0) {//если здоровье объекта <= 0
            arr[obj.get_Info().get_coords().x +
                    obj.get_Info().get_coords().y*size.y_size].l_d_e = 'X';//записывает в соответственную ячейку 'x'
       }else{
            arr[obj.get_Info().get_coords().x +
                    obj.get_Info().get_coords().y*size.y_size].l_d_e = 'O';//если hp>0 записывает в соответственную ячейку 'o'
            }
        arr[obj.get_Info().get_coords().x +
                obj.get_Info().get_coords().y*size.y_size].colour = false;
    }
    for(auto &obj : green_army){
        if(obj.get_Info().get_hp() <= 0){					//то же самое 
            arr[obj.get_Info().get_coords().x +   				//только 
                    obj.get_Info().get_coords().y*size.y_size].l_d_e = 'X';	//для 	
        }else{									//зеленой армии
            arr[obj.get_Info().get_coords().x +					//
                    obj.get_Info().get_coords().y*size.y_size].l_d_e = 'O';	//
        }
       arr[obj.get_Info().get_coords().x +
                obj.get_Info().get_coords().y*size.y_size].colour = true;
    }
    cout << '\n';
    cout << "   ";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << i << ' ';
    }
    cout << "\n *";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << "**";
    }
    cout << "**\n";
    for (size_t i = 0; i < size.y_size; i++) {
        cout << i << '|';
        for (size_t j = 0; j < size.x_size; j++) {
            if( arr[i*size.x_size + j].l_d_e == '.')
                cout << ' ' << arr[i*size.x_size + j].l_d_e ;
            else if(arr[i*size.x_size + j].colour)
                cout << "\033[1;32m " << arr[i*size.x_size + j].l_d_e << "\033[0m"; //green
            else
                cout << "\033[1;31m " << arr[i*size.x_size + j].l_d_e << "\033[0m";
        }
        cout << " |\n";
    }
    cout << " *";
    for (size_t i = 0; i < size.x_size; i++) {
        cout << "**";
    }
    cout << "**\n";
    delete []arr;
}

void Battlefield::Enter(ifstream &fin){ //ввод из файла
    size_t q = 0; 
    Object obj;
    fin >> size;
    fin >> q;

    for (size_t i = 0; i < q; i++) {
        fin >> obj;
        obj.get_position() = i; //располагаем считываемый объект на i=ой позиции
        red_army.Add_to_Head(obj);//добавляет объект в красную армию
    }

    fin >> q;
    for (size_t i = 0; i < q; i++) {
        fin >> obj;
        obj.get_position() = i;
        green_army.Add_to_Head(obj);
    }

    cout << '\n'<< "it's interim object : ";
    cout << '\n';
}

pair<int, Object&> Battlefield::check_colour_on_postion(Object &arm){ //1 - красная армия, 2 - зеленеая
        for(auto &obj: this->red_army)
            if(arm == obj.get_Info())
                return {1, obj.get_Info()};

        for(auto &obj: this->green_army)
            if(arm == obj.get_Info())
                return {2, obj.get_Info()};

        return {3, arm};
}

