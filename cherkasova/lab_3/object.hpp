#ifndef OBJECT
#define OBJECT

#include <iostream>
#include <fstream>
#include <memory>
#include "crown.hpp"

using namespace std;

//--------------------------------------OBJECT-------------------------------------------
class Object 
{
    char mark;
    int x;
    int y;
    int hp;
    
    const int id;
    const shared_ptr<Crown> crown;

    static int count_ob;
    static int cur_amount;

public:     
    Object(shared_ptr<Crown> crown, istream &in); 
    Object(shared_ptr<Crown> crown, char &mark, int &x, int &y, int &hp); 
    Object(Object const &ob);    
    Object(Object&& ob);
    ~Object();

    void read_obj(fstream &f, int id);
    void damage(int damage);
    bool alive();
    int which_army();
    bool check_crown();

    void print_ob();
    void print_ob_simple();
    
    virtual char draw(); 

    char &getmark();
    int &getx();
    int &gety();
    int &gethp();
    const int getid();
    int &get_cur_amount();
    const int &getid() const;
    const shared_ptr<Crown> getcrown();
    
    virtual int move_to(char action, int border_x, int border_y){}  
    // virtual int attack(){}  
    virtual int& getpower(){}  
    virtual vector<pair<int, int>> &getlocation() {}
    

    Object &operator=(Object&& ob);
    Object &operator=(Object &ob);
    bool operator==(Object const &ob);

    friend istream &operator>>(istream &in, Object &ob);
    friend ostream &operator<<(ostream &out, Object &ob);
};
//-----------------------------------------------------------------------------------------


//---------------------------------OBJECT-METHODS------------------------------------------
void Object::print_ob() {
    cout << "Object:"<< endl 
         << "    x = " << x << endl
         << "    y = " << y << endl
         << "    hp = " << hp << endl
         << "    crown = " << crown->getcolor() << endl
         << "    id = " << id << endl
         << "Object." <<endl; 
}

Object::Object(shared_ptr<Crown> crown, istream &in): id(count_ob++), crown(crown){ 
    in >> *this; 
    cur_amount++;
    print_ob(); 
}

Object::Object(shared_ptr<Crown> crown, char &mark, int &x, int &y, int &hp): 
            id(count_ob++), crown(crown), mark(mark), x(x), y(y), hp(hp){ 
    print_ob(); 
}

Object::~Object(){
    cout << "~Object:"<< endl 
            << "    x = " << x << endl
            << "    y = " << y << endl
            << "    hp = " << hp << endl
            << "    crown = " <<crown->getcolor() << endl
            << "    id = " << id << endl
        << "~Object." <<endl;
    cur_amount--;
}   

Object::Object(Object const &ob): 
    id(ob.id), 
    crown(ob.crown), 
    mark(ob.mark), 
    x(ob.x), 
    y(ob.y), 
    hp(ob.hp){cout<<"const&ob\n";}

Object::Object(Object&& ob): 
    id(move(ob.id)), 
    crown(move(ob.crown)), 
    mark(move(ob.mark)), 
    x(move(ob.x)), 
    y(move(ob.y)), 
    hp(move(ob.hp)){cout<<"&&\n";}

Object &Object::operator=(Object&& ob){
    mark = move(ob.mark); 
    x = move(ob.x); 
    y = move(ob.y);
    hp = move(ob.hp);
    return *this; cout <<"op=\n";
}

Object &Object::operator=(Object &ob){
    if(this != &ob){
        mark = move(ob.mark); 
        x = move(ob.x); 
        y = move(ob.y);
        hp = move(ob.hp);
    }
    return *this; cout <<"&&op=\n";
}

bool Object::operator==(Object const &ob){ cout <<"op==\n";
    return (ob.x == x && ob.y == y);
}

void Object::damage(int damage) { 
    hp -= damage; 
}

bool Object::alive(){
    return (hp > 0);
}

char Object::draw(){
    if(alive()) return 'o'; 
    else if(!alive()) return 'x';
} 

int Object::which_army(){
    if(crown->getcolor() == "green") return 1;
    if(crown->getcolor() == "red")return 0;    
}

void Object::print_ob_simple() { 
    cout << "[ " << mark << " " << id << " " << x << " " << y << " "<< hp << " ]" << endl; 
}

char &Object::getmark()
    {return mark;}

int &Object::getx()
    {return x;}

int &Object::gety()
    {return y;}

int &Object::gethp()
    {return hp;} 

const int Object::getid()
    {return id;} 

const int &Object::getid() const
    {return id;}   

int &Object::get_cur_amount()
    {return cur_amount;}

const shared_ptr<Crown> Object::getcrown()
    {return crown;}
       

istream &operator>>(istream &in, Object &ob){
    in >> ob.mark >> ob.hp >> ob.x >> ob.y; 
    return in;
}

ostream &operator<<(ostream &out, Object &ob){
    if(ob.crown->getcolor() ==  "green" ) 
        out << "\033[32m";
    if(ob.crown->getcolor() == "red")
        out << "\033[31m";
    out << ob.draw() << "\033[0m";
    return out;
}   

//-----------------------------------------------------------------------------------------
#endif //OBJECT
