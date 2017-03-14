#include<iostream>
using namespace std;
int pf = 0;
int ispresent(int c[],int a,int l,int *t)
{
	for(int i=0;i<l;i++)
	if(c[i]==a){
		*t = i;
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
	int cn=0;
	for(i=f;i<n;i++)
	{
		if(!(ispresent(c,a[i],f,&d)))
		{
			copy(t,c,f);
			for(j=i-1;j>=0;j--)
			{
			if(ispresent(t,a[j],f,&d))
				{
					
				t[d]=-1;	
				cn++;
				}
			if(cn==f-1)
				{
					c[checkzero(t,f)] = a[i];
					break;
				}
			}
			pf++;
		}
		cn=0;
		copy(t,c,f);
		display(c,f);
	}
}
