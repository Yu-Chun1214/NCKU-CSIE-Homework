#include<stdio.h>
// #include<string.h>
#include<stdlib.h>
#include<math.h>

int main(int args,char *argc[]){
    int r = 10;
    float V = 0.0;
    V = (4.0f/3.0f)*M_PI*pow(r,3);
    printf("%lf\n",V);
    return 0;
}