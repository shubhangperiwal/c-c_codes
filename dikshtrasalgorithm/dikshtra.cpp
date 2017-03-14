#include<iostream>
using namespace std;
int calmin(int a[],int b[],int n)
{
	int i=0,min=9999,j;
	for(i=0;i<n;i++)
	{
		if(min > b[i] && a[i]==0){
		min = b[i];
		j=i;
		}
	}
	a[j]=1;
	cout<<j<<" ";
	return j;
}
int mini(int a,int b)
{
	if(a>b)
	return b;
	return a;
}
int main()
{
	int n;
	cout<<"ENter no. of vertices ";
	cin>>n;
	int a[n][n],i,j;
	cout<<"enter distance matrix ";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		cin>>a[i][j];
		
	}
	cout<<"Assuming we have to calculate distance from first point"<<endl;
	int d[n],min,v[n];
	for(i=0;i<n;i++){
	d[i] = a[0][i];
	v[i] = 0;
	}
	v[0]=1;
	for(i=0;i<n-1;i++)
	{
	int k = calmin(v,d,n);
	if(d[i] > a[k][i] + d[k])
	d[i] = a[k][i] + d[k];
}
	cout<<endl;
	for(i=0;i<n;i++)
	cout<<d[i]<<" ";
}
