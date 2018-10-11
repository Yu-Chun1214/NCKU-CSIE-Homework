
#include<stdio.h>
#include<stdlib.h>
 
int main(int argc, char*argv[])
{
       if(argc<3)
       {
               printf("Please input N and P from command argument list.\n");
               return 2;
       }
 
       if(argc>3)
       {
               printf("%d arguments ignored.\n", argc-3);
       }
 
       int N, P;
 
       N = atoi(argv[1]);
       P = atoi(argv[2]);
 
       if( N < 1 )
       {
               printf("Given N is illegal.\n");
               return 2;
       }
 
       if( P < 1 || P >= 100 )
       {
               printf("Given P is illegal.\n");
               return 3;
       }
 
       printf("You set N = %d, P = %d.\n", N, P);
 
       int answer[P];
       int guess[P];
       int i;
 
       start:
       printf("ans: ");
 
       for( i = 0 ; i < P ; i++)
       {
               scanf("%d", &answer[i]);
               if( answer[i] > N || answer[i] <= 0 )
               {
                       printf("The answer is illegal, please reset the answer.\n");
                       goto start;
               }
       }
 
       start2:
       printf("guess: ");
 
       for( i = 0 ; i < P ; i++)
       {
               scanf("%d", &guess[i]);
               if( guess[i] > N || guess[i] <= 0 )
                       {
                               printf("The guess is illegal, please reset your guess.\n");
                               goto start2;
                       }
       }
 
       int H, X;
       int answer_count[N];
       int guess_count[N];
       int this_number_is, this_number_is2;
 
       H = 0;
 
       for( i = 0 ; i < P ; i++)
       {
               if( answer[i] == guess[i])
               {
                       H++;
               }
       }
 
        //reset
       for( i = 0 ; i < N ; i++ )
       {
               answer_count[i] = 0;
       }
       
       for( i = 0 ; i < P ; ++i )
       {
               int this_number_is = answer[i];
               answer_count[ this_number_is - 1] +=1;
       }
 
       for( i = 0 ; i < N ; ++i )
       {
               guess_count[i] = 0;
       }
 
       for( i = 0 ; i < P ; ++i )
       {
               int this_number_is2 = guess[i];// 假設guess[i] 是10000 那guess_count[10000-1]會造成記憶體錯誤，上面也是一樣
               guess_count[ this_number_is2-1 ] += 1;
       }
 
       int T;
 
       if(answer_count[i] > guess_count[i])//i 是 P
       {
               guess_count[i] = T;// T未初始化 會造成錯誤
       }else{
               answer_count[i] = T;
       }
 
       X = T - H ;
 
       if (H==P)
       {
               printf("Bingo!!\n");
       }else{
               printf("%dH %dX\n", H, X);
               printf("Please answer again.\n");
               goto start2;
       }
 
       printf("The game is over.\n");
       return 0;
}