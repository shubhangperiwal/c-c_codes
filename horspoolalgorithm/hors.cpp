
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int st=0;
void creat(int a[],char c[],int l)
{
    int i = 0;
    for(;i<26;i++)
        a[i]=l;
       
    for(i=0;i<l-1;i++)
    {
        a[c[i] - 'a'] = l-i-1; 
    }   
   
}
int main()
{
    int i,j,ind[26];
    char a[100],b[100];
    cout<<"ENter string ";
    gets(a);
    cout<<"Enter string to be searched ";
    gets(b);
    int f[5];
    for(i=0;i<5;i++)
        f[i]=0;
    int l = strlen(a);
    int n = strlen(b);
    i=n-1;
    creat(ind,b,n);
    while(i<l)
    {
        st++;
        if(a[i]==b[n-1])
        {
            int t = i;
            for(j=n-1;j>=0;j--)
            {
               
                if(b[j] == a[t])
                {
                    f[0]++;
                    t--;
                }   
            }
           
            if(f[0] == n)
            {
            f[1] = i;
            f[2] = 1;
            break;
            }
            f[0]=0;
        }
        i = i + ind[a[i] - 'a'];
           
    }
    cout<<endl;
        if(f[2])
        cout<<"string found at "<<f[1] - n + 2;
       
        else
            cout<<"string not found";
   
            cout<<"counter "<<st;   
}






