#include <iostream>
#include <string>
#include "DynStringQueue.h"
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynStringQueue::DynStringQueue()
{
	front = NULL;
	rear = NULL;   
	#ifdef DEBUGING
		cout << "An empty queue has been created\n";
	#endif
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynStringQueue::dynenqueue(string num[])
{       
	if (dynisEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(num);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(num);
		rear = rear->next;
	} 
	#ifdef DEBUGING
		cout << num << " enqueued\n";
	#endif
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it stringo num. *
//**********************************************
void DynStringQueue::dyndequeue(string num[])
{
	QueueNode *temp;
	if (dynisEmpty())
	{
		cout << "ERROR: Attempting to dequeue on empty queue"<<endl;
		return;
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num[0] = front->value[0];
		num[1] = front->value[1];
		num[2] = front->value[2];
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynStringQueue::dynisEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynStringQueue::dynclear()
{
	string value[3];   // Dummy variable for dequeue
	while(!dynisEmpty())
		dyndequeue(value); //delete all elements
}

//********************************************
// Destructor for class                      *
//********************************************
DynStringQueue::~DynStringQueue()
{
	dynclear();
}