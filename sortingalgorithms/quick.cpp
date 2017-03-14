#include<iostream>
using namespace std;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}
int part(int a[],int s,int e)
{
	int pivot = a[e-1];
	int l=s,r=e-2;
	while(l<=r)
	{
		if(a[l]<pivot)
		l++;
		
		else if(a[r]>pivot)
		r--;	
		
		else 
		swap(&a[l],&a[r]);
				
	}
	swap(&a[l],&a[e-1]);
	
	cout<<a[l]<<" "<<a[r]<<" ";
	return l;
	
}
void quicks(int a[],int s,int e)
{
	if(e-s<=0)
	return;
	
	
	int k = part(a,s,e);
	quicks(a,s,k);
	quicks(a,k+1,e);
}
int main()
{
	int n;
	cout<<"ENter the number of numbers ";
	cin>>n;
	int a[n];
	int i;
	cout<<endl;
	cout<<"Enter numbers "<<endl;
	for(i=0;i<n;i++)
	cin>>a[i];
	quicks(a,0,n);
	cout<<endl;
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
}
