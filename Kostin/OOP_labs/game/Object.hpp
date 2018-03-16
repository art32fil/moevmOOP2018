#ifndef OBJECT_HPP
#define OBJECT_HPP

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
};

class Object {
private:
    Coordinates coords;
    int hit_points;
public:
    Object(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "Object()" << std::endl;
    }
    Object(size_t arg_x, size_t arg_y, int hp = 100) : coords(arg_x, arg_y), hit_points(hp){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "Object(size_t, size_t, int)" << std::endl;
    }
    ~Object(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "~Object()" << std::endl;
    }

    Object(Object const &obj){
        coords = obj.get_coords();
        hit_points = obj.get_hp();

        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "Object(Object const &)" << std::endl;
    }
    Object(Object&& obj) : coords(std::move(obj.get_coords()))
                        , hit_points(std::move(obj.get_hp())) {
                            std::cout << "\tx = " << coords.axis_x << std::endl
                                      << "\ty = " << coords.axis_y << std::endl
                                      << "\thp = " << hit_points << std::endl
                                      << "Object(Object &&)" << std::endl;
             }
    Object &operator=(Object&& obj){
         coords = std::move(obj.get_coords());
         hit_points = std::move(obj.get_hp());
         return *this;
    }
    Object &operator=(Object &obj){
        if(this != &obj)
        {
            coords = obj.get_coords();
            hit_points = obj.get_hp();
        }
        return *this;
    }
    bool    operator== (Object const &obj){
        return (obj.coords.axis_x == coords.axis_x && obj.coords.axis_y == coords.axis_y);
    }

    void        get_Damag(size_t &dmg);
    int         &get_hp(){ return hit_points; }
    const int         &get_hp() const { return hit_points; }
    Coordinates &get_coords(){ return coords; }
    const Coordinates &get_coords() const { return coords; }

    //Object* check_Position(){}; //это  перегрузка оператора ==
};

void Object::get_Damag(size_t &dmg){
    get_hp() -= dmg;
}

#endif //OBJECT
