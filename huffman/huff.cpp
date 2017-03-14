#include<iostream>
#include<stdlib.h>
char code[10];
int top;
using namespace std;
typedef struct tree{
	int f;
	struct tree *l,*r;
	char c;
}TREE; 
void sort(TREE *t[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(t[i]->f > t[j]->f)
			{
				TREE *temp = (TREE *)malloc(sizeof(TREE));
				temp = t[i];
				t[i] = t[j];
				t[j] = temp;
			}
		}
	}
}
	
void inorder(TREE* t)
{
	if(t == NULL)
	return;
	
	if(t->l)
	{
	code[top] = '0';	
	top++;
	inorder(t->l);
	top--;
	}
	if(t->c != ' ')
	{
		cout<<t->c<<" "<<"= ";
		for(int i=0;i<top;i++)
		cout<<code[i];		
		cout<<endl;
	}
	if(t->r)
	{
	code[top] = '1';
	top++;
	inorder(t->r);
	top--;
	}
}

int main()
{
	int n;
	cout<<"ENter no. of characters ";
	cin>>n;
	int fv[n];
	char c[n];
	int i,j;
	top = 0;
	cout<<"ENter frequence table ";
	for(i=0;i<n;i++)
	{
		cin>>c[i];
		cin>>fv[i];
	}
	TREE *t[n];
	for(i=0;i<n;i++)
	{
		t[i] = (TREE *)malloc(sizeof(TREE));
		t[i]->f = fv[i];
		t[i]->c = c[i];
	}
	i=0;
	int k=n;
	while(i<n-1)
	{
		sort(t,k);
		TREE *temp = (TREE *)malloc(sizeof(TREE));
		temp->f = t[0]->f + t[1]->f;
		temp->l = t[0];
		temp->r = t[1];
		temp->c = ' ';
		t[0] = temp;
		for(j=1;j<k-1;j++)
		{
			t[j] = t[j+1];
		}		
		i++;
		k--;	
	}
	cout<<endl;
	inorder(t[0]);
}
