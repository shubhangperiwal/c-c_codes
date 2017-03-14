#include<iostream>
using namespace std;
int a[100][100];
int s[100];
int top=0;
int q[100];
int is_not_present(int n,int k,int s[])
{
	int i;
	for(i=0;i<n;i++)
	if(s[i]==k)
	return 0;
	
	return 1;
}
void bfs(int k,int n,int w)
{
	int i=0,j=0;
	while(top!=w-1)
	{
		
		if(a[k][i]==1)
		{
			if(is_not_present(n,k,q))
			cout<<i<<" ";
			
			q[top] = i;
			top++;
		}
		k=q[j];
		j++;
	}
	
}
void dfs(int k,int n)
{
	int i=0;
	for(;i<n;i++)
	{
		if(a[k][i] == 1)
		{
			if(is_not_present(n,i,s)){
			cout<<i<<" ";
			s[top] = i;
			top++;
			//a[i][k]=0;
			//a[k][i]=0;
			dfs(i,n);
		}
		}
	}
}
int main()
{
	int n,i,j;
	cout<<"Enter number of vertices ";
		cin>>n;
	
	cout<<"Enter adj matrix "<<endl;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		cin>>a[i][j];
	}
	cout<<"0"<<" ";
	s[0] = 0;
	top++;
		int w=n;
	int count=0;
			dfs(0,n);
			for(i=0;i<n;i++){
	for(j=0;j<n;j++){
	if(a[i][j]==0)
	count++;
	}
	if(count==5){
	cout<<i<<" ";
	w--;
}
}
cout<<endl;

	top=0;
	for(i=0;i<n;i++){
	for(j=0;j<n;j++){
	if(a[i][j]==0)
	count++;
	}
	if(count==5){
	cout<<i<<" ";
	w--;
}
count = 0;
q[i]=0;


}

//bfs(0,n,w);
}
