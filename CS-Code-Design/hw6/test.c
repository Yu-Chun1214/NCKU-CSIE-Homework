// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #define M 9100
// #define N 20
// int main(int argc, char*argv[])
// {
//     FILE *hw6 = fopen(argv[1],"r");
//     if(hw6!= NULL)
//     {
//         printf("success\n");
//         char f1[M][N], f2[M][N], f5[M][N];
//         int f3[M][N], f3_2[M][N], f4[M][N], f4_2[M][N];
//         int i,j;
//         int total = 0;
//         for( i = 0 ; i <= M ;i++)
//         {
//         //         for( j = 0 ; j <= N ; j++)
//         //     {
//                 if(EOF!=fscanf(hw6, "%s %s %d : %d %d : %d %s", f1[i], f2[i], &f3[i][0], &f3[i][1], &f4[i][0], &f4[i][1], f5[i]))
//                 {
//                         total++;
//                         // printf("%s %s %d : %d %d : %d %s\n", f1[i], f2[i], f3[i][j], f3_2[i][j], f4[i][j], f4_2[i][j], f5[i]);
//                 }
//                 else
//                         break;
//         //     }
//         }
//         printf("%d\n", total);

//         int count1 = 0;
//         int k;
//         for(i=0;i<total;i++)
//         {
//                 int num = 0;
//             for(k = 0; k < i; k++)
//             {
//                 // printf("i = %d,k = %d\n",i,k);
//                 // printf("f1[i] : %s\nf1[k] : %s\n",f1[i],f1[k]);
//                 if(!strcmp(f1[i],f1[k])){
//                         num = 1;
//                         // printf("The Same !!\n");
//                         break;
//                 }
//                 // printf("-------------\n");
//             }
//             if(!num)
//                 count1++;
//         // printf("%s\n",f1[i]);
//         }

//         printf("%d\n", count1);
//         fclose(hw6);
//         }else{
//                 printf("Could not open the file.\n");
//         }
//     return 0;
// }

#include <string.h>
#include <stdio.h>

int main(){
        printf("%d\n",'b');
}