// Шаблонный линейный двунаправленный список со вставкой элементов в начало
#include <iostream>
#include "list.hpp"
#include "iter.hpp"

using namespace std;


//-----------------MAIN----------------------------
int main(){
    List <int> list;
    for (int i = 0; i < 1; i++){
        list.insert_head(i);
    }
    list.print();
    list.insert_tail(222); 
    list.print();  
    list.insert_after(8,1);
    list.print();   
    list.insert_after(299,299);
    list.print();    
    list.insert_after(2002, 0);    
    list.print();
    list.insert_head(333);    
    list.print();        
    list.delete_elem(2);   
    list.print(); 

    cout<< list[0] <<endl;


    for( Elem<int> &elem : list){
        elem.get()=1;
    }
    
    list.print();   

    auto it = list.begin();
    it->get() = 2;
    list.print();

    cout << "Checking -> : Begin value is "<< list.begin()->get() << endl;

    return 0;   
}
//------------------------------------------------

    