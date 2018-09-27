#include<stdio.h>
#include<stdlib.h>

int main(int args,char *argc[]){
    int x;
    int t1 = 2,sg1 = 5;
    int x1,x2;

    // get argument
    if(args > 1){
        x = atoi(argc[1]);
        printf("Enter a dollar amount: %d\n",x);
    }
    else{
        printf("Enter a dollar amount: ");
        scanf("%d",&x);
    }
    
    x1 = x/10;
    x2 = x%10;

    printf("$20 bills : %d\n",x1/t1);
    printf("$10 bills : %d\n",x1%t1);
    printf("$5  bills : %d\n",x2/sg1);
    printf("$1  bills : %d\n",x2%sg1);
    return 0;
}