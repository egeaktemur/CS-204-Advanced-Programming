#include <iostream>
#include "Driver.h"
#include "Car.h"
#include <string>
using namespace std;

//************************************************
// Constructor to generate an object             *
//************************************************
Driver::Driver(Car &c,double b)
	: car(c), budget(b)
{ }

//************************************************
// Reduces the given km*0.25 from the fuel and   *
// adds to the total distance                    *
//************************************************
void Driver::drive(double km){
	car.setfuel(car.getfuel()-(km*0.25));
	car.settotaldistance(car.gettotaldistance()+km);
}

//****************************************************
// The repairCar(string) function is called by one   *
// of the drivers, the budget of the driver should   *
// reduce 50$ for SMALL accidents, 150$ for          *
// MEDIUM accidents, and 300$ for LARGE accidents.   *
// In each accident, the insurance fee of the car    *
// should increase by 5%, 10% and 20% for SMALL,     *
// MEDIUM, and LARGE accidents, respectively.        *
//****************************************************
void Driver::repairCar(string accident){
	int cost;
	if ( accident == "SMALL"){
		cost = 50;
		budget = budget - cost;
		car.setinsurance(car.getinsurance()*105/100);
	}
	else if ( accident == "MEDIUM"){
		cost = 150;
		budget = budget - cost;
		car.setinsurance(car.getinsurance()*110/100);
	}
	else if ( accident == "LARGE"){
		cost = 300;
		budget = budget - cost;
		car.setinsurance(car.getinsurance()*120/100);
	}
	cout << cost << "$ is reduced from the driver's budget because of the "<< accident<<" accident"<<endl;
	cout << "Yearly insurance fee is increased to "<<car.getinsurance() <<" because of the "<< accident<<" accident"<<endl;
}

//****************************************************
// Displays the budget                               *
//****************************************************
void Driver::display(void){
	cout << "Driver Budget: " << budget << endl;
}

//****************************************************
// Fulls the fuel                                    *
//****************************************************
void Driver::fullFuel(void){
	budget = budget - (300-car.getfuel());
	car.setfuel(300);
	cout << "Fuel is full" << endl;
}

