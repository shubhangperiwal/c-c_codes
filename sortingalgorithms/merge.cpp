#include<iostream>
using namespace std;
void merge(int a[],int l,int r,int m)
{
	int arr[100];
	int i = 0,j=l,k=m;
	while(i<=r && k<=r && j<m)
	{
		if(a[j]>a[k] && k<=r){
		cout<<a[k];
		arr[i] = a[k];
		k++;
		i++;
	}
		else if(j<m && a[k]>a[j])
		{arr[i] = a[j];
		cout<<a[j];
		j++;
		i++;
		
	}	
		
	}
	while(j<m)
	{
		arr[i] = a[j];
		j++;
		i++;
	}
	while(k<=r)
	{
		arr[i] = a[k];
		k++;
		i++;
	}
	for(i=l;i<=r;i++)
	{
		a[i] = arr[i-l];
		cout<<a[i];
	}
	cout<<endl;
}
void mergesort(int a[],int l,int r)
{
	if(l<r)
	{
		int m = (l+r)/2;
		mergesort(a,l,m);
		mergesort(a,m+1,r);
		merge(a,l,r,m+1);
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
	
	mergesort(a,0,n-1);
	cout<<endl;
	for(i=0;i<n;i++)
	cout<<a[i]<<" ";
}
