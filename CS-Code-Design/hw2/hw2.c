#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

double Random(int U, int D){
    return(((double)U - (double)D + 1)*rand() / (double)RAND_MAX + (double)D);
}

int *rnd(int *block, int amount){
    int i; // iterator
    for(int i = 0; i < amount; i++){
        block[i] = (int)Random(1,amount);
        printf("%d\n",block[i]);
    }
    return block;
}

int SetAns(int *array,int P){
    int i = 0;//iterator
    int j = 0;
    int a = 0;
    scanf("ans:");
    for(i = 0; i < P; i++){
        scanf("%d",&array[i]);
    }
    j = scanf("%d",&a);
    
    return 0;
}

int main(int argc, char const *argv[])
{
    int array[100];
    char test[200];
    char bu;
    printf("enter\n");
    int a1;
    scanf("ans:%[^\n]",test);
    char *pch;

    int i = 0,count;
    char *start = test;
    if(*start == ' ')
        for(start = test;*start==' ';start++);
    printf("%s\n",start);
    pch = strtok(start," ");
    while(pch!=NULL){
        array[i] = atoi(pch);
        printf("i = %d  ,  %d\n",i,array[i]);
        pch = strtok(NULL," ");
        i++;
    }
    // printf("%s\n",test);
    count = i;
    for(i = 0;i<count;i++){
        printf("%d\n",array[i]);
    }
}
