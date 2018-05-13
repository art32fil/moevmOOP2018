#include <typeinfo> // cout << typeid(...).name()
#include "field.hpp"

using namespace std;

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
    cout << "See the list :\n"; fd.print_list();

    int exit_key = 0; // all is good
    int flag = 0;
    int finish = 0;
    int check = 0;

    int a = 0, x = 0, y = 0, ind = 0, id_found;
    char c[1];
    int flag_finish = 0;
    while(!flag_finish){
        cinclear();
        cout << "Select a target (enter x y - unsigned int numbers separated by space) or q to exit: " << endl;
        cin >> c[0];
        if ( *c == 'q') {flag_finish = 1; break;}    
        x = atoi(c); 
        cin >> y;
        Object* o;
        Warrior* w;
        id_found = fd.find_id(x,y);
        if(id_found != -1)
            o = fd.get_obj(id_found);
        else { cout << "Selected target wasn't found. Try again (maybe inccorect input).\n"; cin.clear(); continue;}
        if (fd.is_obj(id_found)){ 
            cout << "Selected target is ";
            char action;
            switch(o->getmark()){
                case 'o':
                    cout << "object.\nPress i to see the information [q to quit]: \n";   
                    cin >> action;
                    switch(action){
                        case 'q': 
                            flag_finish = 1; 
                            break;
                        case 'i':
                            cout << "Hit points: " << o->gethp() << endl;
                            cout << "Army it belongs to: " << o->getcrown()->getcolor() << endl;
                            break;
                        default:
                            exit_key = 1; //cout <<"Unknown command\n";
                            break;
                    } 
                    break;
                case 'w':
                    cout << "warrior.\n";
                    w = static_cast<Warrior*>(o);
                    finish = 0;
                    while(!finish){
                        cin.clear();
                        cout << "To attack press 'a', 'm'-to move, to see the info-'i' [any other button to finish]: ";
                        cin >> action; 
                        switch(action){
                        case 'i':
                            cout << "Hit points: " << w->gethp() << endl;
                            cout << "Power: " << w->getpower() << endl;                                
                            cout << "Army it belongs to: " << w->getcrown()->getcolor() << endl;
                            break;
                        case 'm':                                           
                            cout << "To move it up press 'u', down-'d', right-'r', left-'l': ";
                            cin.clear();                                
                            char act;
                            cin >> act;
                            int moved;
                            moved = w->move_to(act, fd.getx_size()-1, fd.gety_size()-1);
                            if ( moved == -1) { cout << "The warriow was not found or the border met\n"; break; }
                            cout << endl << fd;
                            break;
                        case 'a':
                            if (fd.attack(w->aim_attack(), *w))
                                { cout << "There is no targets or they belong to the warrior's army \n"; break; }
                            cout << fd;
                            break;
                        default:
                            finish = 1;
                            break;
                    }
                    check = check_for_win(fd);
                    if(check != 1 && check != 0) { cout << "Continue\n"; }
                    else {flag_finish = 1; break;}
                }
                break;
                case 'b':
                    cout << "building.\nPress i to see the information [q to quit]: \n";   
                    o = static_cast<Building*>(o);
                    char action;
                    cin >> action;
                    switch(action){
                        case 'q': 
                            flag_finish = 1; 
                            break;
                        case 'i':
                            cout << "Hit points: " << o->gethp() << endl;
                            cout << "Army it belongs to: " << o->getcrown()->getcolor() << endl;
                            break;
                        default:
                            exit_key = 1; //cout <<"Unknown command\n";
                            break;
                    }                   
                    break;
                default:
                    exit_key = 1; //cout <<"Unknown behavior\n";
                    flag_finish = 1;
                    break;
            }
        } else {
            cout << "No: doesn't exist or was killed.\n"; 
            flag_finish = 1;
        }
    }    

// fix comments for exit
    // file.close();
    filename.close();
    if(check == 1) {cout << "\n!!!The red army won!!!\n\n"; }
    else if(check == 0){cout << "\n!!!The green army won!!!\n\n"; }
    cout << "Exit status: " << exit_key << endl;
    return 0;   
}
//------------------------------------------------
