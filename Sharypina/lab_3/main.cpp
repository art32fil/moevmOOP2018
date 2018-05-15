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

field.print_field();

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
      Warrior* cur_war = dynamic_cast<Warrior*>(cur_obj);
      cout << "select action:" << endl;
      cout << "1 - move" << endl;
      cout << "2 - attack" << endl;

      int action;
      string direction;
      cin >> action;
      if (action == 1) { //выбрано передвижение
        cin >> direction;
        cur_war->move(direction, field.get_size());
      }
      else if (action == 2) { //выбрана атака

        string attacked_color;
        if (cur_color == "red") attacked_color = "green"; //можно бить только объект противоположной армии
        else attacked_color = "red";

        Object* attacked_object = field.check_object(cur_coords, attacked_color);
        if (!attacked_object) { //если объекта на данной позиции не оказалось
          cout << "there is no object of " << attacked_color << " army" << endl;

        }
        else { //объект на данной позиции есть, тогда атака
          cur_war->attack(attacked_object);
          field.check_hp(); //проверяем, что с hp после атаки, если <= 0, удаляем объект
        }
      }
      field.update_pattern(); //обновляем шаблон - поле
    }
    else { //если выбранный объект не воин, он не может выполнять действия
      cout << "this is not warrior" << endl;
    }

  }
  field.print_field();
}
  return 0;
}
