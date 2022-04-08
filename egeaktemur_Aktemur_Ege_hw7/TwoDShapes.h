#ifndef TWODSHAPE_H
#define TWODSHAPE_H
#include <string>
#include "shape.h"

class TwoDShape: public shape {
public:
	// Constructor.
	TwoDShape(std::string name):shape(name){}
	
	// Member functions.
	virtual float volume(); // To define volume as 0
protected:

};

class rectangle: public TwoDShape {
public:
	// Constructor.
	rectangle(float width,float length,std::string name):TwoDShape(name){
		Width = width;
		Length = length;
	}
	
	// Member functions.
	virtual float perimeter(); // To define perimeter
	virtual float area(); // To define area
protected:
	float Width;
	float Length;
};
#endif
