 #include<stdio.h>
#include<stdlib.h>
 
int main(int argc, char*argv[])
{
       //將字串轉為integer:模式六選一
       int mode=atoi(argv[1]);
 
       //case1使用之參數
       float show_float = 0;
       unsigned int* show_int = (unsigned int*)&show_float; //
 
       //給迴圈跑的
       int i;
 
       //case2和case3使用之參數
       int case2 = atoi(argv[2]);
       float case3 = atof(argv[2]);
       unsigned int a = 1;
       unsigned int* case3_prt = (unsigned int*)&case3;
 
       //case4使用之參數
       long long j = 1;
       double show_64bit_double = 0;
       unsigned long long* show_64bit_int = (unsigned long long*)&show_64bit_double;
 
       //case5和case6使用之參數
       long long case5 = atol(argv[2]);
       double case6 = atof(argv[2]);
       unsigned long long b = 1;
       unsigned long long* case6_prt = (unsigned long long*)&case6;
 
       switch(mode)
       {
               //將32-bit pattern轉為integer和float number
               //上面宣告show_float為0，其原本32-bit pattern應為0000...0000
               //用迴圈、or、<<跑，得知輸入的32-bit pattern中哪項為1並存入show_float
               //再將該value以integer、float number形式印出來
               case 1:
                       for(i = 0; i < 32; i++) //偵測32bit中每個bit
                       {
                               if(argv[2][i]=='1') //因為argv[2]是一個char陣列,所以把int 1改成char的形式'1'
                               {
                                       *show_int |= 1<<(31-i);
                               }
                       }
                    //    printf("integer: ");
                    //    printf("%d\n", *show_int);
                    //    printf("float number: ");
                    //    printf("%f\n", show_float);
                       printf("{\"integer\" : \"%d\",\"float\" : \"%f\"}\n",*show_int,show_float);
                       break;
 
               //將integer轉為32-bit pattern
               //a為0000....1，以迴圈和<<一個一個從頭慢慢檢查每個bit是否為1，是則print1否則print0
               case 2:
                    //    printf("32-bit: ");
                       for(i = 0; i <32; i++)
                       {
                               if(case2&a<<31-i)
                               {
                                       printf("1");
                               }else{
                                       printf("0");
                               }
                       }
                       printf("\n");
                       break;
 
               //將float number轉為32-bit pattern
               //與case2做法差不多，只是把字串以atof轉為float number
               case 3:
                    //    printf("32-bit: ");
                       for(i = 0; i <32; i++)
                       {
                               if(*case3_prt&a<<31-i)
                               {
                                       printf("1");
                               }else{
                                       printf("0");
                               }
                       }
                       printf("\n");
                       break;
 
               //將64-bit pattern轉為integer和double number
               //原理和case1一樣
               case 4:
                       for(i = 0; i < 64; i++)
                       {
                               if(argv[2][i]=='1')
                               {
                                       *show_64bit_int |= j<<(63-i);
                               }
                       }
                    //    printf("integer: ");
                    //    printf("%ld\n", *show_64bit_int);
                    //    printf("double number: ");
                    //    printf("%lf\n", show_64bit_double);
                    printf("{\"integer\" : \"%ld\",\"float\" : \"%lf\"}\n",*show_64bit_int,show_64bit_double);
                       break;
 
               //將integer轉為64-bit pattern
               //原理同case2
               case 5:
                    //    printf("64-bit: ");
                       for(i = 0; i < 64; i++)
                       {
                               if(case5&b<<63-i)
                               {
                                       printf("1");
                               }else{
                                       printf("0");
                               }
                       }
                       printf("\n");
                       break;
 
               //將double number轉為64-bit pattern
               //原理同case3
               case 6:
                    //    printf("64-bit: ");
                       for(i = 0; i <64; i++)
                       {
                               if(*case6_prt&b<<63-i)
                               {
                                       printf("1");
                               }else{
                                       printf("0");
                               }
                       }
                       printf("\n");
                       break;
       }
       return 0;
}
