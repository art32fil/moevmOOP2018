#include <iostream>
#include <string>
#include <limits> // for cinckear()
#include <typeinfo> // cout << typeid(...).name()
#include "list"
#include "iter"
#include "object"
#include "field"

using namespace std;

void cinclear()
{
    cin.clear(); // if the latest input was wrong - flushing bufer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int menu()
{
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

//-----------------MAIN----------------------------
int main()
{
    fstream fin("input");
    if(!fin){cout << " ERROR with file!\n "; exit(1);}
    fstream f("fromconsole", ios::out);
    f.close();
    fstream fc("fromconsole");

    vector <List<Object>*> all_cont; 
   
    int x_load = 0;
    int y_load = 0;
    int army_amount = 0;
    int choice = menu();

    if(choice){ // file
        fin >> x_load >> y_load >> army_amount;    
    }  
    else { //console
        int o_amount, x_, y_, hp_;
        cout << "Enter size of field (x y) and amount of armies (unsigned int numbers separated by space): " <<endl;
        cin >> x_load >> y_load >> army_amount; 
        int m = 0; 
        while(m++ < army_amount){
            cout << "_" << m << " army: " << endl;
            cout << "Enter the amount of objects (unsigned int)\n";
            cout << "Then - their location (x y) and hit points (unsigned int numbers separated by space): \n";
            cin >> o_amount; 
            fc << o_amount << '\n'; 
            int n = 0;
            while(n++ < o_amount){ 
                cout << "_" << n << " object: " << endl;           
                cin >> x_; fc << x_ << " ";
                cin >> y_; fc << y_ << " ";
                cin >> hp_; fc << hp_ << "\n";
            }
        }
    }

    Field *fd = new Field(x_load, y_load);        
   
    if(choice){ // file
        fd->read_file(fin);
    }  
    else { //console
        fd->read_file(fc);    
    }

    fd->print_field();

    cout << "See all containers (army, object_index: [x y hp] ):\n"; fd->print_cont();
while(1){
    int a, x, y, ind;
in1_:
    cout << "If there is alive object? Enter coordinates of the object (x y - unsigned int numbers separated by space) or q to exit: " << endl;
    cin >> x;
    if ( x == 'q') { fd->~Field(); fin.close(); fc.close(); exit(0);}    
    cin >> y;
    a = fd->belonging_army(x,y);
    ind = fd->find_ob_index(x,y);
    if(ind == -1 || a == -1) { cout << "Selected target wasn't found. Try again." <<endl; goto in1_;}
    else if (fd->getconts()[a]->find(ind)->get().is_obj(x,y,fd->getmap())) {
        cout << "Yes: hp = "<< fd->getconts()[a]->find(ind)->get().gethp() << endl;
    } else cout << "No: doesn't exist or was killed.\n";

in2_:
    cout << "Input coordinates of the target (unsigned int numbers separated by space) to select and get to know its army (q to exit):\n";
    x = 0; cin >> x;
    if ( x == 'q') { fd->~Field(); fin.close(); fc.close(); exit(0);}
    cin >> y;             
     
    int belong = fd->belonging_army(x,y);
    switch(belong){
        case 0:
            cout << "Selected target is red\n";
            break;
        case 1:
            cout << "Selected target is green\n";
            break;
// ...another armies
        default:
            cout << "Error! The target wasn't found. Try again.\n";
            goto in2_;
            break;
    }

    int d;
    cout << "Input a damage value (unsigned int): "; 
    cin >> d; 
    ind = fd->find_ob_index(x,y);
    fd->getconts()[a]->find(ind)->get().damage(d);
    cout << "Hit points left in selected target: " << fd->getconts()[a]->find(ind)->get().gethp() <<endl;

    fd->print_field();

in3_:
    cinclear();
    cout << "Continue or quit? (c/q)\n";
    char switch_on;
    cin >> switch_on; 
    if (switch_on == 'c') continue;
    else if (switch_on == 'q') { fd->~Field(); fin.close(); fc.close(); exit(0);}
    else { cout << "ERROR! Incorrect input, try again.\n";  goto in3_; }
}
    
    fd->~Field();
    fin.close();
    fc.close();
    return 0;   
}
//------------------------------------------------
