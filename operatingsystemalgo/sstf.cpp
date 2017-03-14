#include<iostream>
using namespace std;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void sort(int a[],int n,int s)
{
	int i,j;
	for(i=s;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
		if(a[i]>a[j])
		swap(&a[i],&a[j]);
		}
	}
	
}
int calmod(int a,int b)
{
	if(a>b)
	return a-b;
	
	return b-a;
}
int main()
{
	int s;
	int n,i;
	cout<<"ENter start position";
	cin>>s;
	cout<<"Enter number of elements ";
	cin>>n;
	int a[100],b,n1=0,n2=0,temp;
	cout<<"ENter elements5 ";
	for(i=0;i<n;i++)
	{
		
		cin>>a[i];
	
	}
int distance,j; 
	temp = calmod(s,a[0]);
	for(j=0;j<n;j++)
	{
		b = calmod(s,a[j]);
		if(b<temp)
		{
			temp = b;
			n1 = j;
		}		
	}	
	swap(&a[0],&a[n1]);
	cout<<a[0]<<endl;
	for(i=0;i<n-1;i++)
	{
		temp=1000;
		for(j=i+1;j<n;j++)
		{
			b = calmod(a[i],a[j]);
			if(b<temp)
			{
				temp = b;
				n1 = j;
			}
		}
		swap(&a[i+1],&a[n1]);
	}
	
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
	
	
}
