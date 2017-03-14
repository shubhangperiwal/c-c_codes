#include<iostream>
using namespace std;
typedef struct sc{
	int priority;
	int bt;
	int at;
	int done;
	int tl;
	char name;
}SC;
void sjf()
int main()
{
	cout<<"Enter number of queues";
	int noq;
	cin>>noq;
	cout<<"Enter round robin time ";
	int rrt;
	cin>>rrt;
	SC a[100],b[100];
	int temp=2,i=0;
	cout<<"Enter elements in queue 1";
	while(temp!=0)
	{
	
	cout<<"Enter priority ";
	cin>>a[i].priority;
	
	cout<<"Enter burst time ";
	cin>>a[i].bt;
	
	cout<<"Enter arrival time ";
	cin>>a[i].at;
	cout<<"Enter job name ";
	cin>>a[i].name;
	a[i].done = 0;
	i++;
	
	cout<<"ENter 0 to exit entering. to continue enter 1";
	}
	int n1 = i;
	temp = 2;
	i=0;
	cout<<"Enter elements in queue 2";
	while(temp!=0)
	{
	
	cout<<"Enter priority ";
	cin>>b[i].priority;
	
	cout<<"Enter burst time ";
	cin>>b[i].bt;
	
	cout<<"Enter arrival time ";
	cin>>b[i].at;
	b[i].done = 0;
	b[i].tl = b[i].bt;
	i++;
	
	cout<<"ENter 0 to exit entering. to continue enter 1";
	}
	n2 = i;
	i=0;
	
	
	
	
}
