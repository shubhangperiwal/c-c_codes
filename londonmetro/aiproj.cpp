#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct station
{
	char name[30];
	int no_of_neighbors;
	struct station *neighbors;
}STATION;

STATION *london[20][100];
int counter[12];

void displayall()
{
	int i=0,j=0;	
	for(i=0;i<11;i++)
	{
		for(j=0;j<2;j++)
		cout<<london[i][j].name[0]<<endl;
		cout<<endl;
	}
}
void storedata()
{
	int i=0,j=0,k=0;
	char c;
	
	char buffer[20];
	FILE *f1=fopen("stationlist.txt","r");
	
	
	if(f1 == NULL)
		{
		printf("Cannot open file\n");
		exit(0);
		}
	
	i=-1;	
	c=fgetc(f1);
	while(c!=EOF)	
	{	
		int count=0;
		while(!isalpha(c))
			{		
			if(c == '\n')			
			count++;
			c=fgetc(f1);		
			}
		
			
			if(count > 1)
			{
			
			j=0;
			count=0;
			i++;	
					
			}	
					
			while(c!='\n')
			{
			buffer[k] = c;
			c = fgetc(f1);
			k++;
			}
		
			london[i][j] = (STATION *)malloc(sizeof(STATION));
			strcpy(london[i][j]->name,buffer);	
			london[i][j].name[k] = '\0'; 
			j++;			
			k=0;	
			//cout<<london[i][j].name<<endl;
			
			for(int x=0;x<20;x++)
			buffer[x] = 0;

		

	}
		
}
int main()
{
	
		
	storedata();
	
	//displayall();

	char source[20],destination[20];
	cout<<"Enter the name of the first station ";
	gets(source);
	cout<<"Enter the name of the second staion ";
	gets(destination);
}
