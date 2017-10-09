/*
	Abigail Bashore
	March 13, 2017
	Homework8
	VoxelShape implementation
*/
#include <cmath>
#include "VoxelShape.h"
#include "BitVector.h"

// constructor
VoxelShape::VoxelShape(int x, int y, int z) :map(x*y*z){
    nx = x;
    ny = y;
    nz = z;
}    

// destructor
VoxelShape::~VoxelShape(){
	nx = 0;
	ny = 0;
	nz = 0;

}
// see BitVector for implmentation below
void VoxelShape::fill(){
	map.fill();
}
void VoxelShape::clear(){
	map.clear();
}

bool VoxelShape::get_bit(int x, int y, int z) const{
	return map.get_bit(get_index(x, y, z));
}
void VoxelShape::set_bit(int x, int y, int z){
	map.set_bit(get_index(x, y, z));
}
void VoxelShape::clear_bit(int x, int y, int z){
	map.clear_bit(get_index(x, y, z));
}
void VoxelShape::toggle_bit(int x, int y, int z){
	map.toggle_bit(get_index(x, y, z));
}

// getter methods
int VoxelShape::get_index(int x, int y, int z) const{
	int index = (((ny) * (nz)) * x) + ((nz) * y) + z; 
	return index;
}
void VoxelShape::getXYZ(int index, int &x, int &y, int &z) const{
	x = index / ny * nz;
	y = (index % (ny * nz))/ nz;
	z = index % nz;
}

int VoxelShape::get_x() const{ return nx;}
int VoxelShape::get_y() const{ return ny;}
int VoxelShape::get_z() const{ return nz;}


// sphere methods
void VoxelShape::add_sphere(float cx, float cy, float cz, float radius){
	for(int x = 0; x < nx; x++){
		for(int y = 0; y < ny; y++){
			for(int z = 0; z < nz; z++){
				if( ((x - cx) * (x - cx)) + ((y - cy) * (y - cy)) + ((z - cz) * (z - cz)) < radius * radius){
					set_bit(x, y, z);
				}

			}
		}
	}
}
void VoxelShape::subtract_sphere(float cx, float cy, float cz, float radius){
	for(int x = 0; x < nx; x++){
		for(int y = 0; y < ny; y++){
			for(int z = 0; z < nz; z++){
				if( ((x - cx) * (x - cx)) + ((y - cy) * (y - cy)) + ((z - cz) * (z - cz)) < radius * radius){
					clear_bit(x, y, z);
				}

			}
		}
	}
}
void VoxelShape::toggle_sphere(float cx, float cy, float cz, float radius){
	for(int x = 0; x < nx; x++){
		for(int y = 0; y < ny; y++){
			for(int z = 0; z < nz; z++){
				if( ((x - cx) * (x - cx)) + ((y - cy) * (y - cy)) + ((z - cz) * (z - cz)) < radius * radius){
					toggle_bit(x, y, z);
				}

			}
		}
	}
}
