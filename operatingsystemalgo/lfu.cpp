#include<iostream>
using namespace std;
int pf = 0;
int top=0;
int ispresent(int c[],int a,int l,int t[])
{
	for(int i=0;i<l;i++)
	if(c[i]==a){
		t[i]++;
	return 1;
}
	return 0;
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
	for(i=0;i<f;i++)
	t[i]=0;
	
	int cn=0;
	top=0;
	for(i=f;i<n;i++)
	{
		if(!(ispresent(c,a[i],f,t)))
		{
			int min=t[0];
			int flag=0;
			for(j=0;j<f;j++)
			{
			if(t[j]<min)
				{
				min=t[j];
				flag=j;
				}
			}
			t[flag]=0;
			c[flag]=a[i];
		}
		display(c,f);
	}
}
