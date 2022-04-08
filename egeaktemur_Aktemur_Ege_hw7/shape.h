#ifndef SHAPE_H
#define SHAPE_H
#include <string>

class shape {

public:
	// Constructor.
	shape(std::string N){
		MyName = N;
	}
	
	// Member functions.
	virtual float perimeter() = 0; // To make them pure virtual I used = 0
	virtual float area() = 0;
	virtual float volume() = 0;
	std::string getName();
protected:
	std::string MyName;
};

#endif
