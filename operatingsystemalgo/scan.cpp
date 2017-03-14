#include<iostream>
using namespace std;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void rsort(int a[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
		if(a[i]<a[j])
		swap(&a[i],&a[j]);
		}
	}
}
void sort(int a[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
		if(a[i]>a[j])
		swap(&a[i],&a[j]);
		}
	}
	for(i=0;i<n;i++)
	cout<<a[i];
}
int main()
{
	int s;
	int n,i;
	cout<<"ENter start position";
	cin>>s;
	cout<<"Enter number of elements ";
	cin>>n;
	int a[100],b[100],n1=0,n2=0,temp[100];
	cout<<"ENter elements5 ";
	for(i=0;i<n;i++)
	{
		
		cin>>temp[i];
	
	}
	for(i=0;i<n;i++)
	{
		if(temp[i]>s)
		{
		a[n1] = temp[i];
		n1++;
	}
		else
		{
		b[n2] = temp[i];
		n2++;	
		}
	}
	int size;
	cout<<"Enter frame size ";
	cin>>size;
	sort(a,n1);
	rsort(b,n2);
	int distance = a[0]-s;
	for(i=0;i<n1;i++)
	{
		cout<<endl;
		cout<<a[i]<<" "<<distance;
		if(i!=n1-1)
		distance = a[i+1] - a[i];
	}	
	cout<<endl;
	distance = 2*size - a[n1-1] - b[0];
	cout<<b[0]<<" "<<distance<<endl;
	for(i=1;i<n2;i++)
	{
		distance  = b[i-1] - b[i];
		cout<<b[i]<<" "<<distance<<endl;
	}
	
}
