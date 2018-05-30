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
Coordinates cur_coords; //координаты выбранного объекта
Object* cur_obj;

//field.print_field(cout);
cout << field;

while(flag)
{
  cout << "select object (enter color, x, y, separated by space) ";
  cout << "or enter q to exit" << endl;
  cin >> cur_color;
  if (cur_color == "q") break; //проверка на окончание игры
  else {
    cin >> cur_coords.x >> cur_coords.y;
  }

  cur_obj = field.check_object(cur_coords, cur_color); //проверяем, есть ли объект с заданными координатами и цветом
  if (!cur_obj) { //если нет, выводим сообщение
    cout << "there is no object with color " << cur_color << endl;
  }
  else { //такой объект существует
    if (cur_obj->get_type() == 'w') { //если выбранный объект - warrior
      //Warrior* cur_war = dynamic_cast<Warrior*>(cur_obj);
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
        field.fight(cur_obj, cur_color); //
        field.check_hp();
      }
      field.update_pattern(); //обновляем шаблон - поле
    }
    else { //если выбранный объект не воин, он не может выполнять действия
      cout << "this is not warrior" << endl;
    }

  }
  field.winner();
  cout << field;
}
  return 0;
}
