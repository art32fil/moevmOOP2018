#ifndef ITER_H
#define ITER_H

template <typename T>
class Iterator {
	///friend class List<T>;
private:
	//const List<T> *data;
	Elem<T>	*cur;
public:
	Iterator(): cur(NULL) {}
	Iterator(Elem<T> *elem): cur(elem) {}


	T& operator*();
	Elem<T>* operator->();
	Iterator<T> operator++(int); //postfix
	Iterator<T> operator--(int); //postfix
	Iterator<T>& operator++(); //prefix
	Iterator<T>& operator--(); //prefix
	bool operator!=(const Iterator<T>& iter);
	bool operator==(const Iterator<T>& iter);
	Iterator<T>& operator=(const Iterator<T>& equal);

	//friend Iterator<T>& operator+(const Iterator<T>& left, const Iterator<T>& right);
	//friend Iterator<T>& operator-(const Iterator<T>& left, const Iterator<T>& right);

};
//------------------------------------------------

template <typename T>
Iterator<T>& Iterator<T>::operator++() //prefix
{
	cur=cur->next;
	return *this;
}

//------------------------------------------------
template <typename T>
Iterator<T> Iterator<T>::operator++(int) //postfix
{

		Iterator<T> tmp(cur);
		//++(*this);
		cur=cur->next;
		return tmp;

}
//------------------------------------------------
template <typename T>
Iterator<T>& Iterator<T>::operator--() //prefix
{
	 cur=cur->prev;
	return *this;

}
//------------------------------------------------
template <typename T>
Iterator<T> Iterator<T>::operator--(int) //postfix
{

		Iterator<T> tmp(cur);
		cur=cur->prev;
		return tmp;
}
//------------------------------------------------
template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& equal)
{
	if(&equal==this) return *this;
	cur=equal.cur;
	return *this;
}
//------------------------------------------------
template <typename T>
T& Iterator<T>::operator*()
{
	return cur->info;
}
//------------------------------------------------
/*template <typename T>
T& Iterator<T>::operator->()
{
	return cur->info;
}*/
//------------------------------------------------
template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& iter)
{
	return (cur==iter.cur);
}
//------------------------------------------------
template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& iter)
{
	return !(*this==iter);
}


template <typename T>
Elem<T>* Iterator<T>::operator->()
{
	return cur;
}


#endif
