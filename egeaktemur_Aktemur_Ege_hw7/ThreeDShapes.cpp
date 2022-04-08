#include "ThreeDShapes.h"
float ThreeDShape::perimeter(){
	return 0;
}

float box::volume(){
	return Width*Length*Height;
}

float box::area(){
	return 2 * (Width*Length + Width*Height + Length*Height);
}