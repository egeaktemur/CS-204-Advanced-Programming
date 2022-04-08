#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

bool DoesfunctionExist(functions *head, string functionname){
	// Check if the given function exists
	functions *ptr = head;
	if (ptr->funcname == ""){
		return false;
	}
	while(ptr!=NULL){
		if (ptr->funcname == functionname){
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

function * Function(functions *head, string functionname){
	// Returns function with the given function name 
	if ( !DoesfunctionExist(head,functionname) ){
		cout << "The requested service (function) does not exists"<<endl;
		return NULL;
	}
	functions *ptr=head;
	while(ptr != NULL){
		if (ptr->funcname == functionname){
			return ptr->func;
		}
		ptr = ptr->next;
	}
	cout << "The requested service (function) does not exists"<<endl;
	return NULL;
}

void Add2EndFunctions(functions *head, string functionname,function *func){
	// Add to end of the functions
	functions *ptr = head;
	if (ptr->funcname == ""){
		ptr->funcname = functionname;
		ptr->func = func;
		return;
	}
	functions *nn = new functions(functionname,NULL,func);
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = nn;
}

void Add2EndFunction(function *head, string step){
	// Add to end of the function
	function *ptr = head;
	if (ptr->step == ""){
		ptr->step = step;
		return;
	}
	function *nn = new function(step,NULL);
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = nn;
}

void printfunction (function * head){
	function * ptr = head;
	while (ptr->next != NULL) {
		cout << ptr->step << ", " ;
		ptr = ptr->next;
	}
	cout << ptr->step << "."<< endl;
}

void printfunctions (functions * head){
	functions * ptr = head;
	while (ptr != NULL) {
		cout << ptr->funcname <<":"<<endl;
		printfunction(ptr->func);
		ptr = ptr->next;
		cout<<endl;
	}
}

void deletefunction (function *head){
	function *ptr = head;
	function *temp;
	while (ptr != NULL) {
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
}

void deletefunctions (functions *head){
	functions *ptr = head;
	functions *temp;
	while (ptr != NULL) {
		temp = ptr->next;
		deletefunction(ptr->func);
		ptr = temp;
	}
}


