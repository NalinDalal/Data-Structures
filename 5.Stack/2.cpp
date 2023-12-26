/*
std::stack
-[]Container adapter with functionality of a stack
-[]Need to 'include<stack>' header file
-[]Class template acts as a wrapper to underlying container-specific set of function provided
-[]Pushes and Pops element from one end of underlying container(top of stack)
*/

/*
Stack Functions
-[]size()
-[]=
-[]top()
-[]empty()
-[]push(),pop()
*/

#include <iostream>
#include <stack>

using namespace std;

int main(){
	stack<int> S;

	for(int i=0;i<5;++i)
		S.push(i);
	
	cout<<"Size= "<<S.size()<<endl;
	cout<<"Top= "<<S.top()<<endl;
	
	S.pop();
	S.pop();

	cout<<"Size= "<<S.size()<<endl;
        cout<<"Top= "<<S.top()<<endl;

	if(S.empty())
		cout<<"Stack is empty\n";
	else
		cout<<"Not Empty\n";

	return 0;
}
