#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float function(float x){
    int y = 0;
    y = 3.0f*pow(x,5)+2.0f*pow(x,4)-5.0f*pow(x,3)-pow(x,2)+7.0f*x-6.0f;
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