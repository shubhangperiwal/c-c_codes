#include<stdio.h>
#include<iostream>
using namespace std;
void max1(int *a,int *b,int *c)
{
	if(((*b) > (*c))&& (*b)>(*a))
		{
			int temp = *b;
			*b = *a;
			*a = temp;
		}
	else if(((*c) > (*b))&& (*c)>(*a))
		{
			int temp = *c;
			*c = *a;
			*a = temp;
		}
		
}

void max2(int *a,int *b)
{
	int temp = (*a);
	(*a) = (*b);
	(*b) = temp;
}
void del(int a[],int n)
{
	int i=(n/2);
	int min = a[i];
	int j=i;
	for(;i<n;i++)
	{
		if(min>a[i])
		{
			min = a[i];
			j=i;
		}
	}
	cout<<endl<<"deleted element is "<<a[j];
	for(i=j;i<n;i++)
	{
		a[i]=a[i+1];
	}
}

void heapify(int a[],int n,int s)
{
	int i=0,j=0;
	int k=0;
	int w=1;
	
	while(w<=n)
	{
		k++;
		w=w*2;
	}
	w=n/2;
	k++;
	for(i=0;i<=(k+2);i++)
	{
		for(j=s;j<=(w+1);j++)
		{
			if(((2*j) +2) < n)
			max1(&a[j],&a[2*j +1],&a[2*j +2]);
			
			else if(((2*j)+1) < n)
			max2(&a[j],&a[(2*j) +1]);
		}
	}
}
void heapsort(int a[],int n)
{
	
	int temp;
	for(int i=n;i>0;i--)
	{
		
	temp=a[0];
	a[0] = a[i-1];
	a[i-1] = temp;
	n--;
	heapify(a,n,0);
	}
	if(a[0]>a[1])
	{
	temp = a[0];
	a[0] = a[1];
	a[1] = temp;
}
}
int main()
{
	int n;
	cout<<"Enter the number of elements";
	cin>>n;
	int a[n];
	
	int i=0;
	for(i=0;i<n;i++)
		cin>>a[i];
		
		heapify(a,n,0);
		cout<<endl;
		for(i=0;i<n;i++)
			cout<<a[i]<<" ";
			
		del(a,n);	
		n--;
		heapify(a,n,0);
		cout<<endl;
		for(i=0;i<n;i++)
			cout<<a[i]<<" ";	
	
		heapsort(a,n);
			cout<<endl;
		for(i=0;i<n;i++)
			cout<<a[i]<<" ";	
			
}


