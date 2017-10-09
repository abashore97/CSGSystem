/*
	Abigail Bashore
	March 13, 2017
	Homework 8
	Sphere implementation
*/
#ifndef Sphere_h
#define Sphere_h
#include "Shape.h"
#include <iostream>
class Sphere : public Shape{
public:
	Sphere(Point3D c, float r) :center(c), radius(r) {}
	bool InsideShape(Point3D p){

	if(((p.x - center.x) * (p.x - center.x)) + ((p.y - center.y) * (p.y - center.y)) + ((p.z - center.z) * (p.z - center.z)) < (radius * radius)){
				
		return true;
		}
		
	return false;
	}	


private:
	Point3D center;
	float radius;
};




#endif /* Sphere_h */
