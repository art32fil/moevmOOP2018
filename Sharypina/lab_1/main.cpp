#include "battlefield.h"

using namespace std;

int main()
{

ifstream fin("input.txt");
Battlefield field(fin);

bool flag=true; //флажок продолжения работы
char cnt;
Coordinates coord; //координаты цели


field.print_field();

while(flag)
{
  //field.print_field();
  cout<<"Input coordinates of target (separated by space): ";
  cin>>coord.x>>coord.y;
  int pos; //для определения принадлежности армии
  Object* cur=field.check_object(coord, pos); //если на данной позиции есть объект, то вернется указатель на него
  switch(pos) //обработка ситуации
  {
    case 1:
      cout<<"Selected target belongs to the first army"<<endl;
      break;
    case 2:
      cout<<"Selected target belongs to the second army"<<endl;
      break;
    case 0:
      cout<<"This position is empty"<<endl;
      break;
    default:
      cout<<"Coordinates are out of field"<<endl;
      break;
  }
  
  if(cur) //если координаты корректны и объект существует
  { // ?? - обработка отрицательного hp
    int dmg; //урон
    cout<<"Damage value: "; cin>>dmg;
    cur->damage(dmg);
    field.update_pattern(); //обновляем поле боя
  }

  field.print_field();

  cout<<"do you want to continue? y/n "<<endl; cin>>cnt;
  if(cnt=='n') flag=false;
}
//field.print_field();
  return 0;
}
