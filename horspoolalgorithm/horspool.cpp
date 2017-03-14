#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
using namespace std;

void crea(char b[],int a[],int l)
{
	int i;
	for(i=0;i<26;i++)
		a[i]=l;
		
	for(i=0;i<l-1;i++)
	{
		int t = b[i]-'a';
		cout<<t;
		a[t] = l-i-1;
	}
}
int main()
{
	char a[1000],b[100];
	cout<<"Enter string in which we will search"<<endl;
	scanf("%s",a);
	cout<<"Enter string to be searched"<<endl;
	scanf("%s",b);
	int i=0;
	int l=strlen(b);
	int n=strlen(a);
	
	int ind[26];
	crea(b,ind,l);
	for(i=0;i<26;i++)
		cout<<" "<<ind[i];
	
	
	i=l-1;
	int j=0,pos;
	int flag=0;
	while(i<n)
	{
		if(a[i]==b[0])
			{
				for(j=0;j<l;j++)
				{
					if(a[i-j]==b[j])
						flag++;
				}
				if(l==flag)
					pos = i;
				else
					flag=0;
			}
	}
	cout<<endl<<"position is "<<pos;
}


