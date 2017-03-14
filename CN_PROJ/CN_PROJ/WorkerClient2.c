#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <crypt.h>

struct pass_str {
	char ip[20];
	char pass[20];
	char lb[20];
	char ub[20];};

struct result {
	char res[20];
	int flag;};

int flag;
char res[20];

int solve(char *a,char *b)
{
    int i;
    int n=strlen(a);
    for(i=0;i<n;i++)
    {
        if(a[i]!=b[i])
        return 0;
    }
    return 1;
}
int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z'){
        c[0]='a';
        return inc(c+sizeof(char));
    } 
    c[0]++;
    return 1;
}

int perm(int n,char *p,char *l,char *u)
{
   
    int i,j,k=0;
  
        char *d;   
     char *c = (char *)malloc((n+1)*sizeof(char));   
     char *z = (char *)malloc((n+1)*sizeof(char));
   
    strcpy(c,l);
    strcpy(z,u);
   
   
    while(c[0]<=z[0])
    {
   
    d=crypt(c,"aa");
    k=solve(d,p);
        if(k)
              break;
    c[n-1]++;
    if(c[n-1]-'z' == 1)
    {
   
    for(i=n-1;i>0;i--)                   
        {           
        if(c[i]>'z')
            {
            c[i-1]++;
            c[i]='a';
            }
        }
    }
    }
    if(k)
	{
		strcpy(res,c);
    		printf("%d %s",flag,c);
	}

    else
    printf("not found ");

	return k;
   
}
void main()
{
	struct pass_str workval;
	int sd,newsd;
	int n,m,p=0;
	int num;
	struct sockaddr_in sadd,cadd;
	sd=socket(AF_INET,SOCK_STREAM,0);
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	sadd.sin_port=htons(12600);

	n=bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
	
	listen(sd,1);

	int len=sizeof(cadd);
	newsd=accept(sd,(struct sockaddr*)&cadd,&len);
	
	m=read(newsd,(struct pass_str*)&workval,sizeof(struct pass_str));
	printf("The value received for decryption is %s%s%s %s\n",workval.lb,workval.ub,workval.ip,workval.pass);
	int i;
	int k=perm(4,workval.pass,workval.lb,workval.ub);

	printf("%d\t",k);
	struct result r;
	r.flag=k;
	if(k)
		strcpy(r.res,res);
	
	n=write(newsd,(struct result*)&r,sizeof(struct result));	
}

