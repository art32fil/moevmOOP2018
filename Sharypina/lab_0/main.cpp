#include "list.h"
#include "iter.h"

using namespace std;

int main() {

	List<int> vec;

	vec.add_head(5);
	vec.add_head(3);
	vec.add_tail(4);


	cout << "size of list = "<<vec.size() << endl;
	cout<<"show list:\n";

	vec.show();
	cout << "-------------" << endl;
	cout<<"show list:\n";
	vec.add_num(2, 1);

	vec.show();
	cout << "-------------" << endl;
	cout << "size of list = "<<vec.size() << endl;
	cout<<"elem[3]=";
	cout << vec[3] << endl;
	cout << "-------------" << endl;

	cout<<"*iterator\n";
	Iterator<int> iter=vec.begin();
	cout<<*iter<<endl;

	cout<<"postfix++\n";
	iter++;
	cout<<*iter<<endl;

	cout<<"prefix++\n";
	++iter;
	cout<<*iter<<endl;

	cout<<"postfix--\n";
	iter--;
	cout<<*iter<<endl;

	cout<<"equal\n";
	Iterator<int> seconditer=iter;
	cout<<*seconditer<<endl;
	cout << "-------------" << endl;

	vec.delete_head();
	vec.show();
	cout << "-------------" << endl;
	cout<<"add_tail(7)\n";
vec.add_tail(7);
cout<<"add_tail(9)\n";
vec.add_tail(9);
vec.show();
cout << "-------------" << endl;
cout<<"delete tail\n";
vec.delete_tail();
vec.show();
cout << "-------------" << endl;
cout<<"delete 1th elem\n";
vec.delete_num(1);
vec.show();
cout << "-------------" << endl;
//--------------------------------------
cout<<"iterator test 1\n";


for(iter=vec.begin(); iter!=vec.end(); iter++)
{
	cout<<*iter<<endl;
}

cout << "-------------" << endl;
//--------------------------------------
cout<<"iterator test 2\n";
for(Elem<int> elem: vec)
{
	cout<<elem.get_value()<<endl;
}
//--------------------------------------
cout << "-------------" << endl;

//Iterator<int> *it(vec);
//cout<<"->\n"<< it->get_value()<<endl;

cout<<"->\n"<<vec.begin()->get_value()<<endl;


	cout << "----------------------" <<endl;
	auto it = vec.begin();
  (it++)++;
	cout << it->get_value() <<endl;


	return 0;
}
