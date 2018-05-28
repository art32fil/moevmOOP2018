#ifndef FEATURES_H
#define FEATURES_H

enum Color { white, green, red };

//----------------------------------------------

struct Size {
  int size_x;
  int size_y;

  Size(int x, int y): size_x(x), size_y(y) {
    std::cout << "size_x = " << size_x << std::endl;
    std::cout << "size_y = " << size_y << std::endl;
  }

  Size(){}
};

std::ifstream &operator>>(std::ifstream &fin, Size &size) {
  fin >> size.size_x >> size.size_y;
  return fin;
}
//----------------------------------------------

struct Position {
  Color color;
  char status;

  Position(Color clr, char sym) : color(clr), status(sym) {}
};


#endif
