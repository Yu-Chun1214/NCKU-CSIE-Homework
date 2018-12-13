#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int i;
    for(i = (num1 > num2 ? num2 : num1); i&&((num1%i)||(num2%i));i--);
    // printf("%d\n",i);
    if(!i)printf("%d\n",num1 > num2 ? num1 : num2);
    else printf("%d\n",i);
    return 0;
}
