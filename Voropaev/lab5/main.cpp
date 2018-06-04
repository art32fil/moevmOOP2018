#include "battlefield.h"

using namespace std;

int Object::count = 0;
int Object::amount = 0;

int main()
{

ifstream fin("input.txt");
Battlefield field(fin);

bool flag = true; //флажок продолжения работы
//char cnt;
string cur_color;
char cur_type;
Coordinates cur_coords; //координаты выбранного объекта
Object* cur_obj;

cout << field;

while(flag) {
  cout << "select object (enter color, x, y, separated by space) ";
  cout << "or enter q to exit" << endl;
  cin >> cur_color;
  if (cur_color == "q") break; //проверка на окончание игры
  else {
    cin >> cur_type >> cur_coords.x >> cur_coords.y;
  }

  cur_obj = field.check_object(cur_coords, cur_color, cur_type); //проверяем, есть ли объект с заданными координатами и цветом
  if (!cur_obj) { //если нет, выводим сообщение
    cout << "there is no object with color " << cur_color << " and type -" << cur_type << endl;
  }
  else { //такой объект существует
    if (cur_type != 'b') { //если выбранный объект - воин или подобный ему
      cout << "select action:" << endl;
      cout << "1 - move" << endl;
      cout << "2 - attack" << endl;

      int action;
      string direction;
      cin >> action;
      if (action == 1) { //выбрано передвижение
        cin >> direction;
        cur_obj->move(direction);
        field.check_coords_update(cur_obj);
      }
      else if (action == 2) { //выбрана атака
        field.fight(cur_obj, cur_color);
      }
    }
    else if (cur_type == 'b') { //если здание
        field.add_new_object(cur_obj->spawn(), cur_color);
    }
  }
  field.winner(); //проверяем, есть ли победитель
  field.update_pattern(); //обновляем шаблон - поле
  cout << field;
}
  return 0;
}
