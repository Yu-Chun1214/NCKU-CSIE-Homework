#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double ComputeExponent(double n,int exp){
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

void OutputBitPattern(long long *x,int bits){
    long long j = 0;
    for(int i = bits-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
}

int inputBitpattern_int_x32(const char *pattern,int bits){
    int s = 1;//positive or negative;
    int sum = 0;
    int i = 0;
    for(int i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            sum += ComputeExponent(2,(bits-1-i));
        }
    }
    // printf("integer = %d\n",sum);
    return(sum);
}

int inputBitpattern_int_x64(const char *pattern,int bits){
    int s = 1;//positive or negative;
    long double sum = 0.0;
    int i = 0;
    for(int i = 0;i < strlen(pattern); i++){
        if(pattern[i] == '1'){
            sum += ComputeExponent(2,(bits-1-i));
        }
    }
    // printf("integer = %.0Lf\n",sum);
    return(sum);
}

// input bitpattern and output the float number
long double inputBitpattern_float(const char *pattern,int bits){
    int s = 1;
    int exponent = 0,i;
    long double mentisa = 0;
    if(pattern[0] == '1') s = -1;
    int exponentbit = 3*(bits/32) + 5;
    for(i = 1; i < exponentbit + 1; i++){
        if(pattern[i] == '1') {
            exponent += 1<<(exponentbit - i);
        }
    }
    // printf("exponent = %d\n",exponent);
    for(i = exponentbit + 1; i < bits; i++){
        if(pattern[i] == '1'){
            mentisa += ComputeExponent(2,exponentbit - i);
        }
    }
    // printf("%Lf\n",(double)s*ComputeExponent(2,(exponent - (bits*28-769)))*(1+mentisa));
    return (long double)s*(long double)ComputeExponent(2,(exponent - (bits*28-769)))*(long double)(1+mentisa);
}

int main(int argc, char *argv[])
{
    
    if(argc < 3){
        double test = 1;
        printf("count is not enough\n");
        // printf("%lf\n",ComputeExponent(2,atoi(argv[1])));
        long long x = 1;
        OutputBitPattern(&x,64);
        return 0;
    }
    switch(atoi(argv[1])){
        int x;
        float y;
        double z;
        long long w;
        long double r;
        case 1 :
            x = inputBitpattern_int_x32(argv[2],32);
            r = inputBitpattern_float(argv[2],32);
            printf("{\"integer\" : \"%d\",\"float\" : \"%LF\"}\n",x,r);
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
            inputBitpattern_int_x64(argv[2],64);
            inputBitpattern_float(argv[2],64);
            break;
        case 5 : 
            w = atoi(argv[2]);
            OutputBitPattern(&w,64);
            break;
        case 6 : 
            z = atof(argv[2]);
            OutputBitPattern(&z,64);
            break;
    }
}
