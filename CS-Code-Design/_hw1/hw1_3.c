#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float function(float x){
    int y = 0;
    y = ((((3*x+2)*x-5)*x-1)*x+7)*x-6;
    return y;
}


int main(int args,char *argc[]){
    int x = 0;
    float ans = 0.0;
    
    // get argument
    if(args > 1){
        x = atoi(argc[1]);
    }

    ans = function(x);
    printf("ans = %d\n",(int)ans);
    return 0;
}