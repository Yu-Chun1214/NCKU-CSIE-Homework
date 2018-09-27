/************************************************************
 * 學號：E64061151
 * 姓名：林友鈞
 * 編譯方式：gcc -o hw1 hw1.c
 * 執行方式：./hw1 num1 denom1 num2 denom2
 * 程式功能：計算兩分數合，並在最後約分
 * 更新日期：2018/09/27
 ************************************************************/


#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argvs){
    int num1, denom1, num2, denom2, result_num, result_denom;

    // char string to integer
    num1 = atoi(argvs[1]);
    denom1 = atoi(argvs[2]);

    num2 = atoi(argvs[3]);
    denom2 = atoi(argvs[4]);

    // Compute adding fraction
    result_num = num1 * denom2 + num2 * denom1;
    result_denom = denom1 * denom2;

    // Compute the common divisor
    int i;// iterator
    for(i = result_num; result_num % i != 0 || result_denom % i != 0;i--);

    // Answer:
    result_num /= i;
    result_denom /= i;
    printf("%d/%d\n",result_num,result_denom);
    
    return 0;
}