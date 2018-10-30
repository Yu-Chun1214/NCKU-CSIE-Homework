/************************************************************
 * 學號：E64061151
 * 姓名：林友鈞
 * 編譯方式：gcc -std=c99 -o hw4_3 hw4_3.c
 * 執行方式：./hw4_2 mode input
 * 程式功能：transfer bit pattern to number or transfer number to bit pattern
 * 更新日期：2018/10/28
 ************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 以long long pointer 來存 位置 是因為這樣32bits 可以用 64bits也可以用
int OutputBitPattern(long long *x,int bits){
    printf("%d-bit: ",bits);
    long long j = 0;
    int i;
    for(i = bits-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
    return 0;
}

// inputBitpattern_int_x32 和 inputBitpattern_int_x64 兩個function都是用來計算bit pattern 的整數值
// 兩者最大的不同是 sum 的型別
// 在x32 用int 這樣他就會自動overflow
// 在x64 用long long 也是同樣道理 當sign 是 1時就會自動overflow
int inputBitpattern_int_x32(const char *pattern,int bits){
    int sum = 0;
    int i = 0;
    int j = 1;
    for(i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            // sum += ComputeExponent(2,(bits-1-i));// bit - 1 - i 是因為最右邊的0是0次方所以要減1，這行是在算2的幾次方
            sum += j << (bits-1-i);
        }
    }
    // printf("integer = %d\n",sum);
    return(sum);
}

long long inputBitpattern_int_x64(const char *pattern,int bits){
    long long sum = 0;
    int i = 0;
    long long j = 1;
    for(i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            // sum += ComputeExponent(2,(bits-1-i));
            sum += j << (bits - 1 - i);
        }
    }
    // printf("integer = %.0Lf\n",sum);
    return(sum);
}

void Mode(int mode,const char * input_data){
    switch(mode){
        int x;
        float y;
        double z;
        long long w;
        long double r;
        double * test2;
        float * test;
        case 1 :
            x = inputBitpattern_int_x32(input_data,32);
            test = &x;
            // printf("{\"integer\" : \"%d\",\"float\" : \"%f\"}\n",x,*test);
            printf("integer: %d\n",x);
            printf("float: %f\n",*test);
            break;
        case 2 : 
            x = atoi(input_data); 
            OutputBitPattern(&x,32);
            break;
        case 3:
            y = atof(input_data);
            OutputBitPattern(&y,32);
            break;
        case 4:
            w = inputBitpattern_int_x64(input_data,64);
            test2 = &w;
            // printf("{\"integer\" : \"%lld\",\"float\" : \"%lf\"}\n",w,*test2);
            printf("integer: %lld\n",w);
            printf("float: %lf\n",*test2);
            break;
        case 5 : 
            w = atoll(input_data);
            OutputBitPattern(&w,64);
            break;
        case 6 : 
            z = atof(input_data);
            OutputBitPattern(&z,64);
            break;
    }
}

int main(int argc, char *argv[])
{
    
    if(argc < 3){
        double test = 1;
        printf("count is not enough\n");
        return 0;
    }
    else Mode(atoi(argv[1]),argv[2]);
    return 0;
}