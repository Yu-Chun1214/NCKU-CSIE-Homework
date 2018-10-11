#include<stdio.h>
#include<stdlib.h>

int SetData(int data[],const char *choice,int P){
    int i;
    int scf;
    printf("%s",choice);
    for(i = 0; i < P; i++){
        !scanf("%d",&data[i])?scf=1:0;
    }
    while ((getchar()) != '\n');// clear the buffer
    return 1;
}

int Check(int data[],int H,int P){
    int i = 0;
    for(i = 0;i < P; i++){
        if(data[i] < 1 || data[i] > H)
            return 0;
    }
    return 1;
}

void Reset(int data[],int size){
    for(int i = 0;i < size; i++){
        data[i] = 0;
    }
}

void HX(int ans[],int P){
    int ans_match[P];
    int guess[P];
    int guess_match[P];
    int h,x;

    do{
        h = 0;
        x = 0;
        Reset(ans_match,P);
        Reset(guess_match,P);
        SetData(guess,"guess:",P);
        for(int i = 0;i < P; i++){
            if(guess[i] == ans[i]){
                ans_match[i]= guess_match[i] = 1;
                h++;
            }
        }

        for(int i = 0; i < P; i++){
            if(guess_match[i] != 1){
                for(int j = 0; j < P; j++){
                    if(ans[j] == guess[i]&&ans_match[j] != 1)
                        x++;
                }
            }
        }
        printf("%dH%dX\n",h,x);
    }while(h!=P);
}

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    int P = atoi(argv[2]);
    printf("You set N=%d, P=%d\n",N,P);
    
    int ans[100];
    while(!SetData(ans,"ans:",P)||!Check(ans,N,P))
        printf("The answer is  illegal,  please  reset  the  answer.\n");
    HX(ans,P);
    return 0;
}
