/*
	Abigail Bashore
	March 13, 2017
	Homework 8
	Cube implementation
*/

#ifndef Cube_h
#define Cube_h

#include "Shape.h"

class Cube : public Shape{
public:
	Cube(Point3D c, float r) :center(c), radius(r) {}
	bool InsideShape(Point3D p){
		// 6 edges of the cube
		
		double pXEdge = center.x + radius;
		double nXEdge = center.x - radius;
		double pYEdge = center.y + radius;
		double nYEdge = center.y - radius;
		double pZEdge = center.z + radius;
		double nZEdge = center.z - radius;

		return((p.x <= pXEdge) &&
			   (p.x >= nXEdge) &&
			   (p.y <= pYEdge) &&
			   (p.y >= nYEdge) &&
			   (p.z <= pZEdge) &&
			   (p.z >= nZEdge));
	}

		
private:
	Point3D center;
	float radius;
};	


#endif /* Cube_h */
