#include <iostream>
#include "my_vector.hpp"
#include "iterator.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
    List<int> lst;

    lst.Add_After(555, 1);
    lst.Add_After(999, 2);
    lst.Add_After(666, 3);
    lst.Add_After(333, 1);
    lst.Add_After(444, 5);
    lst.Add_After(777, 2);
    lst.Print_List();std::cout << "!!!" << '\n';
    lst.Delete_elem(3);
    lst.Print_List();std::cout << "!!!" << '\n';
    std::cout << "Lenght = " << lst.Quantity() << '\n';

    std::cout << "lst[1] = " << lst[1] << endl;
    //std::cout << "lst[7] = " << lst[6] << endl;
//    std::cout << "lst[8] = " << lst[8] << endl;

    for( Elem<int> &elem : lst){
        //elem.get_Info() = 1;
        elem = 1;
        std::cout << elem.get_Info() << '\n';
    }
    lst.Print_List();

    lst.~List();
    lst.Print_List();
    std::cout << "Lenght = " << lst.Quantity() << '\n';
    lst.Add_After(234, 1);
    lst.Print_List();
    std::cout << "The end!" << '\n';

    return 0;
}
