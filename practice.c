#include<stdio.h>

int abs32(int a){
    int y = a >>31;
    printf("y = %d\n",y);
    return (a ^ y) ;
}

int main(int argc, char const *argv[])
{
    printf("%d\n",abs32(-5));
    return 0;
}
