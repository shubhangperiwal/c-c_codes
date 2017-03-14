#include<iostream>
using namespace std;
typedef struct edj{
	int v1,v2;
	int d;
}EDJ;
void sort(EDJ a[],int n)
{
	int i=0,j=0;
	for(;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[i].d > a[j].d)
			{
				EDJ temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
int main()
{
	int n,v,i,j,k=0;
	cout<<"Enter number of edges ";
	cin>>n;
	cout<<"Enter number of vertices ";
	cin>>v;
	EDJ a[n];
	cout<<"Enter each edge then distance ";
	for(i=0;i<n;i++)
	{
		cin>>a[i].v1;
		cin>>a[i].v2;
		cin>>a[i].d;
	}
	sort(a,n);
	int b[v];
	EDJ res[v-1];
	for(i=0;i<n;i++)
	{
				
		if(b[a[i].v1]==0 || b[a[i].v2]==0)
		{
		res[k] = a[i];
		b[a[i].v1] = 1;
		b[a[i].v2] = 1;
		k++;
		}
	}
	for(i=0;i<v-1;i++)
	{
		cout<<"edge "<<a[i].v1<<" "<<a[i].v2<<" "<<a[i].d;
		cout<<endl;
	}
}

