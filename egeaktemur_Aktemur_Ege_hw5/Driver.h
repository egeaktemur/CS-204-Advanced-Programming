#ifndef DRIVER
#define DRIVER
#include "Car.h"
#include <string>

class Driver{
private:
	Car &car;
	double budget;
public:
	// Constructor
	Driver(Car & car,double budget);
	// Functions
	void drive (double);
	void repairCar(std::string);
	void display();
	void fullFuel();
};

#endif