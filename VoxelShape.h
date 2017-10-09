/*
	Abigail Bashore
	March 13, 2017
	Homework8
	VoxelShape class declaration
*/

#include "BitVector.h"
#ifndef VoxelShape_h
#define VoxelShape_h
#include <iostream>
class VoxelShape{
public:
	VoxelShape(int x, int y, int z);
	~VoxelShape();
	void fill();
	void clear();
	bool get_bit(int x, int y, int z) const;
	void set_bit(int x, int y, int z);
	void toggle_bit(int x, int y, int z);
	void clear_bit(int x, int y, int z);
	void add_sphere(float cx, float cy, float cz, float radius);
	void subtract_sphere(float cx, float cy, float cz, float radius);
	void toggle_sphere(float cx, float cy, float cz, float radius);
	int get_x() const;
	int get_y() const;
	int get_z()const;
private:
	int nx, ny, nz;
	BitVector map;
	int get_index(int x, int y, int z) const;
	void getXYZ(int index, int &x, int &y, int &z) const;
};


#endif /* VoxelShape_h */
