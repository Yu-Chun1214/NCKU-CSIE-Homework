#include <stdio.h>
#include <stdlib.h>

typedef union{
    int integer;
    double floating;
}data;

void OutputBitPattern(long long *x,int bits){
    printf("%d-bit: ",bits);
    long long j = 0;
    int i;
    for(i = bits-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
}

int main(int argc, char * argv[]){
    data flnum;
    flnum.floating = atof(argv[1]);
    OutputBitPattern(&flnum.integer,64);
}