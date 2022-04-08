#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct courseNode{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;
	courseNode::courseNode (){}
	courseNode::courseNode (string code,string name,vector<int> IDs,courseNode * link): 
		courseCode(code),courseName(name),studentsAttendingIDs(IDs),next(link){}
};

void Print ( vector<int> v){
	for ( unsigned int i = 0; i<v.size(); i++){
		cout << v[i] << " ";
	}
}

void Print ( courseNode * head ){
	if(head == NULL) {
		cout << "List is empty ";
	}
	else {
		courseNode*ptr = head;
		while (ptr!= NULL){
			// Print Code and name
			cout << ptr->courseCode << " " << ptr->courseName << ": ";
			// Print Ids
			Print(ptr->studentsAttendingIDs);
			// Go to next element
			ptr = ptr->next;
			cout << endl;
		}
	}
	cout << endl;
}

//Selection sort
void Sort(vector<int> & v){
	int min,temp;
	for(unsigned int i=0; i < v.size() - 1; i++){
		min = i;            
		for(unsigned int j=i+1; j < v.size(); j++){
			if (v[j] < v[min]){
				min = j;    
			}
		}
		temp = v[i];     
		v[i] = v[min];
		v[min] = temp;
	}
}

//This function adds to end and then sorts.
void AddAndSort ( vector<int> & v, string x){
	bool AllreadyAdded = false;
	for (unsigned int i = 0; i < v.size(); i++){
		if (v[i] == stoi(x)){
			AllreadyAdded = true;
		}
	}
	if ( ! AllreadyAdded){
		v.push_back(stoi(x));
	}
	Sort(v);
}

//Check if the given course exists
bool CourseExists(courseNode * head,string CourseName,string CourseCode){
	courseNode*ptr = head;
	while (ptr!= NULL){
		if (ptr->courseCode == CourseCode && ptr->courseName == CourseName){
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

string GetOption(){
	cout<<"Please select one of the choices:"<<endl<<"1. Add to List"<<endl<<"2. Drop from List"
		<<endl<<"3. Display List"<<endl<<"4. Finish Add/Drop and Exit"<<endl;
	string option;
	cin>>option;
	return option;
}

//Returns if given string is id,CourseName or CourseCode
string type(string word){
	if (word.at(0) >= '0' && word.at(0) <= '9') {return "id";}
	else if (word.at(0) <= '0' || word.at(0) >= '9') {
		if (word.at(word.length()-1) <= '0' || word.at(word.length()-1) >= '9') {
			return "CourseName";
		} else {
			return "CourseCode";
		}
	}
}

ifstream GetFile(string &filename){
	ifstream file;
	file.open(filename.c_str());
	return file;
}

// I wrote Add in order myself to understand linked lists better
// I wroted 2 other functions to make my job easier
courseNode * AddToBegining ( courseNode * head , string code, string name, vector<int> IDs){
	//If there is no element in list make first element the node
	if (head == NULL) {
		courseNode *temp = NULL;
		temp = new courseNode(code,name,IDs,head);
		head = temp;
		return head;
	}
	// Else make first element the node and point it to the previous first element
	courseNode *ptr = head;
	courseNode *temp = NULL;
	ptr = ptr->next;
	temp = new courseNode(code,name,IDs,head);
	head = temp;
	return head;
}

courseNode * AddToEnd ( courseNode * head , string code, string name, vector<int> IDs){
	//If there is no element in list make first element the node
	if (head == NULL){
		return AddToBegining(head,code,name,IDs);
	}
	// Else go to the last element and add to there
	courseNode *ptr = head;
	courseNode *temp = NULL;
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	temp = new courseNode(code,name,IDs,NULL);
	ptr->next = temp;
	return head;
}

courseNode * AddInOrder( courseNode * head , string code, string name, vector<int> IDs){
	courseNode *ptr = head;
	courseNode *temp = NULL;
	// If there is no element or first element is bigger than the node
	if (head == NULL || (head->courseName > name)) {
		return AddToBegining(head,code,name,IDs);
	}
	// If there is no second element decide where to add it and add it respectively
	else if (head->next == NULL) {
		if (head->courseName < name) {
			return AddToEnd(head,code,name,IDs);
		}
		else {
			return AddToBegining(head,code,name,IDs);
		}
	}
	// Else search where to insert node and insert
	else{
		courseNode * previous;
		while (ptr != NULL && ptr->courseName < name ) {
			previous = ptr;
			ptr = ptr->next;
		}
		Sort(IDs);
		previous->next = new courseNode(code,name,IDs,(ptr));
		return head;
	}
}

// Because answer 1 and 2 uses similar way to take input I wrote a function for 2
void ProcessInput(string &CourseCode,string &CourseName,vector<int> &Ids, istringstream &input,string &word,bool &noproblem){
	CourseCode=word;
	input >> CourseName >> word;
	Ids.clear();
	noproblem = true;
	while(type(word) == "id" && noproblem){
		Ids.push_back(stoi(word));
		input >> word;
		if ( type(word)=="id" && Ids[Ids.size()-1] == stoi(word)){
			noproblem = false;
		}
	}
}

// Function to delete linked list at the end to prevent memory leakage
void DeleteList (courseNode *head) {
  if (head != NULL) {
      DeleteList(head->next);
      delete head;
  }
}

courseNode * Option1(courseNode * head){
	string input1;
	cout << "Give the student ID and the course names and course codes that he/she wants to add:"<<endl;
	cin.ignore();
	getline(cin,input1);
	istringstream input;
	input.str(input1);
	string CourseCode,CourseName,id,word;
	vector<int> Ids;
	input >> word;
	bool noproblem = true;
	// noproblem becomes false if there is no input to take
	while(noproblem){
		if(type(word) == "CourseCode"){
			ProcessInput(CourseCode,CourseName,Ids,input,word,noproblem);
			bool Added = false , CourseFound = false;
			courseNode*ptr = head;
			while (ptr!= NULL){
				if ( ptr->courseCode == CourseCode && ptr->courseCode == CourseCode){
					CourseFound=true;
					for (int i = 0; i < Ids.size(); i++){
						Added = false;
						bool CanBeAdded = true;
						// If this id allready added it cannot be added
						for (int j = 0; j < (ptr->studentsAttendingIDs).size(); j++){
							if(Ids[i] == (ptr->studentsAttendingIDs)[j]){
								CanBeAdded = false;
							}
						}
						// If it is not in the id list add it
						if(CanBeAdded){
							AddAndSort(ptr->studentsAttendingIDs,to_string(Ids[i]));
							cout << "Student with id "<<Ids[i]<<" enrolled to "<< CourseCode<<"."<<endl;
						}
						// Else dont add
						else{
							cout << "Student with id "<<Ids[i]<<" already is enrolled to  "<<CourseCode<<". No action taken."<<endl;
						}
					}
				}
				ptr = ptr->next;
			}
			// If course does not exit add course
			if (!CourseFound){
				head = AddInOrder(head,CourseCode,CourseName,Ids);
				cout <<CourseCode<<" does not exist in the list of Courses. It is added up. "<<endl;
				// Then add is to its vector 
				for (int i = 0; i < Ids.size(); i++){
					cout<<"Student with id "<<Ids[i]<<" is enrolled to "<<CourseCode<<"."<<endl;
				}
			}
		}
	}
	return head;
}

courseNode * Option2(courseNode * head){
	string input1;
	cout << "Give the student ID and the course names and course codes that he/she wants to drop:"<<endl;
	cin.ignore();
	getline(cin,input1);
	istringstream input;
	input.str(input1);
	string CourseCode,CourseName,id,word;
	vector<int> Ids;
	input >> word;
	bool noproblem = true;
	// noproblem becomes false if there is no input to take
	while(noproblem){
		if(type(word)=="CourseCode"){
			ProcessInput(CourseCode,CourseName,Ids,input,word,noproblem);
			courseNode*ptr = head;
			bool Erased=false, CourseFound=false;
			while (ptr!= NULL){
				if ( ptr->courseCode == CourseCode && ptr->courseCode == CourseCode){
					CourseFound=true;
					for (int i = 0; i < Ids.size(); i++){
						Erased=false;
						// If it can be erased erase it
						for (int j = 0; j < (ptr->studentsAttendingIDs).size(); j++){
							if(Ids[i] == (ptr->studentsAttendingIDs)[j]){
								(ptr->studentsAttendingIDs).erase((ptr->studentsAttendingIDs).begin()+j);
								cout << "Student with id "<<Ids[i]<<" has dropped "<< CourseCode<<"."<<endl;
								// Because one element erased it should go 1 less step
								j = j-1;
								Erased=true;
							}
						}
						// Else dont erase
						if (!Erased){
							cout << "Student with id "<<Ids[i]<<" is not enrolled to "<<CourseCode<<", thus he can't drop that course."<<endl;
						}
					}
				}
				ptr = ptr->next;
			}
			// If there is no such course
			if ( !CourseFound){
				for (int i = 0; i < Ids.size(); i++){
					cout << "The "<<CourseCode<<" course is not in the list, thus student with id "<<Ids[i]<<" can't be dropped"<<endl;
				}
			}
		}
	}
	return head;
}

void Option3 (courseNode *head){
	cout << "The current list of course and the students attending them: "<<endl; Print(head);
}

void Option4 (courseNode *head){
	cout << "The add/drop period is finished. Printing the final list of courses and students attending them."<<endl
		<<"NOTE: Courses with less than 3 students will be closed this semester."<<endl;
	courseNode*ptr = head;
	while (ptr!= NULL){
		cout << ptr->courseName << " " << ptr->courseCode;
		// If there is less then 3 items
		if(ptr->studentsAttendingIDs.size()>=3){
			cout <<": " ;
			Print(ptr->studentsAttendingIDs);
			cout << endl;
		}
		else{
			cout << " -> This course will be closed"<<endl;
		}
		ptr = ptr->next;
	}

}

int main(){
	string filename;
	cout << "Please enter file name: ";
	cin >> filename;
	ifstream file = GetFile(filename);
	string lines;
	courseNode * head = NULL;
	while ( getline(file,lines) ){
		istringstream line(lines);
		string CourseCode,CourseName,id;
		line >> CourseCode >> CourseName;
		// If course exists just add id to course
		if (CourseExists(head,CourseName,CourseCode)){
			courseNode*ptr = head;
			while (ptr!= NULL){
				if (ptr->courseCode == CourseCode){
					while(line >> id){
						AddAndSort(ptr->studentsAttendingIDs,id);
					}
				}
				ptr = ptr->next;
			}
		}
		// Else add course and add ids
		else {
			vector<int> ids;
			while(line >> id){
				AddAndSort(ids,id);
			}
			head = AddInOrder(head,CourseCode,CourseName,ids);
		}
	}
	cout << "Successfully opened file "<< filename << endl << "The linked list is created. " <<endl << "The initial list is: "<<endl;
	Print(head);
	string option = "0";
	while(option != "4"){
		option = GetOption();
		if (option == "1"){ 
			head = Option1(head); 
		}
		if (option == "2"){ 
			head = Option2(head); 
		}
		if (option == "3"){ 
			Option3(head); 
		}
	}
	Option4(head);
	file.close();
	DeleteList(head);
	return 0;
}
