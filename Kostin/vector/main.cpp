#include <iostream>
#include "my_vector.hpp"
#include "iterator.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
    List<int*> lst;
    int *a = new int(222);
    lst.Add_to_Head(a);
    lst.Add_to_Head(a);
    lst.Add_to_Head(a);
    std::cout << "/* Add */" << '\n';
    lst.Print_List();
    std::cout << "/* Delete */" << '\n';
    lst.Delete_elem(2);
    lst.Print_List();


    // lst.Print_List();
    // std::cout << "/* Add */" << '\n';
    // for (size_t i = 1; i < 4; i++) {
    //     lst.Add_to_Head(i*111);
    //     lst.Print_List();
    //     std::cout << "/* message */" << '\n';
    // }
    //
    // lst.Print_List();
    // std::cout << "/* Delete */" << '\n';
    // for (size_t i = 1; i < 4; i++) {
    //     std::cout << "For i ==" << i << '\n';
    //     lst.Delete_elem(i);
    //     lst.Print_List();
    // }

    //std::cout << "lst[0] = " << lst[1] << endl;
    //std::cout << "lst[7] = " << lst[6] << endl;
//    std::cout << "lst[8] = " << lst[8] << endl;
    //
    // for( Elem<int> &elem : lst){
    //     //elem.get_Info() = 1;
    //     elem = 1;
    //     std::cout << elem.get_Info() << '\n';
    // }
    // lst.Print_List();
    //
    // lst.~List();
    // lst.Print_List();
    // std::cout << "Lenght = " << lst.Quantity() << '\n';
    // lst.Add_After(234, 1);
    // lst.Print_List();
    std::cout << "The end!" << '\n';

    return 0;
}
