#include <iostream>

using namespace std;

int myStack[100], n=100, top=-1;
void push(int val){
    if(top>n-1)
        cout<<"Stack Overflow"<<endl;
    else{
        top++;
        myStack[top]=val;
    }    
}

void pop(){
    if(top<=-1)
        cout<<"Stack Underflow"<<endl;
    else{
        cout<<"the popped element is: "<<myStack[top];
        cout<<endl;
        top--;
    }    
}

void display(){
    if(top>=0){
        cout<<"Stack elements are:";
        for(int i=top;i>=0;i--)
            cout<<myStack[i]<<" ";
            cout<<endl;
    }
    else{
        cout<<"Stack is Empty"<<endl;
    }
}

int main()
{
    int ch,val;
    cout<<"1.Push"<<endl;
    cout<<"2.Pop"<<endl;
    cout<<"3.Display"<<endl;
    cout<<"4.Exit"<<endl;
    
    do{
        cout<<"Enter the choice:"<<endl;
        cin>>ch;
        switch(ch){
            case 1:
                {
                    cout<<"Enter value to push:"<<endl;
                    cin>>val;
                    push(val);
                    break;
                }
            case 2:
                {
                    pop();
                    break;
                }
            case 3:
                {
                    display();
                    break;
                }
            case 4:
                {
                    cout<<"Exit"<<endl;
                    break;
                }
            default:
                {
                    cout<<"Invalid Choice"<<endl;
                }
        }
    }
	while(ch!=4);
    return 0;
}
