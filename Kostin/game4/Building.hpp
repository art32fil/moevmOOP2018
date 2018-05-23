#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "Object.hpp"
#include <vector>

std::ostream &operator<< (std::ostream &out, std::vector<Coordinates> const &v){
    for(auto &el : v){
        std::cout << el << ' ';
    }
    if(v.empty())
        std::cout << "empty" << '\n';
    return out;
}

class Building : public Object {
private:
    std::vector<Coordinates> building;
public:
    Building(const std::shared_ptr<Crown>& _crown) : Object(_crown){
        std::cout << "\tBuilding = " << building <<  std::endl  //buildint trow error like lvalue
                  << "\033[1;32m Building(size_t, size_t, ...) \033[0m"
                  << std::endl << std::endl;
    };
    Building(size_t arg_x, size_t arg_y, const std::shared_ptr<Crown> _crown, std::vector<Coordinates> v,
         int hp = 100) : Object(arg_x, arg_y, _crown, hp), building(v){};

    ~Building(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\tforce = " << building << std::endl
                  << "\033[1;31m ~Building() \033[0m" << std::endl << std::endl;
    };

    std::vector<Coordinates>       &get_building()       {return building;}
    const std::vector<Coordinates> &get_building() const {return building;}

    char type() override{
        return 'b';
    }

    friend std::istream &operator>> (std::istream &in, Building &bild);
    friend std::istream &operator>> (std::istream &in, std::vector<Coordinates> v);
    friend std::ostream &operator<< (std::ostream &out, std::vector<Coordinates> v);
};

std::istream &operator>> (std::istream &in, std::vector<Coordinates> &v){
    size_t i = 0, x, y;
    in >> i;
    for(size_t k = 0; k < i; k++){
        in >> x >> y;
        v.push_back({x,y});
    }
    return in;
}

std::istream &operator>> (std::istream &in, Building &bild){
    in >> static_cast<Object &>(bild) >> bild.building;
    return in;
}

#endif
