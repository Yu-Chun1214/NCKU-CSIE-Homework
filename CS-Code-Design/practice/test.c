#include <stdio.h>
#include <stdlib.h>

void fibo_row(int **a,int col,int num){
    a[col][num] = a[col][num + 1] = 1;
    for(int i = num + 2; i < 10; i++){
        a[col][i] = a[col][i - 1] + a[col][i - 2];
    }
}

void fibo_col(int **a,int col,int num){
    a[num][col] = a[num + 1][col] = 1;
    for(int i = num + 2; i < 10; i++){
        a[i][col] = a[i - 1][col] + a[i - 2][col];
    }
}

int main(){
    int ** a = (int **)malloc(11 * sizeof(int *));
    for(int i = 0; i < 11; i++)
        a[i] = (int *)malloc(11 * sizeof(int));

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            a[i][j] = 0;
    
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