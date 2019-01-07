#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    short int ip[16];
    short int length;
}ipv6;

char * OutputBitPattern(long long *x,int bits){
    // printf("%d-bit: ",bits);
    long long j = 0;
    int i;
    int ch_it = 0;
    char * bp = (char *)malloc((bits + 1) * sizeof(char));
    for(i = bits-1;i >= 0; i--){
        j = 1;
        // printf("%d",*x&j<<i?1:0);
        bp[ch_it] = *x&j<<i?'1':'0';
        ch_it++;
    }
    // printf("%s\n",bp);
    bp[bits + 1] = '\0';
    // printf("\n");
    return bp;
}

int main(int argc, char const *argv[])
{
    FILE * file = fopen("file.txt","r");
    short int a[5];
    ipv6 ips[10];
    int i = 0;
    while(EOF != fscanf(file,"%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x/%2d",&ips[i].ip[0],&ips[i].ip[1],&ips[i].ip[2],&ips[i].ip[3],&ips[i].ip[4],&ips[i].ip[5],&ips[i].ip[6],&ips[i].ip[7],&ips[i].ip[8],&ips[i].ip[9],&ips[i].ip[10],&ips[i].ip[11],&ips[i].ip[12],&ips[i].ip[13],&ips[i].ip[14],&ips[i].ip[15],&ips[i].length)){
        // fscanf(file,"%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x/%2d",&ips[i].ip[0],&ips[i].ip[1],&ips[i].ip[2],&ips[i].ip[3],&ips[i].ip[4],&ips[i].ip[5],&ips[i].ip[6],&ips[i].ip[7],&ips[i].ip[8],&ips[i].ip[9],&ips[i].ip[10],&ips[i].ip[11],&ips[i].ip[12],&ips[i].ip[13],&ips[i].ip[14],&ips[i].ip[15],&ips[i].length);
        printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x/%02d\n",ips[i].ip[0],ips[i].ip[1],ips[i].ip[2],ips[i].ip[3],ips[i].ip[4],ips[i].ip[5],ips[i].ip[6],ips[i].ip[7],ips[i].ip[8],ips[i].ip[9],ips[i].ip[10],ips[i].ip[11],ips[i].ip[12],ips[i].ip[13],ips[i].ip[14],ips[i].ip[15],ips[i].length);
        i++;
        
    }
    int count = i;
    // printf("%s\n",OutputBitPattern(&ips[0].ip[0],8));
    for(i = 0; i < count; i++){
        printf("%s%s:",OutputBitPattern(&(ips[i].ip[0]),8),OutputBitPattern(&(ips[i].ip[1]),8));
        for(int j = 2; j < 16; j+=2){
            printf(":%s%s",OutputBitPattern(&(ips[i].ip[j]),8),OutputBitPattern(&(ips[i].ip[j+1]),8));
        }
        printf("/");
        for(int j = 0; j < ips[i].length;j++)
            printf("1");
        for(int j = 0; j < 128 - ips[i].length; j++)
            printf("0");
        printf("\n");
    }
}
