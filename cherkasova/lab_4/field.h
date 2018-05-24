#pragma once
#include "iter.h"
#include "warrior.h"
#include "building.h"

using namespace std;

class Warrior;

//--------------------------------------FIELD----------------------------------------------
class Field
{
    int x_size;
    int y_size;

    weak_ptr<Crown> crown_red;
    weak_ptr<Crown> crown_green;

    List<Object*> list;

  public:
    Field() {}
    ~Field();

    void init();
    int find_id(int x, int y);
    int find_index(int id_);  
    int find_index(int x, int y, int mark_color); 
    Object *get_obj(int id_);
    Object *get_obj(int x, int y, char mark_color);
    bool is_obj(int id_);
    int attack(vector<pair<int,int>> aims, Object* w);
    void read_from_file(istream &in);
    void print_list();
    void print_field(ostream &out);

    List<Object *> &getlist();  
    int &getx_size();
    int &gety_size();

    friend istream &operator>>(istream &in, Field &fd);
    friend ostream &operator<<(ostream &out, const Field &fd);
};
//-----------------------------------------------------------------------------------------

//---------------------------------FIELD-METHODS-------------------------------------------
void Field::init(){
    cout << "Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;
}

Field::~Field(){
    cout << "~Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;
}

int Field::find_id(int x, int y){
    for (const auto &obj : list){
        if (obj.get()->getx() == x && obj.get()->gety() == y){
            return obj.get()->getid();
        }
    }
    return -1;
}

int Field::find_index(int id_){
    int count = 0;
    for (const auto &obj : list){
        if (obj.get()->getid() == id_){
            return count;
        }
        count++;
    }
    return -1; // not found
}

int Field::find_index(int x, int y, int mark_color){
    int count = 0;
    for (const auto &obj : list){
        if (obj.get()->getx() == x && obj.get()->gety() == y){
            if(mark_color == 'a') // ob, bd, wr
                return count;
        
            if(mark_color == 'g'){ // ob, bd
                if(obj.get()->getcrown()->getcolor() == "green"){
                    return count;
                }
            }
            if(mark_color == 'r'){
                if(obj.get()->getcrown()->getcolor() == "red"){
                    return count;
                }
            }
        }
        count++;
    }
    return -1; // not found
}

Object *Field::get_obj(int id_){
    for(const auto &item: list){
        if(item.get()->getid() == id_){
            return item.get();
        }
    }
    return nullptr;
}

Object *Field::get_obj(int x, int y, char mark_color){ //map[j][i]-ok
    int ind = find_index(x,y,mark_color);
    if (ind == -1)
        return nullptr;
    return list.find(ind)->get();
}

bool Field::is_obj(int id_){
    Object* o = get_obj(id_);
    if (o){
        if (!o->alive()){
            list.delete_elem(find_index(id_));
            return false;
        }
        else return true;
    }
    return false; // not found
}

int Field::attack(vector<pair<int,int>> aims, Object* w){
    if(aims.empty()) {cout << "return 0"<<endl;return 0;}
    char mark_color = w->getcrown()->contr_color()[0];   
    for(auto &aim: aims){
        Object* ob = get_obj(get<0>(aim), get<1>(aim), mark_color);
        if (!ob)  
            continue;    
        if(ob->getmark() == 'b'){
                Building* bd = static_cast<Building*>(ob);
                for(auto &item: bd->getlocation()){
                    if(get<0>(item) == bd->getx() && get<1>(item) == bd->gety()) 
                        continue;                         
                    Object* o = get_obj(get<0>(item), get<1>(item), mark_color);
                    o->damage(w->getpower());
                    if(!o->alive()) {
                        list.delete_elem(find_index(get<0>(item),get<1>(item),mark_color));
                    }
                }            
        }
        ob->damage(w->getpower());
        if(!ob->alive()) {
            list.delete_elem(find_index(get<0>(aim), get<1>(aim),mark_color));
        }
    }
    return 0;
}

void Field::print_list(){
    for (auto &ob : list){
        ob.get()->print_ob_simple();
    }
}

void Field::print_field(ostream &out){
    //borders
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
        out << i;
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;

    //fill field
    for (int i = 0; i < y_size; i++)
    {
        out << i << "|";
        for (int j = 0; j < x_size; j++)
        {
            if (!get_obj(j, i, 'a'))
                out << '.';
            else{
                out << *get_obj(j, i, 'a');
            }
        }
        out << "|" << endl;
    }

    //borders
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
        out << i;
    }
    out << endl;
    out << endl;
}

void Field::read_from_file(istream &in){
    int flag_init = 0;
    int obj_amount = 0;
    char which_army_mark;
    char type;
    string color;

    for (int j = 0; j < 2; j++){
        in >> obj_amount >> which_army_mark;
        if (which_army_mark == 'r')
            color = "red";
        if (which_army_mark == 'g')
            color = "green";

        for (int i = 0; i < obj_amount; i++){
            static shared_ptr<Crown> tmp;
            if (!flag_init){
                tmp = shared_ptr<Crown>(new Crown(color));
                this->crown_red = tmp;
                flag_init = 1;
            }
            in >> type;
            in.unget();
            Object *ob;
            if (type == 'o') { ob = new Object(tmp, in); list.insert_tail(ob); }
            if (type == 'w') { ob = new Warrior(tmp, in); list.insert_tail(ob); }
            if (type == 's') { ob = new Swordsman(tmp, in); list.insert_tail(ob); }
            if (type == 'm') { ob = new Magician(tmp, in); list.insert_tail(ob); }           
            if (type == 'b') {
                in >> type;
                int hp;
                in >> hp;
                int coord_amount;
                in >> coord_amount;
                vector<pair<int, int>> loc;
                int x, y;
                for(int i = 0; i < coord_amount; i++){
                    in >> x >> y;
                    auto p = make_pair(x, y);
                    loc.push_back(p);
                }
                for(auto &coord: loc){
                    Object* o;
                    o = new Building(tmp, type, get<0>(coord), get<1>(coord), hp, loc);
                    list.insert_tail(o); 
                }               
            }
            cout << type << endl;
        }
        flag_init = 0;
    }
    cout << "Field.\n";
}

ostream &operator<<(ostream &out, Field &fd){
    fd.print_field(out);
    return out;
}

istream &operator>>(istream &in, Field &fd){
    in >> fd.x_size >> fd.y_size;
    fd.init();
    fd.read_from_file(in);
    return in;
}

int &Field::getx_size()
    { return x_size;}

int &Field::gety_size()
    {return y_size;}

List<Object *> &Field::getlist()
    { return list; }

//-----------------------------------------------------------------------------------------
