#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
typedef struct tree{
	int d;
	struct tree *l,*r;
}TREE;
typedef TREE * TREEPTR;
int max1=0;
int t=0;
int maxval(int a,int b)
{
	if(a>b)
	return a;
	return b;
}
int height(TREEPTR node)
{
	if(node == NULL)
	return 0;
	
	
	return maxval(height(node->l),height(node->r)) + 1;
	

	
	
}
void dia(TREEPTR node)
{
	if(node == NULL)
	return;
	
	if(node->l)
	dia(node->l);
	
	t = height(node->l) + height(node->r) + 1;
	cout<<node->d<<" "<<t<<endl;
	if(t>max1)
	max1 = t;
	
	if(node->r)
	dia(node->r);
}
TREEPTR build_tree(TREEPTR node,int data)
	{
	//cout<<"We are here";
	TREEPTR temp,prev=NULL;
	temp = node;
	while(temp!=NULL)
	{
		prev = temp;
		if(temp->d < data)
		temp = temp->r;
		
		else if(temp->d > data)
		temp = temp->l;
		
		else{
		return node;
		cout<<"repeated value ";
	}
}
	
	if(data > prev->d)
	{
		TREEPTR temp1 = (TREE*)malloc(sizeof(TREE));
		prev->r = temp1;
		temp1->d = data;
		temp1->r=NULL;
		temp1->l=NULL;
		
	}
	else if(data < prev->d)
	{
		TREEPTR temp1 = (TREE*)malloc(sizeof(TREE));
		prev->l = temp1;
		temp1->d = data;
		temp1->r=NULL;
		temp1->l=NULL;
		
	}
	else 
	cout<<"Repeated value ";
	
	return node;
}
int main()
{
	int data;
	cout<<"ENter numbers for bst "<<endl;
	TREEPTR node = (TREEPTR)malloc(sizeof(TREE));
	cout<<"ENter values and enter -1 to exit ";
	cin>>data;
	node->d = data;
	node->l = NULL;
	node->r = NULL;
	cout<<node->d;
	
	while(data!=-1){
			cout<<"ENter next value ";
	cin>>data;
	node = build_tree(node,data);

}
	cout<<"input done";
	dia(node);
	cout<<max1;
	
}
