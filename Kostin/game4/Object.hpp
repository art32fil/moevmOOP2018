#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <iostream>
#include "Crown.hpp"

struct Coordinates{
    size_t axis_x;
    size_t axis_y;
    Coordinates(){}
    Coordinates(size_t arg_x, size_t arg_y) : axis_x(arg_x), axis_y(arg_y){}
    Coordinates(Coordinates const &crd){
        axis_x = crd.axis_x;
        axis_y = crd.axis_y;
    }
    Coordinates (Coordinates&& crd) : axis_x(std::move(crd.axis_x))
                                  , axis_y(std::move(crd.axis_y)){}

    Coordinates &operator=(const Coordinates &crd){
        if (this != &crd) {
            axis_x = crd.axis_x;
            axis_y = crd.axis_y;
        }
        return *this;
    }
    Coordinates& operator=(Coordinates&& crd){
         axis_x = std::move(crd.axis_x);
         axis_y = std::move(crd.axis_y);
         return *this;
    }

    friend std::ostream &operator<< (std::ostream &out, const Coordinates &coords);
    friend std::istream &operator>> (std::istream &in, Coordinates &coords);
};

bool operator== (Coordinates const a,Coordinates const b)
{
    return ( a.axis_x == b.axis_x && a.axis_y == b.axis_y);
}

std::ostream &operator<< (std::ostream &out, const Coordinates &coords){
     out << coords.axis_x << coords.axis_y;
    return out;
}

std::istream &operator>> (std::istream &in, Coordinates &coords){
    in >> coords.axis_x >> coords.axis_y;
    return in;
}

class Object {
private:
    const  size_t ID; // of Object in List
    static size_t count;
    static size_t amount;

protected:
    const std::shared_ptr<Crown> crown;
    int hit_points;
    Coordinates coords;
    Object* check_Coords(Coordinates const &);
public:
    Object() : ID(count++){
        amount++;
    }
    Object(const std::shared_ptr<Crown>& _crown) :ID(count++), crown(_crown){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tcrown = " << crown->get_color() << std::endl
                  << "\tID = " << ID << std::endl
                  << "\tcount = " << count << std::endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << std::endl << std::endl;
        amount++;
    }
    Object(size_t arg_x, size_t arg_y, int hp = 100)
                : ID(count++), hit_points(hp), coords(arg_x, arg_y){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tcrown = " << crown->get_color() << std::endl
                  << "\tID = " << ID << std::endl
                  << "\tcount = " << count << std::endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << std::endl << std::endl;
        amount++;
    }
    Object(size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown, int hp = 100 )
                : ID(count++), crown(_crown), hit_points(hp), coords(arg_x, arg_y){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tcrown = " << crown->get_color() << std::endl
                  << "\tID = " << ID << std::endl
                  << "\tcount = " << count << std::endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << std::endl << std::endl;
        amount++;
    }
    virtual ~Object(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tID = " << ID << std::endl
                  << "\tcount = " << count << std::endl
                  << "\033[1;31m ~Object() \033[0m" << std::endl << std::endl;
            amount--;
    }

    bool    operator== (Object* const &obj){
        return ((*obj).coords == coords && (*obj).coords == coords);
    }

    void              get_Damage(size_t const &dmg);
    int               &get_hp()                 { return hit_points; }
    const int         &get_hp()const            { return hit_points; }
    Coordinates       &get_coords()             { return coords; }
    const Coordinates &get_coords() const       { return coords; }
    const size_t      &get_ID() const           { return ID; }
    const std::shared_ptr<Crown> &get_crown()const   { return crown; }


    virtual char type(){
        return 'o';
    }

    friend std::ostream  &operator<< (std::ostream &out, const Object &obj);
    friend std::istream  &operator>> (std::istream &in, Object &obj);
};

std::ostream &operator<< (std::ostream &out, const Object &obj){  //write to console
     out << obj.get_coords().axis_x << obj.get_coords().axis_y << obj.get_hp();
    return out;
}

std::istream &operator>> (std::istream &in, Object &obj){  //read from console
    in >> obj.get_coords().axis_x >> obj.get_coords().axis_y >> obj.get_hp();
    return in;
}

Object* Object::check_Coords(Coordinates const &crds){
    if(coords == crds)
        return this;
    else
        return nullptr;
};

void Object::get_Damage(size_t const &dmg){
    get_hp() -= dmg;
}

#endif //OBJECT
