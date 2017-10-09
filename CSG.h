/*
    Abigail Bashore
    March 13, 2017
    Homework 8
    CSG Header 
*/
#ifndef CSG_h
#define CSG_h

#include "Shape.h"
#include <vector>

enum op{
	ADD,
	SUB,
	MASK,
	TOGGLE
};
struct step{
	Shape* shape; 
	op instruction;
	step(Shape* s, op i) :shape(s), instruction(i) {}

};
class CSG{
public:
	CSG();
    ~CSG();
	CSG &operator=(Shape*) = delete;
	CSG(const CSG&) = delete;
    void RenderToFile(const char* filename, Point3D min, Point3D max, float widthInInches, int voxelsperInch = 256);
    void Add(Shape*);
    void Subtract(Shape*);
    void Mask(Shape*);
    void Toggle(Shape*);

    CSG &operator+=(Shape*);
    CSG &operator-=(Shape*);
    CSG &operator&=(Shape*);
    CSG &operator^=(Shape*);

	
private:
	std::vector<step> model;
};

#endif /* CSG_h */
