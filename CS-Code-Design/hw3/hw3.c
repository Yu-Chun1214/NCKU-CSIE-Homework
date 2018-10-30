#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 計算指數函數
long double ComputeExponent(double n,int exp){ // n是底數 exp是指數
    int i;
    double num = n;
    if(exp > 0){
        for(i = 1; i < exp; i++){
            num *= n;
        }
    }else{
        for(i = 0; i <= -exp;i++)
            num/=n;
    }
    return num;
}
// 以long long pointer 來存 位置 是因為這樣32bits 可以用 64bits也可以用
void OutputBitPattern(long long *x,int bits){
    printf("%d-bit: ",bits);
    long long j = 0;
    int i;
    for(i = bits-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
}

// inputBitpattern_int_x32 和 inputBitpattern_int_x64 兩個function都是用來計算bit pattern 的整數值
// 兩者最大的不同是 sum 的型別
// 在x32 用int 這樣他就會自動overflow
// 在x64 用long long 也是同樣道理 當sing 是 1時就會自動overflow
int inputBitpattern_int_x32(const char *pattern,int bits){
    int sum = 0;
    int i = 0;
    for(i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            sum += ComputeExponent(2,(bits-1-i));// bit - 1 - i 是因為最右邊的0是0次方所以要減1，這行是在算2的幾次方
        }
    }
    // printf("integer = %d\n",sum);
    return(sum);
}

long long inputBitpattern_int_x64(const char *pattern,int bits){
    long long sum = 0;
    int i = 0;
    for(i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            sum += ComputeExponent(2,(bits-1-i));
        }
    }
    // printf("integer = %.0Lf\n",sum);
    return(sum);
}

// input bitpattern and output the float number
long double inputBitpattern_float(const char *pattern,int bits){
    int s = 1;// s 指的是否是正數
    int exponent = 0,i;// i 是 pattern 的 index
    long double mentisa = 0;
    if(pattern[0] == '1') s = -1;// 如果pattern第一個字是1帶表是負的數
    int exponentbit = 3*(bits/32) + 5; // 32bits 的exponent是8 bits, 64bits的exponentbit是11 bits

    //計算exponentbit部分的值是多少
    for(i = 1; i < exponentbit + 1; i++){
        if(pattern[i] == '1') {
            exponent += 1<<(exponentbit - i);
        }
    }   
    // printf("exponent = %d\n",exponent);

    // 計算mentisa部分的值是多少
    for(i = exponentbit + 1; i < bits; i++){
        if(pattern[i] == '1'){
            mentisa += ComputeExponent(2,exponentbit - i);// mentisa 最左邊的值是-1次方 以此類推 因此是exponentbit - i
        }
    }
    // printf("exponent : %d\n",(exponent - (bits*28-769)));
    // printf("%LF\n",mentisa);
    // printf("%Lf\n",(double)s*ComputeExponent(2,(exponent - (bits*28-769)))*(1+mentisa));
    // 最後的答案是 s(正負號) * 2 ^ (exponent- 127(or 1023)) * (1 + mentisa) 
    return (long double)s*(long double)ComputeExponent(2,(exponent - (bits*28-769)))*(long double)(1+mentisa);
}

int main(int argc, char *argv[])
{
    
    if(argc < 3){
        double test = 1;
        printf("count is not enough\n");
        return 0;
    }
    switch(atoi(argv[1])){
        int x;
        float y;
        double z;
        long long w;
        long double r;
        float * test;
        case 1 :
            x = inputBitpattern_int_x32(argv[2],32);
            test = &x;
            y = inputBitpattern_float(argv[2],32);
            // printf("{\"integer\" : \"%d\",\"float\" : \"%f\"}\n",x,y);
            printf("integer: %d\n",x);
            printf("float: %f\n",*test);
            break;
        case 2 : 
            x = atoi(argv[2]); 
            OutputBitPattern(&x,32);
            break;
        case 3:
            y = atof(argv[2]);
            OutputBitPattern(&y,32);
            break;
        case 4:
            w = inputBitpattern_int_x64(argv[2],64);
            r = inputBitpattern_float(argv[2],64);
            // printf("{\"integer\" : \"%lld\",\"float\" : \"%LF\"}\n",w,r);
            printf("integer: %lld\n",w);
            printf("float: %LF\n",r);
            break;
        case 5 : 
            w = atoll(argv[2]);
            OutputBitPattern(&w,64);
            break;
        case 6 : 
            z = atof(argv[2]);
            OutputBitPattern(&z,64);
            break;
    }
}