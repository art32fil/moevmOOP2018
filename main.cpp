#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"



using std::cout;
using std::cin;
using std::endl;
// ���������� ������� L ��� ������ ����� �����.
typedef List<int> L;





int main()
{
// ������ ������ m � l.
List<int> l, m;
List<int>::Iterator i, j;
int c;

// ��������� � ����� l ������ ��������� ����� �� 1 �� 10.
srand( time( 0 ) ); // �������������� ������������
for (c = 10; c--; )
  l.PushBack(rand() % 10 + 1);
cout << "Push back 10 random el-ts to l.\nl = " ;
l.show(); 
cout << endl;

// ��������� ������� l.

for (i = l.Begin(), c=0;	// �������� � �������
     i != l.End();   // ����������, ���� �� "��������" �� ������� ������
     i++,c+=2)				//                                     ����� ��������� � ���������� �� i-�.
  {
  	// ������� ��������� ������� ����� c-� ��-��� ��� ������,
 	  //l.Insert(c, *i);
	  l.show(); 
	//cout << endl;
  }
  
cout << "Double each el-t in l.\nl = " ;
l.show(); 
cout << endl;

// ��������� ��-�� l � m � �������� �������.
for (i = l.Last();	// �������� � ����������
     i != l.End();   // ����������, ���� �� "��������" �� ������� ������
     i--)            //                                    � ��������� � ���������������.
  m.PushBack(*i);    // ��������� � ����� m i-� ��-� �� l,
cout << "Push back l's el-ts to m in reverse order.\nm = " ;
m.show(); 
cout << endl;

c=0;
// ������� ������ ������ ��-� � m (������� � �������).
for (i = m.Begin();	// �������� � �������
     i != m.End();   // ����������, ���� �� "��������" �� ������� ������
     i++)            // (*) ����� ���������� ����������� �������
  {
	m.Delete(c++);     // ������� c-� ��-�, �������������� ������ c �� ���� ��-� ������.
	i++;				//������� i �� ���� ��-� ������, (*)
  }
  
cout << "Delete each second el-t from m.\nm = " ;
m.show(); 
cout << endl;

// ��������� � ������ m ��� ����.
for (c = 3; c--; )
  m.PushFront(0);
cout << "Push front 3 zeros to m.\nm = " ;
m.show(); 
cout << endl;

// ��������� � ��-� l �������� ��������������� ��-� m, ���� ���� �� ������� �� ��������.
for (i = l.Begin(), j = m.Begin(); i != l.End() && j != m.End(); i++, j++)
  *i += *j;
cout << "Add m's el-ts to l's el-ts until one of the lists isn't done.\nl = " ;
l.show(); 
cout << endl;

// ������� �� m ��� ������ ����.
for (c = 3; c--; )
  m.PopFront();
cout << "Remove lead zeros form m.\nm = " ;
m.show(); 
cout << endl;

// ������� ������ m.
m.Clear();
cout << "Remove all el-ts from m.\nm = " ;
m.show(); 
cout << endl;

cin.ignore(100, 'q');
}
