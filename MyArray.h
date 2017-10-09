/*
	Abigail Bashore
	March 13, 2017
	Homework8 
	Resizeable array class definition
*/

#ifndef MyArray_h
#define MyArray_h

#include <stdint.h>
#include <iostream>
template <typename T>
class MyArray {
public:
	MyArray(int capacity = 20);
	MyArray(const MyArray<T> &);
	MyArray<T> &operator=(const MyArray<T> &);
	~MyArray();
	T getItem(int index) const;
	void setItem(int index, T item);
	int getSize() const;
	int getCapacity() const;
	void resize(int newSize);
	void pushBack(T item);
	T back() const;
	void popBack();

private:
	T * container;
	int size;
	int capacity;

};

template <typename T>
MyArray<T>::MyArray(int c) {
	if(c <= 20){
		container = new T[20];
	}
	else{
		container = new T[c];
	}

	size = 0;
	capacity = c;
	
	
}

template <typename T>
MyArray<T>::~MyArray(){
	delete[] container;
	container = nullptr;
	size = 0;
	capacity = 0;
}

template <typename T>
MyArray<T>::MyArray(const MyArray<T> &s){
	container = new T[s.size];

	for(int i = 0; i < s.size; i++){
		container[i] = s.container[i];
	}

	capacity = s.size;
	size = s.size;



}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T> &s){
	T* copyContainer = new T[s.size];

	for(int i = 0; i < s.size; i++){
		copyContainer[i] = s.container[i];
	}

	delete[] container;
	container = copyContainer;
	capacity = s.size;
	size = s.size;
	return *this;
}

template <typename T>
int MyArray<T>::getSize() const{
	return size;
}
template <typename T>
int MyArray<T>::getCapacity() const{
	return capacity;
}

template <typename T>
T MyArray<T>::getItem(int index) const{
	return container[index];
}

template <typename T>
void MyArray<T>::setItem(int index, T item){
	container[index] = item;
	
}

template <typename T>
void MyArray<T>::resize(int newCapacity){

	T * newC = new T[newCapacity];

	for(int i = 0; i < size; i++){
		newC[i] = container[i];
	}

	delete[] container;
	container = newC;
	capacity = newCapacity;

}
template <typename T>
T MyArray<T>::back() const{
	return container[size - 1];
}

template <typename T>
void MyArray<T>::pushBack(T item){
	
	if(size >= capacity){
		this->resize(capacity*2);
		container[size] = item;
	}
	else{
		container[size] = item;
	}
	
	size++;
}

template <typename T>
void MyArray<T>::popBack(){
	container[size] = 0;
	size--;
}

#endif /* MyArray_h */
