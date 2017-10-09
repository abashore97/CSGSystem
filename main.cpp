/*
	Abigail Bashore
	March 13, 2017
	Homework 8
	main.cpp
*/
#include "CSG.h"
#include "Sphere.h"
#include "Shape.h"
#include "Cube.h"
int main(int argc, const char* argv[]){
	// testing with making a die
	CSG csg;
	Point3D middle = {0.0, 0.0, 0.0};
	Point3D lb = {-1, -1, -1};
	Point3D ub = {1, 1, 1};
	
	csg += new Cube(middle, 1.0);

	// one 
	csg -= new Sphere({0.0, 1.0, 0.0}, 0.2);
	
	// two
	csg -= new Sphere({1.0, -0.5, 0.5}, 0.2);
	csg -= new Sphere({1.0, 0.5, -0.5}, 0.2);

	// three
	csg -= new Sphere({-0.5, 0.5, -1.0}, 0.2);
	csg -= new Sphere({0.5, -0.5, -1.0}, 0.2);
	csg -= new Sphere({0.0, 0.0, -1.0}, 0.2);

	// four
	csg -= new Sphere({0.5, -1.0, 0.5}, 0.2);
	csg -= new Sphere({-0.5, -1.0, 0.5}, 0.2);
	csg -= new Sphere({-0.5, -1.0, -0.5}, 0.2);
	csg -= new Sphere({0.5, -1.0, -0.5}, 0.2);

	// five
	csg -= new Sphere({-1.0, 0.0, 0.0}, 0.2);
	csg -= new Sphere({-1.0, 0.5, 0.5}, 0.2);	
	csg -= new Sphere({-1.0, -0.5, -0.5}, 0.2);	
	csg -= new Sphere({-1.0, -0.5, 0.5}, 0.2);	
	csg -= new Sphere({-1.0, 0.5, -0.5}, 0.2);	

	// six 
	csg -= new Sphere({-0.5, 0.5, 1.0}, 0.2);
	csg -= new Sphere({0.5, -0.5, 1.0}, 0.2);
	csg -= new Sphere({0.5, 0.5, 1.0}, 0.2);
	csg -= new Sphere({-0.5, -0.5, 1.0}, 0.2);
	csg -= new Sphere({0.0, 0.5, 1.0}, 0.2);
	csg -= new Sphere({0.0, -0.5, 1.0}, 0.2);

	csg.RenderToFile("extracredit.stl", lb, ub, 2.0, 128);

	return 0;
}
