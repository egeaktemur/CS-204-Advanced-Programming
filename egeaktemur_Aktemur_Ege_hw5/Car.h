#ifndef CAR
#define CAR

class Car {
private:
	double fuel;
	int insurance;
	int totaldistance;
public:
	Car();
	// Constructor
	Car(int,int,int);
	
	// Member functions
	void display();
	double getfuel();
	int getinsurance();
	int gettotaldistance();
	void setfuel(double);
	void setinsurance(int);
	void settotaldistance(int);
};
#endif