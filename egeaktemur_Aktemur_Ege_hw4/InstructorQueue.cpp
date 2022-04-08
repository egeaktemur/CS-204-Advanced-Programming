#include <iostream>
#include "InstructorQueue.h"
#include <string>
using namespace std;
//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
InstructorQueue::InstructorQueue(){
	queueSize = 5;
	front = -1;
	rear = -1;
	numItems = 0;
	#ifdef DEBUGING
		cout << "A queue with 5 elements created\n";
	#endif
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void InstructorQueue::enqueue(string num[3]){
	if (isFull()){ 
         cout << "The queue is full. " << num << " not enqueued\n";
    }
	else{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear][0] = num[0];
		queueArray[rear][1] = num[1];
		queueArray[rear][2] = num[2];

		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it stringo num. *
//**********************************************
void InstructorQueue::dequeue(string (&num)[3]){
	if (isEmpty()){
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		num[0] = queueArray[front][0];
		num[1] = queueArray[front][1];
		num[2] = queueArray[front][2];

		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool InstructorQueue::isEmpty() const{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool InstructorQueue::isFull() const{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void InstructorQueue::clear(){
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}
