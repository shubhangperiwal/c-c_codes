//black jack!!!!
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
int min=10;
int top;
typedef struct bj{
	int cash;
	int bet;
	char card[11][2];
	int sum;
	int noc;
}Player;



void hit(Player *p,char c[52][2]);
int checkWinner(Player p[],int k,int n);
void createDeck(char c[52][2]);
void shuffle(char c[52][2]);
void bet(Player p[],int n);
void distribute(Player p[],int n,char c[52][2]);
void calsum(Player *p);
int checksum(Player p);
void display(Player p);
void displayD(Player p);
int main()
{
	char deck[52][2];
	int n,i;
	createDeck(deck);
	
	cout<<"Enter the number of players ";
	cin>>n;
	
	Player p[n+1];
	
	
	cout<<"Each player enter initial amount of cash "<<endl;
	
	for(i=0;i<n;i++)
	{
		cout<<"Player "<<i<<" enter ";
		cin>>p[i].cash;
		cout<<endl;
	}
	
	cout<<"Now lets start playing blackjack !!"<<endl;
	
	while(1)
	{
		
		cout<<endl<<endl;
		shuffle(deck);
		
		bet(p,n);
		
		top=0;
		
		distribute(p,n+1,deck);
		
		cout<<"Dealer cards are ";
		
		displayD(p[n]);
		cout<<endl;
		
		for(i=0;i<n;i++)
		{
			cout<<endl;
			
			cout<<"Cards of player no. "<<i<<" are";
			display(p[i]);
			cout<<endl;
			calsum(&p[i]);
			cout<<"sum is "<<(p[i].sum)<<endl;
			
			int k = 0;
			while(k!=2)
			{
				cout<<endl;
				cout<<"Enter 1 to hit and 2 to continue";
				cin>>k;
				
				if(k==1)
				hit(&p[i],deck);
				cout<<endl;
				
				display(p[i]);
				calsum(&p[i]);
				
				cout<<"sum is "<<(p[i].sum)<<endl;
				if(p[i].sum > 21)
				k=2;
			}
			if(!checksum(p[i]))
				cout<<"You are busted "<<endl;			
		}
		calsum(&p[n]);
		while((p[n].sum) < 17)
		{
			hit(&p[n],deck);
			calsum(&p[n]);
		}
		cout<<endl;
		cout<<"dealer has ";
		display(p[n]);
		cout<<endl;
		cout<<"Dealer sum is "<<(p[n].sum); 
		
		if(!checksum(p[n]))
		{
			cout<<"Dealer busted "<<endl;
		}
		
		for(i=0;i<n;i++)
		{
			if(checkWinner(p,i,n) == 0)
			p[i].cash = p[i].cash + p[i].bet;
			
			else if(checkWinner(p,i,n) == 1)
			{
			p[i].cash = p[i].cash + (2*(p[i].bet));
			cout<<endl;
			cout<<"Player "<<i<<" WON "<<endl;
			cout<<"Player "<<i<<" cash amount remaining = "<<p[i].cash<<endl; 
			
			}
			else
			cout<<"You lost";
		}
		
	}

	
}

void createDeck(char c[52][2])
{
	int i;
	for(i=0;i<13;i++)
	{
		c[i][1] = 'd';
	}
	for(i=13;i<26;i++)
	{
		c[i][1] = 'h';
	}
	for(i=26;i<39;i++)
	{
		c[i][1] = 'c';
	}
	for(i=39;i<52;i++)
	{
		c[i][1] = 's';
	}
	for(i=0;i<52;i++)
	{
		if(i%13 == 0)
		c[i][0] = 'A';
		
		else if(i%13 == 1)
		c[i][0] = '2';
		
		else if(i%13 == 2)
		c[i][0] = '3';
		
		else if(i%13 == 3)
		c[i][0] = '4';
	
		else if(i%13 == 4)
		c[i][0] = '5';
	
		else if(i%13 == 5)
		c[i][0] = '6';
	
		else if(i%13 == 6)
		c[i][0] = '7';
	
		else if(i%13 == 7)
		c[i][0] = '8';
	
		else if(i%13 == 8)
		c[i][0] = '9';
	
		else if(i%13 == 9)
		c[i][0] = '0';
	
		else if(i%13 == 10)
		c[i][0] = 'J';
	
		else if(i%13 == 11)
		c[i][0] = 'Q';
		
		else if(i%13 == 12)
		c[i][0] = 'K';
	
	
	}	
}

void shuffle(char c[52][2])
{
	srand(time(0));
	
	int n = 15;
	int l=0;
	for(int i=0;i<n;i++)
	{
		int k = rand()%52;
		for(int w=k;w<52;w++,l++)
		{
			char t[2];
			t[0] = c[w][0];
			t[1] = c[w][1];
			
			c[w][0] = c[l][0];
			c[w][1] = c[l][1];
			
			c[l][0] = t[0];
			c[l][1]	= t[1]; 
		}
		l=0;
	}
}

void bet(Player p[],int n)
{
	int i=0;
	int bet;
	for(i=0;i<n;i++)
	{
		cout<<"Enter bet amount player "<<i<<endl;
		cin>>bet;
		
		if((p[i].cash) > bet)
			{
				(p[i].bet) = bet;
				p[i].cash = p[i].cash - bet;
			}
		else 
		cout<<"Insufficient cash next hand please "<<endl;
	}		
}

void distribute(Player p[],int n,char c[][2])
{
	int i=0,j=0;
	
	for(i=0;i<=n;i++)
	{
		for(j=0;j<2;j++)
		{
		p[i].card[j][0]=c[top][0];
		p[i].card[j][1]=c[top][1];
		top++;
		}	
		p[i].noc = 2;
	}
}

void calsum(Player *p)
{
	int s = 0;
	int i=0;
	int flag = 0;
	for(i=0;i < (p->noc);i++)
	{
		if(p->card[i][0] == 'K' || p->card[i][0] == 'Q' || p->card[i][0] == 'J' || p->card[i][0] =='0')
		s = s+10;		
		
		else if(p->card[i][0] == 'A')
		{
			s = s+11;
			flag++;
		}
		
		else
		s = s + p->card[i][0] - '0';
	}
	while(s>21 && flag>0)
	{
		s = s-10;
		flag--;
	}
	(p->sum) = s;
	
}

int checksum(Player p)
{
	calsum(&p);
	
	if((p.sum)>21)
	{
		return 0;
	}
	else 
		return 1;
}


void hit(Player *p,char c[52][2])
{
	(p->noc)++;
	top++;
	top = top % 52;
	p->card[p->noc -1][0] = c[top][0];
	p->card[p->noc -1][1] = c[top][1];
}

void display(Player p)
{
	for(int i=0;i<(p.noc);i++)
	{
		
		if(p.card[i][0] == '0')
		{
			cout<<" 10"<<" "<<p.card[i][1];
		}
		else 
			cout<<" "<<p.card[i][0]<<" "<<p.card[i][1];
			
		cout<<"  ";	
	}
	
}

void displayD(Player p)
{
	
		
		if(p.card[0][0] == '0')
		{
			cout<<"10"<<" "<<p.card[0][1];
		}
		else 
			cout<<p.card[0][0]<<" "<<p.card[0][1];
			
		cout<<"  "<<" xxx ";	
	
	
}

int checkWinner(Player p[],int k,int n)
{
	if(p[k].sum > p[n].sum && p[k].sum <= 21 && p[n].sum <= 21)
	return 1;
		
	if(p[k].sum<=21 && p[n].sum>21)
	return 1;
		
	if(p[k].sum > 21)
	return -1;
	
	if(p[n].sum <= 21 && p[n].sum > p[k].sum)
	return -1;
	
	
		
	else 
		return 0;
}
