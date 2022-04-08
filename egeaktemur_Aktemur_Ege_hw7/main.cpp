/**Artrim Kjamilji, 20.12.2021**/

/*include all the necessary files, libraries, etc. here, if any*/
#include <iostream>
#include <string>
#include "shape.h"
#include "TwoDShapes.h"
#include "ThreeDShapes.h"
using namespace std;
/*if you choose not to write the 5 required classes in seperate .h and .cpp files, then write them here*/

shape *getShape() {
	int option = 0;
	while ( option != 1 && option != 2 ) { //get input
		cout << endl;
		cout << "Choose an option (1 or 2):"<<endl;
		cout << "1. Rectangle" << endl;
		cout << "2. Box" << endl;
		cin >> option;
		if ( option != 1 && option != 2 ){
			cout << "UNAVAIBLE OPTION CHOSEN. Try again." << endl;
		}
	}
	if ( option == 1 ){ // If rectangle is chosen create a rectangle object and return it
		cout << "You choose rectangle. Give it's width, length and name;" << endl;
		float width,length;
		string name;
		cin >> width;
		cin >> length;
		cin >> name;
		rectangle *new_shape = new rectangle(width,length,name);

		return new_shape;
	}
	else { // If box is chosen create a box object and return it
		cout << "You choose box. Give it's width, length, height and name;" << endl;
		float width,length,height;
		string name;
		cin >> width;
		cin >> length;
		cin >> height;
		cin >> name;
		box *new_shape = new box(width,length,height,name);

		return new_shape;
	}
}//getShape()


int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISON PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;

		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter() == shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area() == shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume() == shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
		{
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		}
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}