#include <iostream>
#include "Car.h"
using namespace std;

Car::Car(){
	fuel=0;
	insurance=0;
	totaldistance=0;
}
//************************************************
// Constructor. Generates an object with given   *
// values                                        *
//************************************************
Car::Car(int i1,int i2,int i3){
	fuel=i1;
	insurance=i2;
	totaldistance=i3;
}

//********************************************
// Displays the object                       *
//********************************************
void Car::display(){       
	cout <<	"Fuel Level: "<< fuel << endl;
	cout << "Insurance Fee: "<< insurance << endl;
	cout << "Total distance that the car has travelled: "<< totaldistance << endl << endl;
}

//********************************************
// Returns the fuel                          *
//********************************************
double Car::getfuel(){
	return fuel;
}

//********************************************
// Returns the insurance                     *
//********************************************
int Car::getinsurance(){
	return insurance;
}

//********************************************
// Returns the total distance                *
//********************************************
int Car::gettotaldistance(){
	return totaldistance;
}

//********************************************
// Sets the fuel to the given value          *
//********************************************
void Car::setfuel(double i){
	fuel=i;

}

//********************************************
// Sets the insurance to the given value     *
//********************************************
void Car::setinsurance(int i){
	insurance=i;
}

//********************************************
// Sets the total fuel to the given value    *
//********************************************
void Car::settotaldistance(int i){
	totaldistance=i;
}
