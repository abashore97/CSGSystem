/*
	Abigail Bashore
	March 13, 2017
	Homework8
	BitVector class implementation
*/

#include <stdint.h>
#include "BitVector.h"
#include <iostream> 
// constructor
BitVector::BitVector(int n){
	size = n;

	if((size % 8) != 0){
		bitmap = new MyArray<uint8_t>((size / 8) + 1);
	}
	else{
		bitmap = new MyArray<uint8_t>((size / 8));
	}
}

// destructor
BitVector::~BitVector(){
	delete bitmap;
	bitmap = nullptr;
	size = 0;
}

// sets all the bits to 0
void BitVector::clear(){
	int length = 0;
	if((size % 8) != 0){
		length = (size / 8) + 1;
	}
	else{
		length = (size / 8);
	}

	for(int i = 0; i < length ; i++){
		bitmap->setItem(i, 0);
	}
}

// set all the bits to 1
void BitVector::fill(){
	int length = 0;
	if((size % 8) != 0){
		length = (size / 8) + 1;
	}
	else{
		length = (size / 8);
	}
	for(int i = 0; i < length; i++){
		bitmap->setItem(i, -1);
	}
}

// gets a bit in a bit vector
bool BitVector::get_bit(int index) const{
	int byte_number = get_byte_number(index);
	uint8_t bit_number = get_bit_number(index);
	uint8_t section = bitmap->getItem(byte_number);
	if((( section >> bit_number) & 1) == 0){
		return false;
	} 
	
	return true;
	
}
// sets a bit in a bit vector at the specified index.
void BitVector::set_bit(int index){
	int byte_number = get_byte_number(index);
	uint8_t bit_number = get_bit_number(index); 

	uint8_t value = 1; 

	value = value << bit_number; 

	uint8_t section = bitmap->getItem(byte_number); 

	section |= value; 
	bitmap->setItem(byte_number, section); 

}
// turns the bit off if it is already on. If it is already off, it will stay off. 
void BitVector::clear_bit(int index){
	int byte_number = get_byte_number(index);
	uint8_t bit_number = get_bit_number(index);

	uint8_t value = 1;

	value = value << bit_number;
	value = ~value;

	uint8_t section = bitmap->getItem(byte_number);

	section &= value;
	bitmap->setItem(byte_number, section);


}
// toggles the bit on or off
void BitVector::toggle_bit(int index){
	int byte_number = get_byte_number(index);
	uint8_t bit_number = get_bit_number(index);

	uint8_t value = 1;

	value = value << bit_number;

	uint8_t section = bitmap->getItem(byte_number);

	section ^= value;
	bitmap->setItem(byte_number, section);

}

// returns the number of bits in a bit vector
int BitVector::get_size() const{
	return size;
}

// helper methods to navigate through a bit vector

// retrieves 
int BitVector::get_byte_number(int index) const{
	return index / 8;
}

uint8_t BitVector::get_bit_number(int index) const{
	return index % 8;
}


