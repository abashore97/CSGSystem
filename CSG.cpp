/*
	Abigail Bashore
	March 13, 2017
	Homework 8
	CSG implementation
*/
#include "CSG.h"
#include "VoxelShape.h"
#include "Shape.h"
#include "surfaceExtraction.hpp"
#include <iostream>
#include <cmath>
CSG::CSG() {}

CSG::~CSG(){
	for(auto i = model.begin(); i != model.end(); ++i){
	  delete (*i).shape;
	}

}

void CSG::RenderToFile(const char* filename, Point3D min, Point3D max, float widthInInches, int voxelsPerInch){
	float xVoxels = widthInInches * voxelsPerInch;
	float yVoxels = (xVoxels/(max.x - min.x)) * (max.y - min.y);
	float zVoxels = (yVoxels/(max.y - min.y)) * (max.z - min.z);	
	
	double rx = 0.0;
	double ry = 0.0;
	double rz = 0.0;
	

	VoxelShape m(xVoxels, yVoxels, zVoxels);
	for(auto i = model.begin(); i != model.end(); ++i) {
		Shape* current = (*i).shape;
		for(int x = 0; x < xVoxels; x++){
			for(int y = 0; y < yVoxels; y++){
				for(int z = 0; z < zVoxels; z++){
					rx = x * ((max.x - min.x)/(xVoxels - 1)) + min.x;
					ry = y * ((max.y - min.y)/(yVoxels - 1)) + min.y;
					rz = z * ((max.z - min.z)/(zVoxels - 1)) + min.z;
					
					Point3D currentPoint(rx, ry, rz);

					op currentInstruction = (*i).instruction;
					if(current->InsideShape(currentPoint)){
						switch(currentInstruction){
							case ADD:
								m.set_bit(x, y, z);
								break;
							case SUB:
								m.clear_bit(x, y, z);
								break;
							case MASK:
								break;
							case TOGGLE:
								m.toggle_bit(x, y, z);
								break;

						}
					}

					else{
						if(currentInstruction == MASK){
							m.clear_bit(x, y, z);
						}
					}
					
				}
			}
		}
	}
	writeSTL(m, filename, 4);

}
void CSG::Add(Shape* s){
	step a(s, ADD);
	model.push_back(a);
}

void CSG::Subtract(Shape* s){
	step b(s, SUB);
	model.push_back(b);
}

void CSG::Mask(Shape* s){
	step c(s, MASK);
	model.push_back(c);
}

void CSG::Toggle(Shape* s){
	step d(s, TOGGLE);
	model.push_back(d);
}

CSG& CSG::operator+=(Shape* s){
	Add(s);
	return *this;
}

CSG& CSG::operator-=(Shape* s){
	Subtract(s);
	return *this;
}

CSG& CSG::operator&=(Shape* s){	
	Mask(s);
	return *this;
}

CSG& CSG::operator^=(Shape* s){
	Toggle(s);
	return *this;
}



