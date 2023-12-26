#include <iostream>
#include <cstdlib>

using namespace std;

#include "1.h"

int option(int percents[]){
    register int i=0,choice=rand()%100+1,perc;
    for(perc=percents[0];perc<choice;perc+=percents[i+1],i++);
    return i;
}
int main()
{
    int arrivals[]={15,20,25,10,30};
    int service[]={0,0,0,10,5,10,10,0,15,25,10,15};
    int clerks[]={0,0,0,0}, numOfClerks=sizeof(clerks)/sizeof(int);
    
    int customers,t,i,numOfMinutes=100,x;
    double maxWait=0.0,currWait=0.0,thereIsLine=0.0;
    
    Queue<int> simulQ;
    cout.precision(2);
    for(t=1;t<numOfMinutes;t++){
        if(clerks[i]<60)
            clerks[i]=0;
        else clerks[i]-=60;
    customers=option(arrivals);
    for(i=0;i<customers;i++)
        x=option(service)*10;
        simulQ.enqueue(x);
        currWait+=x;
    }
    
    for(i=0;i<numOfClerks && !simulQ.isEmpty();)
    if(clerks[i]<60){
        x=simulQ.dequeue(); //assign >1 cutomer if serviceTime>60sec
        clerks[i]+=x;
        currWait-=x;
    }
    else i++;
    
    if(!simulQ.isEmpty()){
        thereIsLine++;
        cout<<"Wait= "<<currWait/60.0;
        
        if(maxWait<currWait){
            maxWait=currWait;
        }
        else
            cout<<"Wait=0";;
    }
    
    cout<<"\n For"<<numOfClerks<<"clerks, there was a line"<<thereIsLine/numOfMinutes*100.0<<"% of the time; \n"<<"max wait time was"<<maxWait/60.0<<"min.";
    cout<<"Hello World";

    return 0;
}
