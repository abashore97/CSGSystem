/*
	Abigail Bashore
    March 13, 2017
	Homework8
	BitVector header

*/

#include <stdint.h>
#include "MyArray.h"
#ifndef BitVector_h
#define BitVector_h

class BitVector{
public:
	BitVector(int n);
	~BitVector();
	void clear();
	void fill();
	bool get_bit(int index) const;
	void set_bit(int index);
	void toggle_bit(int index);
	void clear_bit(int index);
	int get_size() const;
	int get_byte_number(int index) const;
	uint8_t get_bit_number(int index) const;

private:
	int size;
	MyArray<uint8_t>* bitmap;
};


#endif /* BitVector_h */
