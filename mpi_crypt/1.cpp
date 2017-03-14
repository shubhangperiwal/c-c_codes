#include "mpi.h"
#include<string.h>
#include<stdio.h>
#include<Windows.h>
#include<wincrypt.h>
#include<stdlib.h>
#include<math.h>

char res[20];
struct users {				//A structure to store the username and encrypted password of users
	char username[50];
	char password[50];
	char filename[50];
};


struct register_t {			//When a client requires a service , this structure is received
	int functionality;		//Defines the operation, i.e., either registering or hacking
	char username[50];
	char password[50];
};		//invalid if the functionality is hacking

struct pass_str {			//structure passed to all worker_clients
	char ip[20];
	char pass[20];
	char lb[20];			//lowerbound and upperbound to be searched
	char ub[20];
};

struct result {				//The result passed to the user
	char res[20];
	int flag;
};

char target_user[50];
struct users usrs[10];
struct result r;
char rbuf[50];
int file_buf_size;
int no_of_users;

char* crypt(char password[], int key)
{
	int i;
	char *password1 = (char*)malloc(5*(sizeof(char)));
	for (i = 0; i < strlen(password); i++)
	{
		password1[i] = (char)((int)password[i] - key);
	}
	password1[i] = '\0';
	return password1;
}

int solve(char *a, char *b)
{
	int i;
	int n = strlen(a);
	for (i = 0; i<n; i++)
	{
		if (a[i] != b[i])
			return 0;
	}
	return 1;
}


int inc(char *c) {
	if (c[0] == 0) return 0;
	if (c[0] == 'z') {
		c[0] = 'a';
		return inc(c + sizeof(char));
	}
	c[0]++;
	return 1;
}


int perm(int n, char *p, char *l, char *u)
{

	int i, j, k = 0;

	char *d;
	char *c = (char *)malloc((n + 1)*sizeof(char));
	char *z = (char *)malloc((n + 1)*sizeof(char));

	strcpy(c, l);
	strcpy(z, u);

	//printf("%s %s ", c , crypt(c,32));
	while (c[0] <= z[0])
	{

		d = crypt(c, 32);
		k = solve(d, p);
		//if(d[0]=='J'&& d[1]=='U')
			//printf("%s kk\n", c);
		if (k)
		{
			break;
		}
		c[n - 1]++;
		if (c[n - 1] - 'z' == 1)
		{

			for (i = n - 1; i > 0; i--)
			{
				if (c[i] > 'z')
				{
					c[i - 1]++;
					c[i] = 'a';
				}
			}
		}
	}
	if (k)
	{
		strcpy(res, c);
		printf("%s", c);
	}

	else
		printf("not found ");
	return  k;

}


void Return_Contents_Of_File(struct register_t rgs)
{
	int p = 0;

	if ((strcmp(usrs[0].username, rgs.username) == 0) && (strcmp(usrs[0].password, rgs.password) == 0))
	{
		FILE * file1;
		int c;
		char filename[50];

		strcpy(filename, usrs[0].filename);
		file1 = fopen(filename, "r");
		if (file1)
		{
			while ((c = getc(file1)) != EOF)
			{
				rbuf[p++] = c;
			}
			rbuf[p] = '\0';
			fclose(file1);
		}
		file_buf_size = p;
		printf("%s\n", rbuf);
	}
	else if ((strcmp(usrs[1].username, rgs.username) == 0) && (strcmp(usrs[1].password, rgs.password) == 0))
	{
		FILE * file1;
		int c;
		char filename[50];

		strcpy(filename, usrs[1].filename);
		file1 = fopen(filename, "r");
		if (file1)
		{
			while ((c = getc(file1)) != EOF)
			{
				rbuf[p++] = c;
			}
			rbuf[p] = '\0';
			fclose(file1);
		}
		file_buf_size = p;
		printf("%s\n", rbuf);
	}


}

int main(int argc, char* argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	struct register_t rgs;

	strcpy(usrs[0].username, "raviteja");
	strcpy(usrs[0].password, "ravi");
	strcpy(usrs[0].filename, "file1.txt");

	strcpy(usrs[1].username, "armaan");
	strcpy(usrs[1].password, "jude");
	strcpy(usrs[1].filename, "file2.txt");

	no_of_users = 2;

	if (rank == 0)
	{
		int i, num;
		printf("Enter target user\n");
		fflush(stdout);
		scanf("%s", target_user);
		char password[50];
		for (i = 0; i < no_of_users; i++)
		{
			if (strcmp(target_user, usrs[i].username) == 0)
				strcpy(password, usrs[i].password);
		}
		num = 4;
		strcpy(password , crypt(password, 32));
		struct pass_str workerclients[10];

		int no_of_clients = 3;
		float fact;
		fact = (float)25 / no_of_clients*1.0;
		char last[10];
		char first[10];
		for (i = 1; i < num; i++)
		{
			first[i] = 'a';
			last[i] = 'z';
		}
		first[i] = '\0';
		last[i] = '\0';
		for (int i = 0; i < 3; i++)
		{
			float f1 = (float)fact*i;
			float f2 = (float)fact*(i + 1);			//distribution of range 
			int d1 = ceil(f1);
			int d2 = floor(f2);
			printf("%f %f\n", f1, f2);
			first[0] = (char)(d1 + 97);
			last[0] = (char)(d2 + 97);
			strcpy(workerclients[i].lb, first);
			strcpy(workerclients[i].ub, last);
			strcpy(workerclients[i].pass,password);
			//call worker client function
			MPI_Send(workerclients[i].pass, strlen(workerclients[i].pass), MPI_CHAR, i + 1, 3 * (i + 1), MPI_COMM_WORLD);
			MPI_Send(workerclients[i].lb, strlen(workerclients[i].lb), MPI_CHAR, i + 1, 3 * (i + 1) + 1, MPI_COMM_WORLD);
			MPI_Send(workerclients[i].ub, strlen(workerclients[i].ub), MPI_CHAR, i + 1, 3 * (i + 1) + 2, MPI_COMM_WORLD);
		}
	}
	else
	{
		int num;
		struct pass_str workval;
		MPI_Status status;
		MPI_Recv(workval.pass, strlen(workval.pass), MPI_CHAR, 0, 3 * rank, MPI_COMM_WORLD, &status);
		workval.pass[status.count] = '\0';
		MPI_Recv(workval.lb, strlen(workval.lb), MPI_CHAR, 0, 3 * rank + 1, MPI_COMM_WORLD, &status);
		workval.lb[status.count] = '\0';
		MPI_Recv(workval.ub, strlen(workval.ub), MPI_CHAR, 0, 3 * rank + 2, MPI_COMM_WORLD, &status);
		workval.ub[status.count] = '\0';
		printf("The value received for decryption is %s%s %s\n", workval.lb, workval.ub, workval.pass);
		int i;
		int k = perm(4, workval.pass, workval.lb, workval.ub);

		struct result r;
		r.flag = k;
		if (k)
			strcpy(r.res, res);
		if (k)
			printf("The value decoded is %s  ", res);
		fflush(stdout);
		//n = write(newsd, (struct result*)&r, sizeof(struct result));
	}
	MPI_Finalize();
	return 0;
}