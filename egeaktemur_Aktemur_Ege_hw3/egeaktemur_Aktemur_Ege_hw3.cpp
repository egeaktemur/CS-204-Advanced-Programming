#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;
	busStop::busStop (){}
	busStop::busStop (string busStopName,busStop *left,busStop *right): 
		busStopName(busStopName),
		left(left),
		right(right){}
};

struct busStopprev {
	string busStopName;
	string prev;
	busStopprev *left;
	busStopprev *right;
	busStopprev::busStopprev (){}
	busStopprev::busStopprev (string busStopName,busStopprev *left,busStopprev *right,string prev=""): 
		busStopName(busStopName),
		left(left),
		right(right),
		prev(prev)
	{}
};

struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;
	busLine::busLine (){}
	busLine::busLine (string busLineName,busLine *next,busStop *busStops): 
		busLineName(busLineName),
		next(next),
		busStops(busStops){}
};

busLine* head = nullptr;

void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
		 <<"I 0 - EXIT PROGRAM                              I"<<endl
		 <<"I 1 - PRINT LINES                               I"<<endl
		 <<"I 2 - ADD BUS LINE                              I"<<endl
		 <<"I 3 - ADD BUS STOP                              I"<<endl
	   	 <<"I 4 - DELETE BUS LINE                           I"<<endl
		 <<"I 5 - DELETE BUS STOP                           I"<<endl
		 <<"I 6 - PATH FINDER                               I"<<endl
		 <<"I 7 - CHALLENGE                                 I"<<endl
		 <<"I***********************************************I"<<endl
		 <<">>";
	cout << endl;
}

void printBusStops(busStop* currBS){
	if(currBS == NULL){
		cout << "Empty" <<endl;
		return;
	}
	while(currBS != NULL) {
		cout << currBS->busStopName;
		if (currBS->right != NULL){
			cout << " <-> ";
		}
		currBS = currBS->right;
	}
	cout << endl;
}

void printBusLines(){
	busLine* currBL=head;//a global variable
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		cout << currBL->busLineName<<": ";
		printBusStops(currBS);
		currBL = currBL->next;
	}
}

//Print Busline with given name
void printBusLine(string buslinename){
	busLine* currBL=head;//a global variable
	while(currBL != NULL) {
		if(currBL->busLineName == buslinename){
			busStop* currBS = currBL->busStops;
			cout << currBL->busLineName<<": ";
			printBusStops(currBS);
		}
		currBL = currBL->next;
	}
}

void AddAfter(string ToBeAdded,string BusStopBefore,string BusLine){
	busLine* currBL = head; //a global variable
	busStop* temp = NULL;
	while(currBL != NULL) {
		if (currBL->busLineName == BusLine) {
			// Find the busline
			busStop* currBS = currBL->busStops;
			while(currBS != NULL) {
				if (currBS->busStopName == BusStopBefore){
					// Find the busstop and add there
					if (currBS->right != NULL){
						temp = new busStop(ToBeAdded,currBS,currBS->right);
						currBS->right->left=temp;
						currBS->right=temp;
						return;
					}
					else{
						temp = new busStop(ToBeAdded,currBS,NULL);
						currBS->right=temp;
						return;
					}

				}
				currBS = currBS->right;
			}
		}
		currBL = currBL->next;
	}
}

//If user wants to add a busstop to begining
void AddBStoBegining(string ToBeAdded,string BusLine){
	busLine* currBL = head; //a global variable
	busStop* temp = NULL;
	while(currBL != NULL) {
		if (currBL->busLineName == BusLine) {
			// Find Busline
			//If there is no element set as frst element
			if (currBL->busStops == NULL){
				temp = new busStop(ToBeAdded,NULL,NULL);
				currBL->busStops = temp;
				return;
			}
			// Else add to begining
			temp = new busStop(ToBeAdded,currBL->busStops->left,currBL->busStops);
			currBL->busStops->left=temp;
			currBL->busStops=temp;
			return;
		}
		currBL=currBL->next;
	}
}

void AddBSToEnd(busStop **BusStops,string ToBeAdded){
	busStop* temp=NULL;
	if (*BusStops == NULL){
		temp = new busStop(ToBeAdded,NULL,*BusStops);
		*BusStops = temp;
		return;
	}
	busStop* currBS = *BusStops;
	// Go to end
	while(currBS->right != NULL) {
		currBS = currBS->right;
	}
	//Add to there
	temp = new busStop(ToBeAdded,currBS,NULL);
	currBS->right=temp;
}

// adds Busstop to end of the given busline
void AddToEnd(string ToBeAdded,string BusLine){
	busLine* currBL = head; //a global variable
	busStop*temp=NULL;
	while(currBL->next != NULL) {
		if (currBL->busLineName == BusLine) {
			// Find the busline and get the busstops
			busStop* currBS = currBL->busStops;
			AddBSToEnd(&currBL->busStops,BusLine);
		}
		currBL = currBL->next;
	}
}

bool IsThereBusLine(string BusLineName){
	if (head == NULL){
		return false;
	}
	busLine* currBL = head; //a global variable
	while(currBL != NULL) {
		if (currBL->busLineName == BusLineName) {
			return true;
		}
		currBL = currBL->next;
	}
	return false;
}

// checks Entire buslines for given busstops
bool DoesBusStopExists(string BusStopName){
	busLine* currBL = head; //a global variable
	if (head == NULL){
		return false;
	}
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == BusStopName) {
				return true;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return false;
}

// Checks if given busstops contains the busstop
bool IsThereBusStop(busStop *BusStops, string BusStopName){
	busStop* currBS = BusStops;
	if (BusStops == NULL){
		return false;
	}
	while(currBS != NULL) {
		if (currBS->busStopName == BusStopName) {
			return true;
		}
		currBS = currBS->right;
	}
	return false;
}

void DeleteBusStop (busStop *busStop) {
	if (busStop != NULL) {
		DeleteBusStop(busStop->right);
		delete busStop;
	}
}

void DeleteBusLine (busLine * head) {
	if (head != NULL) {
		DeleteBusStop(head->busStops);
		DeleteBusLine(head->next);
		delete head;
	}
}

void addBusLine (){
	string BusLineName;
	cout << "Enter the name of the new bus line (0 for exit to main menu)."<<endl;
	cin >> BusLineName;
	while(IsThereBusLine(BusLineName)){
		cout <<"Bus line already exists: enter a new one (0 for exit)"<<endl;
		cin >> BusLineName;
	}
	if(BusLineName == "0"){
		return;
	}
	string BusStopName;
	cout << "Enter the name of the next bus stop (enter 0 to complete)"<<endl;
	cin >> BusStopName;
	if(BusStopName == "0"){
		cout <<"You are not allowed to add an empty bus line"<<endl;
		return;
	}
	busStop* BusStops = NULL;
	while(BusStopName != "0"){
		// Add entered BusStop to the end of the BusStops
		AddBSToEnd(&BusStops,BusStopName);
		cout << "Enter the name of the next bus stop (enter 0 to complete)"<<endl;
		cin >> BusStopName;
		while(IsThereBusStop(BusStops,BusStopName)){
			cout << "Bus stop already exists in the line"<<endl<<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
			cin >> BusStopName;
		}
	}
	char add;
	cout << "The bus line information is shown below"<<endl<<BusLineName<<": ";
	printBusStops(BusStops);
	cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?"<<endl;
	cin >> add;
	if ( add =='n' || add == 'N'){
		// delete the busstops from heap
		DeleteBusStop(BusStops);
		return;
	}
	else if ( add =='y' || add == 'Y'){
		// I  there is no element make first element
		if (head == NULL){
			busLine *temp = NULL;
			temp = new busLine(BusLineName,NULL,BusStops);
			head = temp;
			return;
		}
		// Else go to the last element and add to there
		busLine *ptr = head;
		busLine *temp = NULL;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		temp = new busLine(BusLineName,NULL,BusStops);
		ptr->next = temp;
		return;
	}
}

void addBusStop(){
	string BusLineName;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)"<<endl;
	cin >> BusLineName;
	if(BusLineName == "0"){
		return;
	}
	if(!IsThereBusLine(BusLineName)){
		cout << "Bus line cannot be found. Going back to previous (main) menu."<<endl;
		return;
	}
	cout << "The bus line information is shown below"<<endl;
	printBusLine(BusLineName);
	busLine* currBL = head; //a global variable
	busStop* BusStops;
	while(currBL != NULL) {
		if (currBL->busLineName == BusLineName) {
			BusStops = currBL->busStops;
		}
		currBL = currBL->next;
	}
	cout <<"Enter the name of the new bus stop"<<endl;
	string BusStop;
	cin >> BusStop;
	if(IsThereBusStop(BusStops,BusStop)){
		cout << "Bus stop already exists. Going back to previous menu."<<endl;
		return;
	}
	cout <<"Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)"<<endl;
	string PreviousBusStop;
	cin >> PreviousBusStop;
	if(!IsThereBusStop(BusStops,PreviousBusStop) && PreviousBusStop != "0"){
		cout <<"Bus stop does not exist. Typo? Enter again (0 for main menu)"<<endl;
		cin >> PreviousBusStop;
		if(PreviousBusStop == "0"){
			return;
		}
	}
	// Add to place accordingly
	if(PreviousBusStop == "0"){
		AddBStoBegining(BusStop,BusLineName);
	}
	else{
		AddAfter(BusStop,PreviousBusStop,BusLineName);
	}
	printBusLines();
}

void deleteBusLine(){
	cout << "Enter the name of the bus line to delete" << endl;
	string BusLineName;
	cin >> BusLineName;
	if (!IsThereBusLine(BusLineName)){
		cout << "Bus line cannot be found. Going back to the previous (main) menu."<<endl;
		return;
	}
	busLine* currBL = head; //a global variable
	if(head->busLineName == BusLineName) {// If user wants to delete the first busline
		DeleteBusStop(head->busStops);
		busLine* ToBeDeleted = head;
		head = head->next;
		delete ToBeDeleted;
		cout << endl;
		printBusLines();
		return;
	}
	while(currBL->next != NULL) {
		if (currBL->next->busLineName == BusLineName) {
			//go to the busline and delete it
			DeleteBusStop(currBL->next->busStops);
			busLine* ToBeDeleted = currBL->next;
			currBL->next = currBL->next->next;
			delete ToBeDeleted;
			cout << endl;
			printBusLines();
			return;
		}
		currBL = currBL->next;
	}
}

void deleteBusStop(){
	cout << "Enter the name of the bus line to delete" << endl;
	string BusLineName;
	cin >> BusLineName;
	if (BusLineName == "0"){
		cout << "Going back to previous (main) menu."<<endl;
		return;
	}
	if (!IsThereBusLine(BusLineName)){
		cout << "Bus line cannot be found. Going back to previous (main) menu."<<endl;
		return;
	}
	busLine* currBL = head;
	busStop* BusStops;
	while(currBL != NULL) { // Find the Busline
		if (currBL->busLineName == BusLineName) {
			BusStops = currBL->busStops;
		}
		currBL = currBL->next;
	}
	cout <<"The bus line information is shown below"<<endl;
	printBusLine(BusLineName);
	cout <<"Enter the name of the bus stop to delete (0 for main menu)"<<endl;
	string BusStopName;
	cin >> BusStopName;
	while(!IsThereBusStop(BusStops,BusStopName) && (BusStopName != "0")){
		cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)"<<endl;
		cin >> BusStopName;
	}
	if(BusStopName == "0"){
		cout << "Going back to previous (main) menu."<<endl;
		return;
	}
	currBL = head;
	busLine*Prev=currBL;
	while(currBL != NULL) {
		if (currBL->busLineName == BusLineName) {
			busStop* currBS = BusStops;
			// Find the busline
			while(currBS != NULL) {
				if (currBS->busStopName == BusStopName) {
					if (currBS->right == NULL && currBS->left == NULL){ // If it is the only busstop
						currBL->busStops = NULL;
						if(Prev->busLineName != currBL->busLineName){
							Prev->next=currBL->next;
						}
						else{
							head=head->next;
						}
						delete currBL;
					}
					else if (currBS->right == NULL){ // If it is the last
						currBS->left->right=NULL;
					}
					else if (currBS->left == NULL){ // If it is the first
						currBS->right->left=NULL;
						BusStops=currBS->right;
						currBL->busStops=BusStops;
						currBS->right=NULL;
					}
					else{ // If it is in the middle
						currBS->left->right=currBS->right;
						currBS->right->left=currBS->left;
					}
					delete currBS;
					cout << endl;
					printBusLines();
					return;
				}
				currBS = currBS->right;
			}
		}
		Prev=currBL;
		currBL = currBL->next;
	}
}

void CreatePath(busStop* currBS,string buslinename,string BusStopName2,bool first){
	if(first){ // I use first bool to print interchang eeasily
		cout << "You can go there by "<<buslinename<<":";
	}
	else{
		cout << "                    "<<buslinename<<":";
	}
	busStop* currBS2 = currBS;
	bool foundright=false,foundleft=false;
	while(currBS2 != NULL) { // Check if it is on the riight
		if(currBS2->busStopName==BusStopName2){
			foundright=true;
		}
		currBS2 = currBS2->right;
	}
	if (foundright){ // If it is on the right
		currBS2 = currBS;
		while(currBS2 != NULL) {
			if(currBS2->busStopName==BusStopName2){
				// Find the second ones place and cout until arriving
				busStop* currBS3 = currBS;
				while(currBS2->right != currBS3) {
					if(currBS3->busStopName != BusStopName2){
						cout << currBS3->busStopName<< "->";
					}
					if(currBS3->busStopName == BusStopName2){
						cout<< currBS3->busStopName<<endl;
						return;
					}
					currBS3 = currBS3->right;
				}
			}
			currBS2 = currBS2->right;
		}
	}
	currBS2 = currBS;
	while(currBS2 != NULL) {
		if(currBS2->busStopName==BusStopName2){
			foundleft=true;
		}
		currBS2 = currBS2->left;
	}
	if (foundleft){// Find the second ones place and cout until arriving
		currBS2 = currBS;
		while(currBS2 != NULL) {
			if(currBS2->busStopName==BusStopName2){
				busStop* currBS3 = currBS;
				while((currBS2->left==NULL && currBS3!=NULL) || (currBS2->left != currBS3)) {
					if(currBS3->busStopName != BusStopName2){
						cout << currBS3->busStopName<< "->";
					}
					if(currBS3->busStopName == BusStopName2){
						cout<< currBS3->busStopName<<endl;
						return;
					}
					currBS3 = currBS3->left;
				}
			}
			currBS2 = currBS2->left;
		}
	}
}

// Functions for challenge
void PrintBusStops(busStopprev* currBS){
	if(currBS == NULL){
		cout << "Empty" <<endl;
		return;
	}
	while(currBS != NULL) {
		cout << currBS->busStopName <<" prev: "<< currBS->prev<<endl;
		if (currBS->right != NULL){
			cout << " | "<<endl<<" V"<<endl;
		}
		currBS = currBS->right;
	}
	cout << endl;
}

//Checks if given busstopprev contains the busstop
bool IsThereBusStopPrev(busStopprev *BusStops, string BusStopName){
	busStopprev* currBS = BusStops;
	if (BusStops == NULL){
		return false;
	}
	while(currBS != NULL) {
		if (currBS->busStopName == BusStopName) {
			return true;
		}
		currBS = currBS->right;
	}
	return false;
}

// returns the size of head
int buslinesize(){
	busLine * ptr = head;
	int count = 0;
	while(ptr){
		count=count+1;
		ptr=ptr->next;
	}
	return count;
}

// checks if you can go from busstop1 to busstop2 without interchange
bool IsThereAPath (string busstop1, string busstop2){
	busLine * currBL = head;
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == busstop1) {
				if(IsThereBusStop(currBL->busStops,busstop2)){
					return true;
				}
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return false;
}

// to make things simpler
void CreatePathChallenge(string busstop1, string busstop2, bool first){
	busLine* currBL = head; 
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == busstop1) {
				if(IsThereBusStop(currBL->busStops,busstop2)){
					CreatePath(currBS,currBL->busLineName,busstop2,first);
				}
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
}

//Adds to end of the busstopprev
void AddBSPToEnd(busStopprev **BusStops,string ToBeAdded,string prev=""){
	busStopprev* temp=NULL;
	if (*BusStops == NULL){
		temp = new busStopprev(ToBeAdded,NULL,*BusStops,prev);
		*BusStops = temp;
		return;
	}
	busStopprev* currBS = *BusStops;
	while(currBS->right != NULL) {// Go to end
		currBS = currBS->right;
	}
	temp = new busStopprev(ToBeAdded,currBS,NULL,prev);//Add to there
	currBS->right=temp;
}

//Calculate where user can go from given point
busStop * CanGo (string BusStopName , busStop * usertried){
	busStop * CanAccess = NULL;
	busLine* currBL = head; 
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == BusStopName) {
				busStop* BusStopThatContains = currBL->busStops;
				while(BusStopThatContains != NULL) {
					if (BusStopThatContains->busStopName != BusStopName 
						&& !IsThereBusStop(usertried,BusStopThatContains->busStopName)) {
						AddBSToEnd(&CanAccess,BusStopThatContains->busStopName);
					}
					BusStopThatContains = BusStopThatContains->right;
				}
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return CanAccess;
}

// This one adds to the some busstops too
void CanGo (busStopprev * & MayWent,busStop * & CanAccess,string BusStopName){
	busLine* currBL = head; 
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == BusStopName) {
				busStop* BusStopThatContains = currBL->busStops;
				while(BusStopThatContains != NULL) {
					if (BusStopThatContains->busStopName != BusStopName 
						&& !IsThereBusStop(CanAccess,BusStopThatContains->busStopName)
						&& !IsThereBusStopPrev(MayWent,BusStopThatContains->busStopName)) {
							AddBSToEnd(&CanAccess,BusStopThatContains->busStopName);
							AddBSPToEnd(&MayWent,BusStopThatContains->busStopName,BusStopName);
					}
					BusStopThatContains = BusStopThatContains->right;
				}
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
}

void DeleteBusStopPrev (busStopprev *busStop) {
	if (busStop != NULL) {
		DeleteBusStopPrev(busStop->right);
		delete busStop;
	}
}

// I first begin with the node we are in if we can go to the destination without interchange print it
// Else detect where user can go from the point and add these to userwent
// If user can go to the destination from these points end loop
// Else new usercango is these nodes

/*example
user is in Sabanci
Wants to go to Cam_Evleri
"Not ordered"
We can go from sabanci to Nakliyeciler,Viaport,Pendik,Kartal
User can go to Cam_Evleri from Nakliyeciler
Userwent is now:
Sabanci Prev:
Nakliyeciler Prev:Sabanci
Pendik Prev:Sabanci
Kartal Prev:Sabanci
Viaport Prev:Sabanci
Cam_Evleri Prev: Nakliyeciler

start going back from Cam_Evleri
If it is not Nakliyeciler delete it
when found Nakliyeciler we are searching for sabanci

now userwent is:
Sabanci Prev:
Nakliyeciler Prev:Sabanci
Cam_Evleri Prev: Nakliyeciler

Create route from sabanci to nakliyeciler
Create route from nakliyeciler to Cam_Evleri
*/
void challenge(){
	busLine* currBL = head; //a global variable
	cout <<"Where are you now?"<<endl;
	string BusStopName1;
	cin >> BusStopName1;
	if(!DoesBusStopExists(BusStopName1)){
		cout <<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		return;
	}
	cout <<"Where do you want to go?"<<endl;
	string BusStopName2;
	cin >> BusStopName2;
	if(!DoesBusStopExists(BusStopName2)){
		cout <<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		return;
	}
	cout <<endl;
	//If user cna go without interchange print it
	if (IsThereAPath(BusStopName1,BusStopName2)){
		CreatePathChallenge(BusStopName1,BusStopName2,true);
		return;
	}
	int interchange=1;
	busStopprev *userwent = NULL;
	AddBSPToEnd(&userwent,BusStopName1,"");
	busStop *usercango = NULL;
	AddBSToEnd(&usercango,BusStopName1);
	busStop *usercango2 = NULL;
	bool found=false;
	// Interchange numbers should not be greater than buslinesize
	while(interchange<buslinesize() && usercango!=NULL && found==false){
		busStop * currBS = usercango;
		//User to includes where user can go from the last usercango
		while(currBS != NULL){
			CanGo(userwent,usercango2,currBS->busStopName);
			currBS=currBS->right;
		}
		busStop * currBS2 = usercango2;
		while(currBS2 != NULL && found==false){
			//If user can go to destination from the one of the usercango2 elements add this node to userwent
			if(IsThereAPath(currBS2->busStopName,BusStopName2)){
				if (!IsThereBusStopPrev(userwent,currBS2->busStopName)) {
					AddBSPToEnd(&userwent,currBS2->busStopName);
				}
				// then add destination to userwent
				AddBSPToEnd(&userwent,BusStopName2,currBS2->busStopName);
				found = true;
			}
			currBS2=currBS2->right;
		}
		DeleteBusStop(usercango);
		usercango=usercango2;
		interchange = interchange+1;
	}
	// If no solution found
	if(!found){
		cout<< "Could not find any route. Going back to main menu..."<<endl;
		DeleteBusStopPrev(userwent);
		return;
	}
	busStopprev * currBS = userwent;
	// Go to the last elment of the userwent
	//If you want to see the logic:
	//PrintBusStops(userwent);
	while(currBS->right != NULL){
		currBS=currBS->right;
	}
	// go left from the last
	while(currBS->prev != ""){ // is the first lements prev
		// If left of the node is not the prev of the node user stays delete it
		while (currBS->left->busStopName != currBS->prev){
			busStopprev * currBS2 = currBS->left;
			currBS2->left->right=currBS;
			currBS->left=currBS2->left;
			delete currBS2;
		}
		currBS=currBS->left;
	}
	// this way we can create a clean solution
	//PrintBusStops(userwent); // U can see the solution
	//Print the solution
	currBS = userwent->right;
	CreatePathChallenge(currBS->prev,currBS->busStopName,true);
	currBS=currBS->right;
	while(currBS != NULL){
		CreatePathChallenge(currBS->prev,currBS->busStopName,false);
		currBS=currBS->right;
	}
	DeleteBusStopPrev(userwent);

}

// End of Chalenge

void pathfinder(){
	busLine* currBL = head; //a global variable
	cout <<"Where are you now?"<<endl;
	string BusStopName;
	cin >> BusStopName;
	if(!DoesBusStopExists(BusStopName)){
		cout <<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		return;
	}
	cout <<"Where do you want to go?"<<endl;
	string BusStopName2;
	cin >> BusStopName2;
	if(!DoesBusStopExists(BusStopName2)){
		cout <<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		return;
	}
	cout <<endl;
	busStop* StopsUserCanGo = NULL;
	bool interchangeneeded = true;
	string userused;
	while(currBL != NULL) {
		busStop* currBS = currBL->busStops;
		while(currBS != NULL) {
			if (currBS->busStopName == BusStopName) {
				StopsUserCanGo = currBL->busStops;
				if(IsThereBusStop(currBL->busStops,BusStopName2)){
					// If both stops are in the same buslineno interchang eis needed
					interchangeneeded = false;
					CreatePath(currBS,currBL->busLineName,BusStopName2,true);
				}
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	if(!interchangeneeded){
		return;
	}

	// For bonus
	string interchange;
	busLine* currBL1 = head;
	vector<vector<string>> UsedBusLines;
	while(currBL1 != NULL) {
		busStop* currBS0 = currBL1->busStops;
		while(currBS0 != NULL) {
			// Search for the busstop it can search multiple buslines
			if (currBS0->busStopName == BusStopName) {
				//If there is busstop in the current busline
				StopsUserCanGo = currBL1->busStops;
				userused=currBL1->busLineName;
				busStop* StopsUserCanGoFromDestination = NULL;
				currBL = head;
				// Search where user can go from destination from multiple buslines
				while(currBL != NULL) {
					busStop* currBS = currBL->busStops;
					while(currBS != NULL) {
						if (currBS->busStopName == BusStopName2) {
							StopsUserCanGoFromDestination = currBL->busStops;
							busStop* currBS1 = StopsUserCanGo;
							// Check for same busstop in user can go from begining and end
							while(currBS1 != NULL) {
								if(IsThereBusStop(StopsUserCanGoFromDestination,currBS1->busStopName)){
									interchange = currBS1->busStopName;
									busStop* currBS2 = StopsUserCanGo;
									vector<string> BusLines;
									BusLines.push_back(userused);
									BusLines.push_back(currBL->busLineName);
									bool buslinesused=false;
									for (unsigned int i = 0; i < UsedBusLines.size(); i++){
										// If this interchange allready used
										if(UsedBusLines[i][0]==BusLines[0] && UsedBusLines[i][1]==BusLines[1]){
											buslinesused = true;
										}
									}
									if(!buslinesused){
										// If user did not use ths interchange
										// Create first point to interchange and interchange to destination
										UsedBusLines.push_back(BusLines);
										while(currBS2 != NULL) {
											if (currBS2->busStopName == BusStopName) {
												CreatePath(currBS2,userused,interchange,true);
											}
											currBS2 = currBS2->right;
										}
										currBS2 = StopsUserCanGoFromDestination;
										while(currBS2 != NULL) {
											if (currBS2->busStopName == interchange) {
												CreatePath(currBS2,currBL->busLineName,BusStopName2,false);
											}
											currBS2 = currBS2->right;
										}
										cout <<endl;
									}
								}
								currBS1 = currBS1->right;
							}
						}
						currBS = currBS->right;
					}
					currBL = currBL->next;
				}
			}
			currBS0 = currBS0->right;
		}
		currBL1 = currBL1->next;
	}
}

bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName
					<< " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

void processMainMenu() {
	char input;
	do
	{
		if(!consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
		case '0':
			cout << "Thanks for using our program" << endl;
			return;
		case '1':
			printBusLines();
			break;
		case '2':
			addBusLine();
			break;
		case '3':
			addBusStop();
			break;
		case '4':
			deleteBusLine();
			break;
		case '5':
			deleteBusStop();
			break;
		case '6':
			pathfinder();
			break;
		case '7':
			challenge();
			break;
		default:
			cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu

ifstream GetFile(string &filename){//Reading file
	ifstream file;
	file.open(filename.c_str());
	return file;
}

int main(){
	string filename = "busLines.txt";
	ifstream file = GetFile(filename);
	string lines;
	busLine* temp=NULL;
	busStop* BusStops = NULL;
	while (getline(file,lines)){
		istringstream line(lines);
		string BusLineName,BusStopName;
		line >> BusLineName;
		BusLineName = BusLineName.substr(0 , BusLineName.find(":"));
		BusStops = NULL;
		while(line >> BusStopName){// Add busstops to busstop object
			AddBSToEnd(&BusStops,BusStopName);
		}
		if (head == NULL){// If there is no busline
			busLine *temp = NULL;
			temp = new busLine(BusLineName,NULL,BusStops);
			head = temp;
		}
		else{ // Else go to the last element and add to there
			busLine *ptr = head;
			busLine *temp = NULL;
			while(ptr->next != NULL){
				ptr = ptr->next;
			}
			temp = new busLine(BusLineName,NULL,BusStops);
			ptr->next = temp;
		}
	}
	file.close();
	printBusLines();
	processMainMenu();
	DeleteBusLine(head);
	printBusLines();
	return 0;
}