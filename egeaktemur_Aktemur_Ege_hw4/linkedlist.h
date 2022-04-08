#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <iostream>
#include <string>
using namespace std;
struct function {
	string step;
	function *next; 

	function::function ()
	{}

	function::function (const string & s, function * link)
		: step(s), next (link)
	{}
};


struct functions {
	string funcname;
	functions *next; 
	function *func; 

	functions::functions ()
	{}

	functions::functions (const string & s, functions * link, function * func)
		: funcname(s), next (link),func (func)
	{}
};

bool DoesfunctionExist (functions * head, string functionname);
function *Function     (functions * head, string functionname);
void Add2EndFunctions  (functions * head, string functionname,function * func);
void Add2EndFunction   (function * head, string step);
void printfunction     (function * head);
void printfunctions    (functions * head);
void deletefunction    (function * head);
void deletefunctions   (functions * head);
#endif