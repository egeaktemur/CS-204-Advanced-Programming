#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynstringStack.h"
#include "DynStringQueue.h"
#include "InstructorQueue.h"
#include "linkedlist.h"
using namespace std;

extern functions *functionshead = new functions("",NULL,NULL);
DynStringQueue studentsQueue;
InstructorQueue instructorsQueue;
DynstringStack stack;

// Returns first or second part of the given word such as "define" "a"
string Part(string command,string part){
	if (part == "first"){
		return command.substr(0 , command.find(" "));
	}
	else if (part == "second"){
		return command.substr(command.find(" ")+1,-1);
	}
}

void processARequest(string functionName) { 
	function * ptr = Function(functionshead,functionName);
	// Returns linked list of the given function.
	int i=0; // count of how many elements defined
	while (ptr != NULL) { 
		string step = ptr->step;
		if(Part(step,"first") == "define") { 
			i++;
			stack.push(step);
			//process the define command 
		} else if (Part(step,"first") == "call") { 
			cout << "Calling " << Part(step,"second") << " from " << functionName << endl;
			processARequest(Part(step,"second")); 
		} else {
			//print the stack … 
			cout << "PRINTING THE STACK TRACE:" << endl;
			if(stack.isEmpty()){
				cout << "The stack is empty" << endl;
			}
			DynstringStack tempstack;
			string temp;
			while( !stack.isEmpty() ){ 
				// While stack is not empty add each element to another stack
				stack.pop(temp);
				tempstack.push(temp);
			}
			while( !tempstack.isEmpty() ){
				// Then print each element of tempstack and add to stack again
				tempstack.pop(temp);
				cout << functionName << ": " << temp << endl;
				stack.push(temp);
			}
		}
		ptr = ptr->next;
	}// delete this function’s data from the top of the stack 
	cout<<functionName<<" is finished. Clearing the stack from it's data... " <<endl; 
	string temp;
	while( i > 0 ){ // Delete i many elements which is the amount of elements added in particular recursion
		stack.pop(temp);
		i = i - 1;
	}
	system("pause"); 
} 

void processARequest() { 
	string functionName;
	if (!instructorsQueue.isEmpty()) {
		//if instruc tors queue is not empty, process the next request 
		string arr[3];
		// arr holds instructor name id and function name in order
		instructorsQueue.dequeue(arr);
		// Get first element of the queue
		cout << "Processing instructors queue..." << endl;
		cout << "Processing prof." << arr[0] << "'s request (with ID " << arr[1] << ") of service (function):" << endl;
		cout << arr[2] << endl;
		processARequest(arr[2]); 
		// Check if the stack is empty in the end
		if(stack.isEmpty()){
			cout << "The stack is empty" << endl;
			cout << "GOING BACK TO MAIN MENU" << endl;
		}
		else{
			cout << "The stack is not empty" << endl;
		}
	} 
	else if (!studentsQueue.dynisEmpty()) { 
		//if instructors queue is empty and student’s not, 
		//then process the next student request 
		string arr[3];
		studentsQueue.dyndequeue(arr);
		// arr holds student name id and function name in order
		cout << "Processing students queue..." << endl;
		cout << "Processing " << arr[0] << "'s request (with ID " << arr[1] << ") of service (function):" << endl;
		cout << arr[2] << endl;
		processARequest(arr[2]); 
		if(stack.isEmpty()){
			cout << "The stack is empty" << endl;
			cout << "GOING BACK TO MAIN MENU" << endl;
		}
		else{
			cout << "The stack is not empty" << endl;
		}
	}
	else { 
		// otherwise… 
		cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl
			<< "GOING BACK TO MAIN MENU" << endl; 
	} 
}

void addInstructorRequest(){
	if(instructorsQueue.isFull()){ // Check if queue is full
		cout << "Instructor Queue is curently full" << endl;
		return;
	}
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	string functionname , instructorname , instructorid;
	cin >> functionname;
	if( !DoesfunctionExist(functionshead,functionname) ){ // Check if function does not exist
		cout << "Requested service (function) does not exists" << endl;
		cout <<"GOING BACK TO MAIN MENU" << endl; 
		return;
	}
	cout << "Give instructor's name: ";
	cin >> instructorname;
	cout << "Give instructor's ID (an int): ";
	cin >> instructorid;
	string arr[3];
	arr[0] = instructorname;
	arr[1] = instructorid;
	arr[2] = functionname;
	instructorsQueue.enqueue(arr); // Add the array to queue
	cout << "Prof. " << instructorname << "'s service request of " << functionname << " has been put in the instructor's queue." << endl;
	cout << "Waiting to be served..." << endl;
}

void addStudentRequest() {
	cout << "Add a service (function) that the student wants to use:" << endl;
	string functionname , studentname , studentid;
	cin >> functionname;
	if( !DoesfunctionExist(functionshead,functionname) ){ // Check if function does not exist
		cout << "Requested service (function) does not exists" << endl;
		cout << "GOING BACK TO MAIN MENU" << endl; 
		return;
	}
	cout << "Give student's name: ";
	cin >> studentname;
	cout << "Give student's ID (an int): ";
	cin >> studentid;
	string arr[3];
	arr[0] = studentname;
	arr[1] = studentid;
	arr[2] = functionname;
	studentsQueue.dynenqueue(arr); // Add the array to queue
	cout << studentname << "'s service request of " << functionname << " has been put in the student's queue." << endl;
	cout << "Waiting to be served..."<<endl;
}

void mainmenu(){
	while (true){ 
		cout << endl; 
		cout<<"**********************************************************************"<<endl 
			<<"**************** 0 - EXIT PROGRAM                        *************"<<endl 
			<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl 
			<<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl 
			<<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl 
			<<"**********************************************************************"
			<<endl<< endl; 
		int option; 
		cout << "Pick an option from above (int number from 0 to 3): "; 
		cin >> option; 
		switch (option) { 
		case 0: 
			cout << "PROGRAM EXITING ... " << endl; 
			studentsQueue.dynclear();
			instructorsQueue.clear();
			deletefunctions(functionshead);
			system("pause"); 
			exit(0); 
		case 1: 
			addInstructorRequest(); 
			break; 
		case 2: 
			addStudentRequest(); 
			break; 
		case 3: 
			processARequest(); 
			break; 
		default: 
			cout<<"INVALID OPTION!!! Try again"<<endl; 
		}//switch 
	}//while (true)
}

void ProcessFile(ifstream &file){
	function *temp = new function("",NULL);
	string lines;
	string command,command2;
	(getline(file,lines));
	istringstream line(lines);
	line >> command;
	command = command.substr(0 , command.find(":"));;
	string functionname = command; // Function name is first word minus :
	while (getline(file,lines)){ // Add each line to function
		istringstream line(lines);
		line >> command;
		line >> command2;
		command2 = command2.substr(0 , command2.find(";"));
		command = command+" "+command2;
		Add2EndFunction(temp,command);
	}
	Add2EndFunctions(functionshead,functionname,temp); // add function to functions
}

ifstream GetFile(string &filename){//Reading file
	ifstream file;
	file.open(filename.c_str());
	if (file.fail()){ // If coulld not open the file
		cout << "Cannot open file exiting program..."<<endl;
		deletefunctions(functionshead);
		file.close();
		exit(0);
	}
	return file;
}

int main(){
	string input,filename;
	ifstream file;
	cout << "If you want to open a service (function) defining file, then press(Y/y) for 'yes' , otherwise press any single key"<<endl;
	cin >> input;
	if (input != "y" && input != "Y"){
		return 0;
	}
	while(input == "y" || input == "Y"){
		cout << "Enter the input file name: " << endl;
		cin >> filename;
		ifstream file = GetFile(filename);
		ProcessFile(file);
		cout << "Do you want to open another service defining file?" << endl;
		cout << "Press(Y/y) for 'yes' , otherwise press any single key" << endl;
		cin >> input;
		file.close();
	}
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
	cout << "-------------------------------------------------------------------" << endl<<endl;
	printfunctions(functionshead);
	mainmenu();
	return 0;
}