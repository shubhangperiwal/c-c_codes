#include<iostream>
using namespace std;
int max(int a,int b)
{
	if(a>b)
	return a;
	
	return b;
}
int main()
{
	int n,w,i,j,l=0;
	int b[n];
	cout<<"Enter no. of items ";
	cin>>n;
	cout<<"Enter allowed weight ";
	cin>>w;
	int a[n][2];
	cout<<"Enter weight and value ";
	for(i=0;i<n;i++)
	{
		cin>>a[i][0]>>a[i][1];
	}
	int r[n+1][w+1];
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=w;j++)
		{
		if(i==0 || j==0)
		r[i][j] = 0;
		
		else if(a[i-1][0] < j)
			{
			r[i][j] = max(a[i-1][1] + r[i-1][j-a[i-1][0]],r[i-1][j]);
			
				
			}
		else
				r[i][j] = r[i-1][j];
		}
	}
	cout<<r[n][w];
	cout<<endl;
	for(i=0;i<l;i++)
	cout<<b[i]<<" ";
}
