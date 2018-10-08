#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    char test[200];
    int i = 0;
    i = scanf("ans:%[^\n]",test);
    printf("%s\n",test);
    printf("%d\n",i);
    return 0;
}
