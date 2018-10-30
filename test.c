#include<stdio.h>
#include<stdlib.h>

int check_command_argument(int argc)
{
        if(argc<3)
        {
                printf("Please input N and P from command argument list.\n");
        }
        if(argc>3)
        {
                printf("%d arguments ignored.\n", argc-3);
        }
}

void check_input_NP(int N, int P)
{
        if( N < 1 )
        {
                printf("Given N is illegal.\n");
        }
        if( P < 1 ||P >= 100 )
        {
                printf("Given P is illegal.\n");
        }
}

void input_and_check_answer(int P, int N,int * answer)
{
        // int answer[P];
        int i, k;

        start:
        printf("ans: ");

        for( i = 0 ; i < P; i++)
        {
                scanf("%d", &answer[i]);
        }
        for( k = 0; k < P ; k++)
        {
                if( answer[k] > N || answer[k] <=0)
                {
                        printf("The answer is illegal, please reset the answer.\n");
                        goto start;
                }
        }
}

void input_and_check_guess(int P, int N,int * guess)
{
        // int guess[P];
        int i,k;


        start2:
        printf("guess: ");

        for( i = 0 ; i < P; i++)
        {
                scanf("%d", &guess[i]);
        }
        for( k = 0; k < P ; k++)
        {
                if( guess[k] > N || guess[k] <=0)
                {
                        printf("The guess is illegal, please reset the guess.\n");
                        goto start2;
                }
        }
}

int check_H(int H, int P, int answer[], int guess[])
{
        int i;
        H = 0;
        for( i = 0 ; i < P ; i++)
        {
                if(answer[i] == guess[i])
                {
                        H++;
                }
        }
        return(H);
}

int main(int argc, char*argv[])
{
        int N = atoi(argv[1]);
        int P = atoi(argv[2]);
        int answer[P];
        int guess[P];
        int i, k, m, a, f, t;
        int H, h;

        if(argc>3||argc<3)
                {
                        check_command_argument(argc);
                }
        else
                {
                        if( N < 1 || P < 1 || P >= 100)
                        {
                                check_input_NP(N,P);
                        }else{
                                printf("You set N = %d, P = %d.\n", N,P);
                        }
                }
        input_and_check_answer(P,N,answer);
        input_and_check_guess(P,N,guess);
        h = check_H(H,P,answer,guess);
        printf("%d\n",h);
        return 0;
}