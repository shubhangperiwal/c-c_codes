#include<iostream>
using namespace std;
int sum=9999;
int c[100][100];
int d[100];
void perm(int b[],int n,int l)
{
	int i,temp=0;
	if(n==l)
	{
	for(i=0;i<=n;i++){
		
		temp = temp + c[i][b[i]];
	}
	if(temp<sum)
	{
		sum = temp;
		for(int k=0;k<=n;k++)
		{
			d[k] = b[k];
		}
	}
		//cout<<b[i]<<" ";
		
	}
	else{
		for(i=l;i<=n;i++){
			swap(b[l],b[i]);
			perm(b,n,l+1);
			swap(b[l],b[i]);
		}
	}
}
int main()
{
	cout<<"Enter number of assignments ";
	int n,i,j;
	cin>>n;
	int a[n][n];
	cout<<"Enter the assignment matrix ";
	cout<<endl;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++){
	cin>>a[i][j];
	c[i][j] = a[i][j];
}
	int b[n];
	for(i=0;i<n;i++)
	b[i] = i;
	
	cout<<endl;
	perm(b,n-1,0);
	for(i=0;i<n;i++)
	cout<<d[i]<<" ";
	cout<<endl<<sum;
}

