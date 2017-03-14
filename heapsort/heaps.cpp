#include<iostream>
using namespace std;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void swapmax(int *a,int *b,int *c)
{
	if(*b > *c && *b > *a)
	swap(a,b);
	else if(*c > *b && *c > *a)
	swap(a,c);
}
void heapify(int a[],int n)
{
	int k = n/2;
	int i=k;
	for(;i>=0;i--)
	{
		if((2*i + 2)< n)
		if(a[i]<a[2*i+1] || a[i]<a[2*i + 2]){
		swapmax(&a[i],&a[2*i+1],&a[2*i+2]);
		i=i*2 + 3;
		}
		else if(2*i + 1 < n)
		if(a[i]<a[2*i+1]){
		swap(&a[i],&a[2*i+1]);
		i=i*2 + 2;
	}
}
}
void hs(int a[],int n)
{
	int i=0,j=0,min=a[n/2];
	for(int k = 0;k<n;k++){
	for(i=n/2;i<n;i++)
	{
		if(min>a[i]){
		min = a[i];
		j=i;
		
		}
	}
	swap(&a[0],&a[j]);
	
	heapify(a,n);
	
}

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
	heapify(a,n);
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
	
	hs(a,n);
	cout<<endl;
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
}
