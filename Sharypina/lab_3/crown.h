#ifndef CROWN_H
#define CROWN_H
#include <string>


class Crown {
private:

 std::string color;

public:

Crown(std::string color) : color(color){
  std::cout << "Crown:" << std::endl;
  std::cout << "color = "<< color << std::endl;
  std::cout << "Crown." << std::endl;
}

//----------------------------------------------

~Crown() {
  std::cout << "~Crown:" << std::endl;
  std::cout << "color = "<< color <<  std::endl;
  std::cout << "~Crown." << std::endl;
}

//----------------------------------------------

const std::string &get_color() {
  return color;
}

};


#endif
