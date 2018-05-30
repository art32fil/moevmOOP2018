#pragma once
#include <memory>
#include "Crown.hpp"
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

	friend ostream &operator<<(ostream &out, const Position &coords);
	friend istream &operator>> (istream &in, Position &coords);

};

ostream &operator<< (ostream &out, const Position &coords){
     out << coords.x << coords.y;
    return out;
}

istream &operator>> (istream &in, Position &coords){
    in >> coords.x >> coords.y;
    return in;
}

bool operator== (Position const a, Position const b)
	{return(a.x == b.x && a.y == b.y);}

class Object {
private:
    const size_t ID;
    static size_t count;
    static size_t amount;
protected:
	Object *check_Coords(Position const &);
	Position coords;//координаты объекта
    	int hit_points; //hp объекта
    	const shared_ptr <Crown> crown; // корона
public:
   Object():ID(count++){amount++;}
    Object(const shared_ptr<Crown>& _crown) :ID(count++), crown(_crown){
        cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                  << "\tcrown = " << crown->get_color() << endl
                  << "\tID = " << ID << endl
                  << "\tcount = " << count << endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << endl << endl;
        amount++;
    }

	Object(size_t arg_x, size_t arg_y, int hp = 100)
                : ID(count++), hit_points(hp), coords(arg_x, arg_y){
        std::cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
                  << "\tcrown = " << crown->get_color() << endl
                  << "\tID = " << ID << endl
                  << "\tcount = " << count << endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << endl << endl;
        amount++;
    }

    Object(size_t arg_x, size_t arg_y, const shared_ptr<Crown> m_crown, int hp = 100) 
                : coords(arg_x, arg_y), hit_points(hp),crown(m_crown), ID(count++){
	    cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y <<endl
                  << "\thp = " << hit_points << endl
		  << "\tcrown = " << crown->get_color() << endl
		  << "\tID = " << ID << endl
		  << "\tcount = " << count << endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" <<endl <<endl;
		  amount++;
    }
   virtual ~Object(){
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
		  << "\tID = " << ID << endl
		  << "\tcount = " << count << endl
                 << "\033[1;31m ~Object() \033[0m" <<endl <<endl;
		 amount--;
   }

	bool operator== (Object* const &obj)
	{ return ((*obj).coords == coords && (*obj).coords == coords);}

 /*  Object(Object const &obj): ID(count++), crown(obj.crown){
        coords = obj.get_coords();
        hit_points = obj.get_hp();
        //position = obj.get_position();
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
		  << "\tcrown = " << crown->get_color() << endl
		  << "\tID = " << ID << endl
		  << "\tcount = " << count << endl
                  << "\033[1;32m Object(Object const &) \033[0m" << endl << endl;
		  amount++;
    }
    Object(Object&& obj) : coords(move(obj.get_coords())),
                hit_points(move(obj.get_hp())), ID(move(obj.get_ID())), crown(move(obj.crown)) {
             cout << "\tx = " << coords.x << endl
                  << "\ty = " << coords.y << endl
                  << "\thp = " << hit_points << endl
		  << "\tcrown = " << crown->get_color() << endl
		  << "\tID = " << ID << endl
		  << "\tcount = " << count << endl
                  << "\033[1;32m Object(Object &&) \033[0m" << endl << endl;
		  amount++;
             }


    Object &operator=  (Object &obj){
        if(this != &obj)
        {
            coords = obj.get_coords();
            hit_points = obj.get_hp();            
        }
        return *this;
    }
	
    Object &operator=  (Object&& obj){
         coords = move(obj.get_coords());
         hit_points = move(obj.get_hp());
         return *this;
    }*/
    

	

    void get_Damage(size_t const &dmg);
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
    const size_t &get_ID() const 
	{
		return ID;
	}
	const shared_ptr<Crown> &get_crown()const   { return crown; }
     virtual char type(){
        return 'o';
    }

   // Object* check_Coords(Position const &);
    friend ostream &operator<< (ostream &out, const Object &obj);
    friend istream &operator>>(istream &in, Object &obj);
};

ostream &operator<< (ostream &out, const Object &obj)
{
	out << obj.get_coords().x << obj.get_coords().y << obj.get_hp();
	return out;
}

istream &operator>>(istream &in, Object &obj)
{
	in >> obj.get_coords().x >> obj.get_coords().y >> obj.get_hp();
	return in;
}

Object* Object::check_Coords(Position const &crds){
    if(coords == crds)
        return this;
    else
        return nullptr;
};

void Object::get_Damage(size_t const &dmg){
    get_hp() -= dmg;
}

