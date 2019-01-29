#ifndef STACK_H
#define STACK_H
#define MAX 400;

template <class T>
class stack {
public:
	stack() { top = -1; } //Defualt Constrcutor
	//~Stack(); //Deconstructor
	bool empty(); //Check if stack is empty
	int size(); //returns size of the stack
	void push(T& element); //pushes new element on top of stack
	void pop();
private:
	int top;
	T elements[MAX];
};

template <class T>
bool stack::empty() {
	if (top == -1)
		return true;
	else
		return false;
}

template <class T>
int stack::size() {
	return elements.size();
}

template <class T>
void stack::push(T& element) {
	if (size() > MAX) {
		cout << "Stack is full" << endl;
	}
	else {
		top++;
		elements[top] = element;
	}
}

template <class T>
void stack::pop() {
	if (empty()) {
		return;
	}
	else {
		T tmp = elements[top];
		top--;
	}
}





#endif