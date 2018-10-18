#include<stdio.h>

int main(int argc, char const *argv[])
{
    float a = 111;
    int *x;
    x = &a;
    printf("test %d %d\n",x,*x);
    int j = 1;
    for(int i = 31;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
}
