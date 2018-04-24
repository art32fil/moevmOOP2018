#include "field.cpp"

using namespace std;

int Object::count_ob;
int Object::cur_amount;

void cinclear()
{
    cin.clear(ios::goodbit); 
    cin.ignore(65535, '\n');
}

int check_for_win(Field &fd){
// 0 - red won, 1- green won, -1 - continue game
    int red_total = fd.getconts()[0]->get_size(); 
    int green_total = fd.getconts()[1]->get_size();    

    for(auto& elem: *(fd.getconts()[0])){
        if(!elem.get()->alive()) 
            red_total--;
    }
    for(auto& elem: *(fd.getconts()[1])){
        if(!elem.get()->alive()) 
            green_total--;
    }   
    if(!green_total) 
            return 1;
    if(!red_total) 
            return 0;
    return -1; // continue gamme   
}

int main()
{
    filebuf filename;
    auto flagfile = filename.open("input", ios::in);
    if(!flagfile){ cout << " ERROR with file!\n "; exit(1); }
    istream fin(&filename);
    int x_load = 0;
    int y_load = 0;
    int army_number = 0;
       
    Field fd;
    fd.read_from_file(fin);   
    fd.print_field(cout);

    int flag = 0;
    int flag_exit = 0;

    while(!flag_exit){
        int a = 0, x = 0, y = 0, ind = 0;
        char c[1];
        int flag_finish = 0;
        while(!flag_finish){
            cinclear();
            cout << "Enter coordinates of the object (x y) or q to exit: " << endl;
            cin >> c[0];
            if ( *c == 'q') {flag_exit = 1; break;}    
            x = atoi(c); 
            cin >> y;
            a = fd.belonging_army(x,y);
            ind = fd.find_ob_index(x,y);
            if(ind == -1 || a == -1) { cout << "Try again.Target wasn't found. " <<endl; 
                    cin.clear(); continue;}
            else if (fd.is_obj(x,y) == 1) {
                cout << "Yes: hp = "<< fd.get_ob(x,y)->gethp() << endl;
                flag = 1; 
                break;
            } else {cout << "No: Target doesn't exist \n"; flag = 1;}
            if(flag) break;
        }
    if(flag_exit) break;
    flag = 0;
        while(1){
            switch(a){
                case 0:
                    cout << "Selected target is red\n";
                    flag = 1; break;
                case 1:
                    cout << "Selected target is green\n";
                    flag = 1; break;
                default:
                    cout << "Error! Try again. The target wasn't found. \n";
                    cinclear(); continue;
            }
            if(flag) break;
        }

    int d;
    cout << "Input a damage value : "; 
    cin >> d; 
    ind = fd.find_ob_index(x,y);
    fd.get_ob(x,y)->damage(d);
    fd.is_obj(x,y); 
    cout << "New damage value selected target: " << fd.get_ob(x,y)->gethp() <<endl;

    cout << fd;
    
    int check = check_for_win(fd);
    if(check == 1) {cout << "\n!!!The red army won!!!\n"; break; }
    else if(check == 0){cout << "\n!!!The green army won!!!\n"; break;}
    else continue;

     
}
    
    filename.close();
    return 0;   
}
