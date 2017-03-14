#include<iostream>

#include<stdio.h>
#include<stdlib.h>
using namespace std;



typedef struct process{
	int pid;
	int at;
	int bt;
	int wt;
	int tt;
	int rbt;
	
	}proc;

int main(){
	
	int n;
int i;
printf("enter the number of process");
scanf("%d",&n);
proc a[n];

printf("\nenter at and bt for processes");
for(i=0;i<n;i++){
	a[i].pid=i+1;
	scanf("%d",&a[i].at);
	scanf("%d",&a[i].bt);
	a[i].rbt=a[i].bt;
	}
	
int tq;
printf("\nenter the time quantum");
scanf("%d",&tq);


int k=0;
//int rtq=0;
int fin[n];
for(i=0;i<n;i++){
	fin[i]=0;
	// unfinished process marked 0.	
	}
int sum;
int flag=0;	
int ttq=0;
printf(" pid   rbt    tq\n");


for(i=0;i<n;i++){
		sum+=a[i].rbt;
		}


while(1){
	sum=0;
	for(i=0;i<n;i++){
		sum+=a[i].rbt;
		}
		
	if(sum==(-n))
	exit(0);
	
	
	if(a[k].rbt>tq && fin[k]!=1 && a[k].at<=ttq){
		
		a[k].rbt=a[k].rbt-tq;
		ttq+=tq;
		printf(" %d \t %d \t %d\n",a[k].pid,a[k].rbt,ttq);
		int min=9999;
		for(int j=0;j<n;j++)
			{
				if((a[j].at <= ttq) && (fin[j]!=1) && (min>a[j].rbt))
				{
					min=a[j].rbt;
					k=j;
										
				}
			}
		
		

		
		}
	else if(a[k].rbt<=tq && a[k].rbt>=0 && a[k].at<= ttq){
		ttq+=a[k].rbt;
		printf(" %d \t %d \t %d\n",a[k].pid,0,ttq);
		a[k].rbt=-1;
		
		fin[k]=1;
		int min=9999;
		
		for(int j=0;j<n;j++)
			{
				if((a[j].at <= ttq) && (fin[j]!=1) && (min>a[j].rbt))
				{
					min=a[j].rbt;
					k=j;
										
				}
			}
		
		}
	else{
		flag=0;
		int min=9999;
		while(flag==0){
		for(int j=0;j<n;j++)
			{
				if((a[j].at <= ttq) && (fin[j]!=1) && (min>a[j].rbt))
				{
					min=a[j].rbt;
					k=j;
					flag =1;
					
				}
			}
			if(flag==0)
			ttq++;
		}
		}
	
	}
}
