#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct station
{
	char name[50];
	int no_of_neighbors;
	struct station *neighbors;
	struct station *s_parent;
	struct station *d_parent;
	int count;
	
}STATION;

STATION** london;
int counter[12];
char source[30],destination[30];
STATION *visited_s[1000],*visited_d[1000];
int v_s=0,v_d=0;
int top1=0,top2=0;

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
typedef struct tree
{
	char name[30];
	struct tree *children[12];
}TREE;

typedef TREE * TREEPTR;



int in_visited_s(char *c)
{
	int i=0;
	for(;i<v_s;i++)
	{
		if(!strcmp(visited_s[i]->name,c))
		return 1;
	}	
	return 0;
}
void displayall()
{
	int i=0,j=0;	
	for(i=0;i<=12;i++)
	{
		for(j=0;j<counter[i];j++){
		cout<<london[i][j].name<<" "<<london[i][j].no_of_neighbors<<endl;
		for(int x=0;x<london[i][j].no_of_neighbors;x++)
		{
			cout<<london[i][j].neighbors[x].name<<endl;
		}
	}
}
}

void storedata()
{
	int i=0,j=0,k=0;
	char c;
	
	char buffer[30];
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
		while(!isalpha(c) && c!=EOF)
			{		
			if(c == '\n')			
			count++;
			c=fgetc(f1);		
			}
		
			
			if(count > 1)
			{
			counter[i]=j;
			j=0;
			count=0;
			i++;	
					
			}	
			memset(buffer,0,30);		
			while(c!='\n' && c!=EOF)
			{
			buffer[k] = c;
			c = fgetc(f1);
			k++;
			}
			//cout<<i<<"here"<<j;
			
			
			
			strcpy(london[i][j].name,buffer);	
			london[i][j].count = 0;
			//london[i][j].name[0]=buffer[0];
			
			//london[i][j].name[k] = '\0'; 
			k=0;
			//cout<<london[i][j].name<<endl;
			j++;					
		
		

	}
		
}

void find_no_of_neig()
{
	int i=0,j=0,k=0,l=0;
	for(i=0;i<12;i++)
	{
		for(j=0;j<counter[i];j++)
		{
			london[i][j].no_of_neighbors=0;
			for(k=0;k<12;k++)
			{
				for(l=0;l<counter[k];l++)
				{
				if(!strcmp(london[i][j].name,london[k][l].name))
						{
						if(j == counter[i]-1 || j == 0)
						london[i][j].no_of_neighbors +=1;
						else
						london[i][j].no_of_neighbors +=2;	
						if(l-1 > 0)
						london[i][j].neighbors[london[i][j].no_of_neighbors - 1] = london[k][l-1];
						if(l+1 < counter[k])
						london[i][j].neighbors[london[i][j].no_of_neighbors - 2] = london[k][l+1];
						}
				}
			}
			
		}
	}
}
/*
void bfs(TREEPTR c)
{
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<counter[i];j++)
		{
			if(!strcmp(c->name,london[i][j].name))
			{
				for(int k=0;k<london[i][j].no_of_neighbors;k++)
				{
					c->children[k] = (TREEPTR)malloc(sizeof(TREE));
					strcpy(c->children[k].name,london[i][j].neighbors[k].name);
				}
			}
		}
	}
}
*/
void bfs1(STATION *node)
{
	int flag=0;
	
	for(int i=0;i<node->no_of_neighbors;i++)
		{
			for(int j=0;j<v_s;j++)
			{
				if(!strcmp(node->neighbors[i].name,visited_s[j]->name))
				{
				flag=1;	
				}
			}
			 
			if(!flag)
			{			
			
			visited_s[v_s] = &(node->neighbors[i]);
			
			v_s++;
			flag=0;
			//cout<< node->neighbors[i].name<<" ";
			node->neighbors[i].s_parent = visited_s[i];
			}
			flag=0;
		}
		
		
}

void bfs2(STATION *node)
{
	int flag=0;
	
	for(int i=0;i<node->no_of_neighbors;i++)
		{
			for(int j=0;j<v_d;j++)
			{
			
				if(!strcmp(node->neighbors[i].name,visited_d[j]->name))
				{
				flag=1;	
				}
			}
			
			if(!flag)
			{
			
			visited_d[v_d] = &(node->neighbors[i]);
			v_d++;
			flag=0;
			//cout<< node->neighbors[i].name<<" ";

			node->neighbors[i].d_parent = visited_d[i];
						
			}
			flag=0;
		}
		
}

int main()
{
	int i,j=0;
	london=(STATION**)malloc(20*sizeof(STATION*));
	for(i=0;i<20;i++){
			london[i]=(STATION*)malloc(100*sizeof(STATION));
			
			}
	for(i=0;i<20;i++)
	for(j=0;j<100;j++)
	london[i][j].neighbors = (STATION*)malloc(16*sizeof(STATION));
	
		
	storedata();
	find_no_of_neig();
	displayall();

	
	cout<<"Enter the name of the source station ";
	gets(source);
	cout<<"Enter the name of the  destination station ";
	gets(destination);
	int l1,w1,l2,w2,flag=0;
	for(i=0;i<12;i++)
	{
		for(j=0;j<counter[i];j++)
		{
			if(!strcmp(source,london[i][j].name))
			{
			l1=i;
			w1=j;
			flag=1;
			break;
			}
		}
		
			if(flag==1)
			break;
	}
	flag=0;			
	for(i=0;i<12;i++)
	{
		for(j=0;j<counter[i];j++)
		{
			if(!strcmp(destination,london[i][j].name))
			{
			l2=i;
			w2=j;
			flag=1;
			break;	
			}
		}
		if(flag==1)
			break;

	}

	london[l1][w1].s_parent = NULL;
	london[l2][w2].d_parent = NULL;
	
	int done = 0;
	visited_s[0] = &london[l1][w1];
	v_s = 1;
	v_d = 1;
	top1 = 0;
	top2 = 0;
	visited_d[0] = &london[l2][w2];
	while(!done)
	{
	//	cout<<endl;
		int temp = v_s;
		for(i=top1;i<temp;i++)
		{
		bfs1(visited_s[i]);		
		top1++;
		
		}
		cout<<endl<<"source over "<<endl;
		
	
		temp = v_d;
		for(i=top2;i<temp;i++)
		{
		bfs2(visited_d[i]);
		top2++;		
		}
	
		cout<<endl<<"destination over "<<endl;
	//	cout<<endl;
		
		
		for(i=0;i<v_s;i++)
		{
			for(j=0;j<v_d;j++)
			{
			
				if(!strcmp(visited_s[i]->name,visited_d[j]->name))
				{
				
				done = 1;
				cout<<endl;
				cout<<"the intersection meet is ";
				cout<<endl;
				cout<<visited_d[j]->name;
				}
			}
		}
		
		for(i=0;i<v_s;i++)
		if(!strcmp(destination,visited_s[i]->name)) 
		cout<<"Found";
		
	}
		
}

