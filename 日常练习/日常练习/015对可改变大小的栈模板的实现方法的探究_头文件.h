#ifndef 程序清单14_15
#define 程序清单14_15

template <class Type>
class Stack
{
private:
	const static int stacksize;
	Type ar[stacksize];
	int top;
public:
	Stack(int ss = SIZE);
	Stack(const Stack & st);
	
	bool isempty() {return top == 0;}
	bool isfull() {return top == stacksize;}
	bool push(const Type & item);
	bool pop(Type & item);
	Stack & operator=(const Stack & st);
};

template<class Type>
Stack<Type>::Stack(int ss) : stacksize(ss), top(0)
{
}

template<class Type> 
Stack<Type>::Stack(const Stack & st) : stacksize(st.stacksize)
{
	top = st.top;
	for (int i = 0; i < top; i++)
		ar[i] = st.ar[i];
}

template<class Type>
bool Stack<Type>::push(const Type & item)
{
	if (top < stacksize)
	{
		ar[top++] = item;
		return true;
	}
	else
		return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item)
{
	if (top > 0)
	{
		item = ar[--top];
		return true;
	}
	else
		return false;
}

template<class Type>
//Stack<Type> & Stack<Type>::operator=(const Stack<Type> & st)
//{
//	if (this == &st)
//		return *this;
//	delete [] items;
//	stacksize = st.stacksize;
//	top = st.top;
//	items = new Type[stacksize];
//	for (int i = 0; i < top; i++)
//		items[i] = st.items[i];
//	return *this;
//
//}

#endif