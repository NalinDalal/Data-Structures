/*
*Approach 1:
    using 2 stacks and deQueue operation only

    enQueue Operation:Push to stack1
    deQueue Operation:
        1.if both stack are empty then rpint error
        2.stack2 is empty
            while(stack1!=empty)
                push(stack1->stack2)
        3.pop[stack2]
            return stack2
* */

#include <stack>
#include <iostream>
using namespace std;

class queue{
    stack<int> s1;
    stack<int> s2;
public:
    void push(int){
        s1.push(x);
    }
    int pop(){
        if(s1.empty() and s2.empty()){
            cout<<"Queue is empty\n";
            return -1;
        }
        if(s2.empty()){
            while(!s1.empty()){
                s.push(s1.top());
                s1.pop();
            }
        }
        int topval=s2.top();
        s2.pop();
        return topval;
    }
    bool empty(){
        if(s1.empty() and s2.empty())
            return true;
        return false;
    }
};

int main(){
    que q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout<<q.pop();
    q.push(5);
    cout<<q.pop()<<"\n";
    cout<<q.pop()<<"\n";
    cout<<q.pop()<<"\n";

    return 0;
}
