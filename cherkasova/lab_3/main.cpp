#include <typeinfo> // cout << typeid(...).name()
#include "field.hpp"

using namespace std;

int flag_exit = 0;
int check = 0;

int Object::count_ob;
int Object::cur_amount;

void cinclear(){
    cin.clear(ios::goodbit); // if the latest input was wrong - flushing bufer
    cin.ignore(65535, '\n');
}

int menu(){
    char choice;
    int key = 1;
    while(key){
        cout << "Would you like to load data from file? (y/n)\n";
        cin >> choice;
        if (choice == 'y') { key = 0; return 1; }
        if(choice == 'n') { key = 0; return 0; }
        else { cout << "ERROR! Incorrect input, try again.\n"; continue; }
    }
}

int check_for_win(Field &fd){
// 0 - red won, 1- green won, -1 - continue game
    int green_total = 0;
    int red_total = 0;
    for(auto& elem: fd.getlist()){
        if (elem.get()->getcrown()->getcolor() == "green") {
            green_total++;
        }
        else red_total++;
    }
    for(auto& elem: fd.getlist()){
        if(elem.get()->getcrown()->getcolor() == "green" && !elem.get()->alive())
            green_total--;
        if(elem.get()->getcrown()->getcolor() == "red" && !elem.get()->alive())
            red_total--;
    }
    if(!green_total) 
            return 1;
    if(!red_total) 
            return 0;
    return -1; // continue gamme   
}

string names(char name_mark){
    switch(name_mark){
        case 'o':
            return "object";
            break;
        case 'w':
            return "warrior";
            break;
        case 's':
            return "swordsman";
            break;
        case 'm':
            return "magician";
            break;
        case 'b':
            return "building";
            break;
        default:
            return "c";
            break;
    }
}

void warrior_group_action(Object* o, Field& fd){
    Warrior* w;
    switch(o->getmark()){
        case 'w':
            w = static_cast<Warrior*>(o);
            break;
        case 's':
            w = static_cast<Swordsman*>(o);
            break;
        case 'm':
            w = static_cast<Magician*>(o);
            break;
    }
    // int check = 0;    
    char action;
    int finish = 0;
    while(!finish){
        cin.clear();
        cout << "To attack press 'a', to move -'m' [to finish - any other button]: ";
        cin >> action; 
        switch(action){
        case 'm':                                           
            cout << "----To move it up press 'u', down-'d', right-'r', left-'l': ";
            cin.clear();                                
            char act;
            cin >> act;
            if (w->move_to(act, fd.getx_size()-1, fd.gety_size()-1) == -1) { 
                cout << "The warriow was not found or the border met\n"; break; 
            }
            cout << endl << fd;
            break;
        case 'a':
            if (fd.attack(w->aim_attack(), w))
                { cout << "There is no targets or they belong to the warrior's army \n"; break; }
            cout << fd;
            break;
        default:
            finish = 1;
            break;
        }
        check = check_for_win(fd);
        if(check != 1 && check != 0) { cout << "Continue\n"; }
        else {finish = 1; flag_exit = 1;}
    }

}

void behavior(string name, Object* o, Field& fd){
    cout << "Selected target is " << name << endl;
    cout << "----Location: " << o->getx() << " " << o->gety() << endl;    
    cout << "----Hit points: " << o->gethp() << endl;
    cout << "----Army: " << o->getcrown()->getcolor() << endl;
    
    char action;
    int finish;
    int mark = o->getmark();
    if(mark == 'w' || mark == 's' || mark == 'm'){
        warrior_group_action(o, fd); 
    }         
}

//-----------------MAIN----------------------------
int main()
{
    filebuf filename;
    auto flagfile = filename.open("input", ios::in);
    if(!flagfile){ cout << " ERROR with file!\n "; exit(1); }
    istream fin(&filename);
    //ifstream fin("file");
       
    Field fd;
    fin >> fd;   
    fd.print_field(cout);
    // cout << "See the list :\n"; fd.print_list();

    int a = 0, x = 0, y = 0, ind = 0, id_found;
    char c[1];
    int finish = 0; 
    while(!finish){ // continue: finish = 0, quit: finish = 1
        cinclear();
        cout << "Select a target (enter x y - unsigned int numbers separated by space) [q to exit]: " << endl;
        cin >> c[0];
        if ( *c == 'q') {finish = 1; break;}    
        x = atoi(c); 
        cin >> y;
        Object* ob;
        id_found = fd.find_id(x,y);
        if(id_found != -1)
            ob = fd.get_obj(id_found);
        else { cout << "Selected target wasn't found. Try again (maybe inccorect input).\n"; cin.clear(); continue;}
        if (!fd.is_obj(id_found)){ 
            cout << "No: doesn't exist or was killed.\n"; 
            continue;
        }   
        string name = names(ob->getmark());
        if(name == "c") continue;
        behavior(name, ob, fd); 
        if(flag_exit) break;
    }    

// fix comments for exit
    // file.close();
    filename.close();
    if(check == 1) {cout << "\n!!!The red army won!!!\n\n"; }
    else if(check == 0){cout << "\n!!!The green army won!!!\n\n"; }
    // cout << "Exit status: " << exit_key << endl;
    return 0;   
}
//------------------------------------------------
