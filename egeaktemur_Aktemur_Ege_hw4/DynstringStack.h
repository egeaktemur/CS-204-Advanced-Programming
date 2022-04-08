struct StackNode
{
	std::string value;
	StackNode *next;
};

class DynstringStack
{
private:
	StackNode *top;

public:
	DynstringStack(void);
	void push(std::string);
	void pop(std::string &);
	bool isEmpty(void);
};
