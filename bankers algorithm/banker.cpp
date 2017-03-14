#include<iostream>
using namespace std;
int check(int a[],int b[],int l)
{
	for(int i=0;i<l;i++)
	if(a[i]-b[i]<0)
	return 0;
	
	return 1;
}
void add(int a[],int b[],int l)
{
	for(int i=0;i<l;i++)
	a[i] = a[i]+b[i];
}
int main()
{
	cout<<"Enter number of processes ";
	int n,i,j;
	cin>>n;
	cout<<"Enter number of resources ";
	int m;
	cin>>m;
	int al[n][m],max[n][m],av[m],done[n],need[n][m],flag;
	cout<<"ENter allocation matrix";
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		cin>>al[i][j];
	}
	cout<<"ENter max matrix";
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		cin>>max[i][j];
	}
	cout<<"Enter available matrix ";
	for(i=0;i<m;i++)
	cin>>av[i];
	
	for(i=0;i<n;i++)
	done[i]=0,flag=1;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		need[i][j] = max[i][j] - al[i][j];
	}
	for(j=0;j<=n+10;j++){
	for(i=0;i<n;i++)
	{
		if((check(av,need[i],m))&&(!done[i]))
		{
		done[i] = flag;
		flag++;	
		add(av,al[i],m);
		
		}
		
	}
}
	for(i=0;i<n;i++)
	cout<<done[i]<<" ";
	cout<<endl;//if any element in done is 0 then deadlock situation has arised
	int list[n+1];
	for(i=0;i<n;i++)
	{
		list[done[i]] = i+1;
	}
	for(i=0;i<n;i++)
	{
		cout<<list[i+1]<<" ";
	}
	 
}
