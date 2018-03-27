#pragma once
#include <iostream>
#include <cstddef>
using namespace std;
struct Position{
    size_t x; //ось х
    size_t y; //ось y
    Position(){}
    Position(size_t arg_x, size_t arg_y) : x(arg_x), y(arg_y){}
    Position(Position const &crd){//создаем объект типа Position
        x = crd.x;
        y = crd.y;
    }
    Position (Position&& crd) : x(move(crd.x))
                                  , y(move(crd.y)){}

    Position &operator=(const Position &crd){
        if (this != &crd) {
            x = crd.x;
            y = crd.y;
        }
        return *this;
    }
    Position& operator=(Position&& crd){
         x = move(crd.x);
         y = move(crd.y);
         return *this;
    }
};

class Object {
private:
    Position coords;//координаты объекта
    int hit_points; //hp объекта
    size_t position; // индекс в списке
public:
   Object(){}
    Object(size_t arg_x, size_t arg_y, int hp = 100, size_t pos = 0) 
                : coords(arg_x, arg_y), hit_points(hp), position(pos){
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y <<endl
                  << "\thp = " << hit_points << endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" <<endl <<endl;
    }
    ~Object(){
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                 << "\033[1;31m ~Object() \033[0m" <<endl <<endl;
   }
   Object(Object const &obj){
        coords = obj.get_coords();
        hit_points = obj.get_hp();
        position = obj.get_position();
        cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                  << "\033[1;32m Object(Object const &) \033[0m" << endl << endl;
    }
    Object(Object&& obj) : coords(move(obj.get_coords())),
                hit_points(move(obj.get_hp())), position(move(obj.get_position())) {
                            cout << "\tx = " << coords.x << endl
                                      << "\ty = " << coords.y << endl
                                      << "\thp = " << hit_points << endl
                                      << "\033[1;32m Object(Object &&) \033[0m" << endl << endl;
             }


    Object &operator=  (Object &obj){
        if(this != &obj)
        {
            coords = obj.get_coords();
            hit_points = obj.get_hp();
            position = obj.get_position();
        }
        return *this;
    }
	
    Object &operator=  (Object&& obj){
         coords = move(obj.get_coords());
         hit_points = move(obj.get_hp());
         position = move(obj.get_position());
         return *this;
    }
    

	bool    operator== (Object const &obj){
        return (obj.coords.x == coords.x && obj.coords.y == coords.y);
    	}

    void get_Damag(size_t const &dmg);
    int &get_hp()                 
	{ 
		return hit_points; 
	}
    const int &get_hp()const            
	{ 
		return hit_points; 
	}
    Position &get_coords()             
	{ 
		return coords; 
	}
    const Position &get_coords() const       
	{ 
		return coords; 
	}
    size_t &get_position()           
	{
		return position;
        }
    const size_t &get_position() const     
	{
		 return position; 
	}

    Object* check_Coords(Position const &);
};

Object* Object::check_Coords(Position const &crds){
    if(coords.x == crds.x && coords.y == crds.y)
        return this;
    else
        return nullptr;
};

void Object::get_Damag(size_t const &dmg){
    get_hp() -= dmg;
}

