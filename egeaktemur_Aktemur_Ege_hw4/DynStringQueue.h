#ifndef DYNstringQUEUE_H
#define DYNSTRINGQUEUE_H
#include <string>

struct QueueNode
{
	std::string value[3];
	QueueNode *next;
	QueueNode(std::string *num, QueueNode *ptr = NULL){
		value[0] = num[0];
		value[1] = num[1];
		value[2] = num[2];
		next = ptr;
	}
};

class DynStringQueue {
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynStringQueue();
	
	// Member functions.
	void dynenqueue(std::string num[]);
	void dyndequeue(std::string num[]);
	bool dynisEmpty() const;     
	void dynclear();
	~DynStringQueue();
};
#endif