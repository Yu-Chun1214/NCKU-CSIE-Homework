#include <stdio.h>
#include <stdlib.h>

int gcd(int small, int big){
    // int num = big % small;
    if(!small) return big;
    else{
        return gcd(big%small,small);
    }
}

int main(int argc,char * argv[]){
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[1]);
    printf("%d\n",num1 > num2 ? gcd(num2,num1) : gcd(num1,num2));
}