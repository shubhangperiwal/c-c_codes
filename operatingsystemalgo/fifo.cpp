#include<iostream>
using namespace std;
int pf = 0;
int top=0;
int ispresent(int c[],int a,int l)
{
	for(int i=0;i<l;i++)
	if(c[i]==a){
		
	return 1;
	}
	return 0;
}

int checkzero(int a[],int l)
{
	for(int i=0;i<l;i++)
	{
		if(a[i]!=-1)
		return i;
	}
	
}
void display(int a[],int l)
{
	for(int i=0;i<l;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void copy(int a[],int b[],int l)
{
	for(int i=0;i<l;i++)
	a[i]=b[i];
}
int main()
{
	cout<<"Enter frame size ";
	int f;
	cin>>f;
	int c[f];
	int d;
	int i=0;
	for(;i<f;i++)
	c[i]=0;
	cout<<"Enter number of pages ";
	int n;
	cin>>n;
	int j,a[n];
	cout<<"Enter pages ";
	for(i=0;i<n;i++)
	cin>>a[i];
	for(i=0;i<f;i++)
	{
		c[i] = a[i];
		display(c,f);
	}
	int t[f];
	
	top=0;
	for(i=f;i<n;i++)
	{
		if(!(ispresent(c,a[i],f)))
		{
			c[top] = a[i];
			top++;
			top = top%f;
		}
		display(c,f);
	}
}
