#ifndef InstructorQueue_H
#define InstructorQueue_H
#include <string>
class InstructorQueue{
private:
	std::string queueArray[5][3];
	
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	InstructorQueue();  //constructor, parameter is capacity
	void enqueue(std::string[]); 
	void dequeue(std::string (&strings)[3]);
	bool isEmpty() const; 
	bool isFull() const;
	void clear();  //removes all elements
};
#endif
