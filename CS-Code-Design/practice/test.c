#include <stdio.h>
#include <stdlib.h>

void fibo_row(int **a,int col,int num){
    for(int i = num + 2; i < 10; i++){
        a[col][i] = a[col][i - 1] + a[col][i - 2];
    }
}

void fibo_col(int **a,int col,int num){
    for(int i = num + 2; i < 10; i++){
        a[i][col] = a[i - 1][col] + a[i - 2][col];
    }
}

int main(){
    int ** a = (int **)malloc(10 * sizeof(int *));
    for(int i = 0; i < 11; i++)
        a[i] = (int *)malloc(10 * sizeof(int));

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            a[i][j] = 1;
    
    for(int i = 0; i < 10; i++){
        fibo_row(a,i,i);
        fibo_col(a,i,i); 
    } 

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            printf("%5d",a[i][j]);
        printf("\n");
    }
}