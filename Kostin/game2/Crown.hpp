#ifndef CROWN_HPP
#define CROWN_HPP

#include <string>

class Crown {
private:
    string colour;
public:
    Crown (string clr = "without colour") : colour(clr){
        std::cout << "\tcolor = " << colour << std::endl
                  << "\033[1;32m Crown \033[0m"
                  << std::endl << std::endl << std::endl;
    }
    ~Crown(){
        std::cout << "\tcolor = " << colour << std::endl
                  << "\033[1;32m ~Crown\033[0m"
                  << std::endl << std::endl << std::endl;
    }
    // const string &get_color() const { return colour; }
    string &get_color() { return colour; }

};

#endif // CROWN_HPP
