#ifndef CROWN_HPP
#define CROWN_HPP
#include <iostream>
#include <string>

class Crown {
private:
    std::string colour;
public:
    Crown (std::string clr = "without colour") : colour(clr){
        std::cout << "\tcolor = " << colour << std::endl
                  << "\033[1;34m Crown \033[0m"
                  << std::endl << std::endl << std::endl;
    }
    ~Crown(){
        std::cout << "\tcolor = " << colour << std::endl
                  << "\033[1;34m ~Crown\033[0m"
                  << std::endl << std::endl << std::endl;
    }
    // const string &get_color() const { return colour; }
    std::string &get_color() { return colour; }

};

#endif // CROWN_HPP
