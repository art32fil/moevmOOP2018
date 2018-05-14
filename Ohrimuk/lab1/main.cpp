#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"

using std::cout;
using std::cin;
using std::endl;
// Определяем синоним L для списка целых чисел.
typedef List<int> L;

int main()
{
// Пустые списки m и l.
List<int> l, m;
List<int>::Iterator i, j;
int c;

// Добавляем в конец l десять случайных чисел от 1 до 10.
srand( time( 0 ) ); // автоматическая рандомизация
for (c = 10; c--; )
  l.PushBack(rand() % 10 + 1);
cout << "Push back 10 random el-ts to l.\nl = " ;
l.show(); 
cout << endl;

// Удваиваем элемнты l.

for (i = l.Begin(), c=0;	// начинаем с первого
     i != l.End();   // продолжаем, пока не "выскочим" за пределы списка
     i++,c+=2)				//                                     затем переходим к следующему за i-м.
  {
  	// Сначала вставляем элемент перед c-м эл-том его компию,
 	  //l.Insert(c, *i);
	  l.show(); 
	//cout << endl;
  }
  
cout << "Double each el-t in l.\nl = " ;
l.show(); 
cout << endl;

// Вставляем эл-ты l в m в обратном порядке.
for (i = l.Last();	// начинаем с последнего
     i != l.End();   // продолжаем, пока не "выскочим" за пределы списка
     i--)            //                                    и переходим к предшествующему.
  m.PushBack(*i);    // Добавляем в конец m i-й эл-т из l,
cout << "Push back l's el-ts to m in reverse order.\nm = " ;
m.show(); 
cout << endl;

c=0;
// Удаляем каждый второй эл-т в m (начиная с первого).
for (i = m.Begin();	// начинаем с первого
     i != m.End();   // продолжаем, пока не "выскочим" за пределы списка
     i++)            // (*) затем пропускаем оставляемый элемент
  {
	m.Delete(c++);     // Удаляем c-й эл-т, предварительно смещая c на один эл-т вперед.
	i++;				//смещаем i на один эл-т вперед, (*)
  }
  
cout << "Delete each second el-t from m.\nm = " ;
m.show(); 
cout << endl;

// Вставляем в начало m три нуля.
for (c = 3; c--; )
  m.PushFront(0);
cout << "Push front 3 zeros to m.\nm = " ;
m.show(); 
cout << endl;

// Добавляем к эл-м l значения соответствующих эл-в m, пока один из списков не кончится.
for (i = l.Begin(), j = m.Begin(); i != l.End() && j != m.End(); i++, j++)
  *i += *j;
cout << "Add m's el-ts to l's el-ts until one of the lists isn't done.\nl = " ;
l.show(); 
cout << endl;

// Удаляем из m три первых нуля.
for (c = 3; c--; )
  m.PopFront();
cout << "Remove lead zeros form m.\nm = " ;
m.show(); 
cout << endl;

// Очищаем список m.
m.Clear();
cout << "Remove all el-ts from m.\nm = " ;
m.show(); 
cout << endl;

cin.ignore(100, 'q');
}
