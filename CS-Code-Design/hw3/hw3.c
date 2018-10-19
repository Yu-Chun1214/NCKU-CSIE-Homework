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
    // printf("%lf\n",num);
    return num;
}

void OutputBitPattern_x32(int *x,int bits){
    // printf("%d\n",*x);
    // double test = *x;
    // printf("%lf\n",test);
    int j = 0;
    for(int i = bits-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    printf("\n");
}

void OutputBitpattern_x64(long long *x){
    printf("x = %lld\n",*x);
    long long j;
    for(int i = 64-1;i >= 0; i--){
        j = 1;
        printf("%d",*x&j<<i?1:0);
    }
    // printf("%d",j<<63?1:0);
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
    printf("integer = %d\n",sum);
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
    printf("integer = %.0Lf\n",sum);
    return(sum);
}

// input bitpattern and output the float number
void inputBitpattern_float(const char *pattern,int bits){
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
    for(i = exponentbit + 1; i < bits; i++){
        if(pattern[i] == '1'){
            mentisa += ComputeExponent(2,exponentbit - i);
        }
    }
    printf("%Lf\n",(double)s*ComputeExponent(2,(exponent - 1023))*(1+mentisa));
}



int main(int argc, char *argv[])
{
    
    if(argc < 3){
        double test = 1;
        printf("count is not enough\n");
        // printf("%lf\n",ComputeExponent(2,atoi(argv[1])));
        long long x = 1;
        OutputBitpattern_x64(&x);
        return 0;
    }
    switch(atoi(argv[1])){
        int x;
        float y;
        double z;
        case 1 :
            inputBitpattern_int_x32(argv[2],32);
            inputBitpattern_float(argv[2],32);
        case 2 : 
            x = atoi(argv[2]); 
            OutputBitPattern_x32(&x,32);
        case 3:
            y = atof(argv[2]);
            OutputBitPattern_x32(&y,32);
            break;
        case 4:
            inputBitpattern_int_x64(argv[2],64);
            inputBitpattern_float(argv[2],64);
            break;
        // case 5 : 
        //     x = atoi(argv[2]);
        //     OutputBitpattern_x64(&x,64);
        //     break;
        // case 6 : 
        //     z = atof(argv[2]);
        //     OutputBitpattern_x64(&z,64);
        //     break;
    }
}


