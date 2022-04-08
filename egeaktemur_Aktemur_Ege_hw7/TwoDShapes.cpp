#include "TwoDShapes.h"
float TwoDShape::volume(){
	return 0;
}

float rectangle::perimeter(){
	return 2*(Width+Length);
}

float rectangle::area(){
	return (Width*Length);
}