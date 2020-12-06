#include <iostream>
#include "stack.h"
#include "multiStack.h"

using namespace std;

int main()
{
	TStack<int> a(3);
	a.Push(10);

	MultiStack<int> b(9, 3);
	b.Push(11, 0);
	b.Push(12, 1);
	b.Push(13, 1);
	b.Push(14, 1);

	b.Push(15, 1);
	

	cout << b << endl;

	return 0;
}