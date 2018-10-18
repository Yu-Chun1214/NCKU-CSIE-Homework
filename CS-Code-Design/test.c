#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    while ((getchar()) != '\n');
    scanf("%d",&i);
    printf("i = %d\n",i);
    return 0;
}
