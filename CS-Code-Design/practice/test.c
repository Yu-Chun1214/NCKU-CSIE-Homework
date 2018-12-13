#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef union{
    int integer;
    double floating;
}testunion1;

typedef union{
    int integer1;
    int integer2;
}testunion2;

typedef struct{
    int integer1 : 4;
    int integer2 : 4;
}bitfield;

// 以long long pointer 來存 位置 是因為這樣32bits 可以用 64bits也可以用
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


int main(){
    testunion1 u;
    u.floating = 10;
    u.integer = 6666666666666666666;
    printf("%p\n",&u.floating);
    printf("%p\n",&u.integer);
    printf("%.64lf\n",u.floating);
    printf("%d\n",u.integer);
    OutputBitPattern(&u.integer,8 * sizeof(u.integer));
    OutputBitPattern(&u.floating,64);

    testunion2 u2;
    u2.integer1 = 5;
    u2.integer2 = 10;
    printf("%p\n",&u2.integer1);
    printf("%p\n",&u2.integer2);
    printf("%d\n",u2.integer1);
    printf("%d\n",u2.integer2);

    
}