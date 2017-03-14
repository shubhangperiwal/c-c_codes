#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	int n;
	cout<<"ENter number of numbers in the disjoint set ";
	cin>>n;
	int a[n],b[n];
	
	int i,j;
	cout<<"Enter numbers ";
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		b[i]=0;
	}
	
	int k = pow(2,n);
	int sum[k][n+1];
	for(i=0;i<k;i++)
	{
		for(j=0;j<n+1;j++)
		{
			sum[i][j] = 0;
		}
	}
	cout<<"reached here !!";
	i=0;
	
	while(i<=k)
	{
			for(j=0;j<n;j++)
			{
				if(b[j])
				{
					
				sum[i][j] = a[j];
				sum[i][n] = sum[i][n] + a[j];
				}
			}
			
		if(b[n-1]==0)
		b[n-1]++;
		
			else
			{
			b[n-1] = 0;
			for(j=n-2;j>=0;j--)
				{
				if(b[j]==0)
					{
					b[j]++;
					break;
					}
				else
					b[j]=0;
				}
			}
			
	
			
			i++;
		}
		for(i=0;i<k;i++)
		{
			for(j=0;j<n+1;j++)
			cout<<sum[i][j]<<" ";
			cout<<endl;
		}
	
		int w=0,flag=0;
		for(j=0;j<k-1;j++)
		for(i=j+1;i<k;i++)
		{
			if(sum[j][n] == sum[i][n])
			{
				flag=0;
				for(w=0;w<n;w++)
				{
					if(sum[j][w] == sum[i][w] && sum[i][w]!=0 && sum[j][w]!=0)
					flag=1;
				}
				
				if(!flag)
				{
					
					cout<<endl;
					cout<<"first set is "<<endl;
					for(w=0;w<n;w++)
					{
						if(sum[j][w]!=0)
						cout<<sum[j][w]<<" ";
					}
					
					cout<<endl;
					cout<<"Second set is "<<endl;
					for(w=0;w<n;w++)
					{
						if(sum[i][w]!=0)
						cout<<sum[i][w]<<" ";
					}
					cout<<endl<<"one pair above ";
				}
			}
		}
		
}
