#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H
#include <string>
#include "shape.h"

class ThreeDShape: public shape {
public:
	// Constructor.
	ThreeDShape(std::string name):shape(name){}
	
	// Member functions.
	virtual float perimeter(); // To define perimeter as 0
protected:

};

class box: public ThreeDShape {
public:
	// Constructor.
	box(float width,float length,float height,std::string name):ThreeDShape(name){ // Used ThreeDShape constructer
		Width = width;
		Length = length;
		Height = height;
	}
	// Member functions.
	virtual float volume(); // To define volume
	virtual float area(); // To define area
protected:
	float Width;
	float Length;
	float Height;
};
#endif

