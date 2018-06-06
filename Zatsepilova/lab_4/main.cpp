#include <typeinfo> // cout << typeid(...).name()
#include "field.h"

using namespace std;

int flag_exit = 0;
int check = 0;

int Object::count_ob;
int Object::cur_amount;

void cinclear(){
    cin.clear(ios::goodbit); // if the latest input was wrong - flushing bufer
    cin.ignore(65535, '\n');
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
    cout << "----Power: " << o->getpower()  << endl;          
    char action;
    int finish = 0;
    while(!finish){
        cin.clear();
        cout << "To attack - 'a', to move -'m': ";
        cin >> action; 
        switch(action){
        case 'm':                                           
            cout << "----To move it up press 'u', down-'d', right-'r', left-'l': ";
            cin.clear();                                
            char act;
            cin >> act;
            if (o->move_to(act, fd.getx_size()-1, fd.gety_size()-1) == -1) { 
                cout << "The warriow was not found or the border met\n"; break; 
            }
            cout << endl << fd;
            break;
        case 'a':
            if (fd.attack(o))
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

void building_action(Object* o, Field& fd){ 
    cout << "To launch production press 'p' [any key to quit]: ";
    char inp;
    cin >> inp;
    if (inp == 'p'){
        int x, y;
        cout << "Enter the location of a new warrior (x, y space delimed): ";
        cin >> x >> y; 
        if(fd.find_id(x,y) == -1 && x < fd.getx_size() && y < fd.gety_size()){
            Object* new_w = o->production(x, y);
            fd.getlist().insert_tail((new_w));
            cout << fd << endl;
        }
        else if (fd.find_id(x,y) != -1) cout << "This location isn't available\n";
    }
}

void behavior(string name, Object* o, Field& fd){
    cout << "Selected target is " << name << " [to select the next press any other key]" << endl;
    cout << "----Location: " << o->getx() << " " << o->gety() << endl;    
    cout << "----Hit points: " << o->gethp() << endl;
    cout << "----Army: " << o->getcrown()->getcolor() << endl;
    
    char action;
    int finish;
    int mark = o->getmark();
    if(mark == 'o' || mark == 's' || mark == 'm' || mark == 'w'){
        warrior_group_action(o, fd); 
    }         
    if(mark == 'b') building_action(o, fd);
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

    int a = 0, x = 0, y = 0, ind = 0, id_found;
    char c[1];
    int finish = 0; 
    while(!finish){ // continue: finish = 0, quit: finish = 1
        cout << "Press any key to start\n";
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
    if (flag_exit == 0){
        if(check == 1) {cout << "\n!!!The red army won!!!\n\n"; }
        else if(check == 0){cout << "\n!!!The green army won!!!\n\n"; }
    }   
    else {cout << "\nERROR (1)\n";}
    // cout << "Exit status: " << exit_key << endl;
    return 0;   
}
//------------------------------------------------
