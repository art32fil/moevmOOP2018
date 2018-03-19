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
    size_t position; // of Object in List
public:
    Object(){
        /*std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\033[1;32m Object() \033[0m" << std::endl << std::endl;*/
    }
    Object(size_t arg_x, size_t arg_y, int hp = 100, size_t pos = 0)
                : coords(arg_x, arg_y), hit_points(hp), position(pos){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\033[1;32m Object(size_t, size_t, int) \033[0m" << std::endl << std::endl;
    }
    ~Object(){
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\033[1;31m ~Object() \033[0m" << std::endl << std::endl;
    }
    Object(Object const &obj){
        coords = obj.get_coords();
        hit_points = obj.get_hp();
        position = obj.get_position();
        std::cout << "\tx = " << coords.axis_x << std::endl
                  << "\ty = " << coords.axis_y << std::endl
                  << "\thp = " << hit_points << std::endl
                  << "\033[1;32m Object(Object const &) \033[0m" << std::endl << std::endl;
    }
    Object(Object&& obj) : coords(std::move(obj.get_coords())),
                hit_points(std::move(obj.get_hp())), position(std::move(obj.get_position())) {
                            std::cout << "\tx = " << coords.axis_x << std::endl
                                      << "\ty = " << coords.axis_y << std::endl
                                      << "\thp = " << hit_points << std::endl
                                      << "\033[1;32m Object(Object &&) \033[0m" << std::endl << std::endl;
             }

    Object &operator=  (Object&& obj){
         coords = std::move(obj.get_coords());
         hit_points = std::move(obj.get_hp());
         position = std::move(obj.get_position());
         return *this;
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
    bool    operator== (Object const &obj){
        return (obj.coords.axis_x == coords.axis_x && obj.coords.axis_y == coords.axis_y);
    }

    void              get_Damag(size_t const &dmg);
    int               &get_hp()                 { return hit_points; }
    const int         &get_hp()const            { return hit_points; }
    Coordinates       &get_coords()             { return coords; }
    const Coordinates &get_coords() const       { return coords; }
    size_t            &get_position()           { return position; }
    const size_t      &get_position() const     { return position; }

    Object* check_Coords(Coordinates const &);
};

Object* Object::check_Coords(Coordinates const &crds){
    if(coords.axis_x == crds.axis_x && coords.axis_y == crds.axis_y)
        return this;
    else
        return nullptr;
};

void Object::get_Damag(size_t const &dmg){
    get_hp() -= dmg;
}

#endif //OBJECT
