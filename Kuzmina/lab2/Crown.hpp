#ifndef Crown_hpp
#define Crown_hpp
#include <iostream>
#include <string>
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLACK   "\033[30m"      /* Black */
class Crown {
private:
    std::string colour;
public:
    Crown (std::string clr = "without colour") : colour(clr){
        std::cout << "Crown:\n    color = " << colour << std::endl
        <<"Crown.\n";
    }
    ~Crown(){
        std::cout << "~Crown:\n    color = " << colour << std::endl
        <<"Crown.\n";
    }
    std::string &get_color() { return colour; }
};

#endif /* Crown_hpp */
