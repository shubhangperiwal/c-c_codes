#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>

int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z'){
        c[0]='a';
        return inc(c+sizeof(char));
    }  
    c[0]++;
    return 1;
}

int main(){
    
    int i,j,k=0,n=5;
    char *c = (char *)malloc((n+1)*sizeof(char));
   	
    for(i=1;i<=n;i++){
        for(j=0;j<i;j++) c[j]='a';
        c[i]=0;
        do {            
            
	printf("%s\n",c); 
	
	            
        } while(inc(c));
	
    }
	
    free(c);
}



