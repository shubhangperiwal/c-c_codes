#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<math.h>

int no_of_users; //Integer representing the users which are stored in the server

struct users {				//A structure to store the username and encrypted password of users
	char username[50];
	char password[50];};


struct register_t {			//When a client requires a service , this structure is received
	int functionality;		//Defines the operation, i.e., either registering or hacking
	char username[50];
	char password[50];};		//invalid if the functionality is hacking

struct pass_str {			//structure passed to all worker_clients
	char ip[20];
	char pass[20];			
	char lb[20];			//lowerbound and upperbound to be searched
	char ub[20];};

struct result {				//The result passed to the user
	char res[20];
	int flag;};

pthread_t p2[10];			//pthreads for corresponding worker_clients
char target_user[50];
struct users usrs[10];
struct result r;

void Terminate_all_threads(struct result r)
{
	printf("\n\n\n\tThe password is\t%s\n\n",r.res);
	for(int i=0;i<3;i++)
		pthread_cancel(p2[i]);		//Terminate before finishing
}


void* runner1(void *param)
{
/*
Function is run in parallel for each worker client for a different set of lower bound and upper bounds.

Each function retrieves the structure containing the password if found.
*/
	struct pass_str* args=param;
	struct pass_str temp;
	
	r.flag=0;
	char* c=(char*)malloc(10*sizeof(char));
	strcpy(c,args->ip);
	printf("%s %s %s %s \n",args->ip,args->pass,args->lb,args->ub);
	strcpy(temp.ip,args->ip);
	strcpy(temp.pass,args->pass);
	strcpy(temp.lb,args->lb);
	strcpy(temp.ub,args->ub);
	int csd,cnewsd;
	struct sockaddr_in csadd,ccadd;
	int num=3;

	csd=socket(AF_INET,SOCK_STREAM,0);
	csadd.sin_family=AF_INET;
	csadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	csadd.sin_port=htons(atoi(temp.ip));

	int result=connect(csd,(struct sockaddr*)&csadd,sizeof(csadd));
	if(result==-1)
		perror("Connection Failed. Try Again");
	int m=write(csd,(struct pass_str*)&temp,sizeof(struct pass_str));

	int n=read(csd,(struct result*)&r,sizeof(struct result));
	
	printf("%s %d\n",temp.lb,r.flag);
	
	if(r.flag)
		Terminate_all_threads(r);	//Password Found and hence termination

}

void *runner(void *param)
{
/*
Function distributes the load on different worker clients by distributing the range.

It calls the respective runner functions for implementing each worker client.
*/
	int i,num = atoi(param);
	char password[50];
	for(i=0;i<no_of_users;i++)
	{
		if(strcmp(target_user,usrs[i].username)==0)
			strcpy(password,usrs[i].password);
	}
	num=4;
	struct pass_str workerclients[10];
	strcpy(workerclients[0].ip,"12300");	//worker clients ports being used
	strcpy(workerclients[1].ip,"12400");
	strcpy(workerclients[2].ip,"12600");
	int no_of_clients=3;
	float fact;
	fact=(float)25/no_of_clients*1.0;
	char last[10];
	char first[10];
	for(i=1;i<num;i++)
	{
		first[i]='a';
		last[i]='z';
	}
	first[i]='\0';
	last[i]='\0';
	for(int i=0;i<3;i++)
	{
		float f1=(float)fact*i;
		float f2=(float)fact*(i+1);			//distribution of range 
		int d1=ceil(f1);
		int d2=floor(f2);
		printf("%f %f\n",f1,f2);
		first[0]=(char)(d1+97);
		last[0]=(char)(d2+97);
		strcpy(workerclients[i].lb,first);
		strcpy(workerclients[i].ub,last);
		strcpy(workerclients[i].pass,password);
		pthread_create(&p2[i],NULL,runner1,(void*)&workerclients[i]); //call worker client function
	}
	for(int i=0;i<3;i++)
		pthread_join(p2[i],NULL);
	pthread_exit(0);
}

int main()
{
	pthread_t p1;
	struct register_t rgs;
	
	no_of_users=0;
	char num[2];
	num[0]='4';
	num[1]='\0';
	int sd;
	int n,m,p=0;
	struct sockaddr_in sadd,cadd;
	sd=socket(AF_INET,SOCK_STREAM,0);
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	sadd.sin_port=htons(10200);
	pid_t pid;
	n=bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
	
	listen(sd,3);

	int len=sizeof(cadd);

						//Iterative for supporting different users and functionalities
	for(;;)
	{
		char num;
		num=4;
		int newsd=accept(sd,(struct sockaddr*)&cadd,&len);
		{
			int m1=read(newsd,(struct register_t*)&rgs,sizeof(struct register_t));
			switch(rgs.functionality)
			{
			case 1:
				strcpy(usrs[no_of_users].username,rgs.username);
				strcpy(usrs[no_of_users].password,rgs.password);
				printf("Username\t%s\n",usrs[no_of_users].username);  
				printf("Password\t%s\n",usrs[no_of_users].password);
				(no_of_users)++;
			break;
			
			case 2:
				printf("Username\t%s\n",rgs.username);  
				printf("Password\t%s\n",rgs.password);
				strcpy(target_user,rgs.username);
				pthread_create(&p1,NULL,runner,&num);
				pthread_join(p1,NULL);
				int m1=write(newsd,(struct result*)&r,sizeof(struct result));
			break;
			}
			
			close(newsd);
		}
		close(newsd);
	}		
	return 0;
}


