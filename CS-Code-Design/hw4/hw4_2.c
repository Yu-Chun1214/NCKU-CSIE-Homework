/************************************************************
 * 學號：E64061151
 * 姓名：林友鈞
 * 編譯方式：gcc -std=c99 -o hw4_2 hw4_2.c
 * 執行方式：./hw4_2 N P
 * 程式功能：master mind game
 * 更新日期：2018/10/28
 ************************************************************/

#include<stdio.h>
#include<stdlib.h>


int SetData(int data[],const char *choice,int P){
    int i;
    printf("%s",choice);
    for(i = 0; i < P; i++){
        scanf("%d",&data[i]);
    }
    while ((getchar()) != '\n');// clear the buffer
    return 1;
}

int Check(int data[],int H,int P){
    int i = 0;
    for(i = 0;i < P; i++){
        if(data[i] < 1 || data[i] > H)
            return 0; // if it is illegal the function return 0
    }
    return 1;// return 1 finally , means that all number is legal
}

int ComputeH(int *ans_match,int *ans,int *guess_match,int *guess,int P){
    int h = 0;
    for(int i = 0;i < P; i++){
        if(guess[i] == ans[i]){
            // if guess[i] match to ans[i] ans_match[i] and guess_match[i] are assigned 1
            // this assignment is to avoid computing in "x" again
            ans_match[i]= guess_match[i] = 1;
            h++;
        }
    }
    return h;
}

int ComputeX(int *ans_match,int *ans,int *guess_match,int *guess,int P){
    int x = 0;
    for(int i = 0; i < P; i++){
        if(guess_match[i] != 1){
            for(int j = 0; j < P; j++){
                if(ans_match[j] != 1 && ans[j] == guess[i]){
                    ans_match[j] = 1;
                    x++;
                    break;
                }
            }
        }
    }
    return x;
}

int * Zeroing(int data[],int size){ 
    for(int i = 0;i < size; i++){
        data[i] = 0;
    }
    return data;
}

void Reset(int *ans_match,int * guess_match,int * guess,int P){
    Zeroing(ans_match,P); // reset ans_match
    Zeroing(guess_match,P);// reset guess_match
    SetData(guess,"guess: ",P);//input guess
}

void PlayGame(int *ans,int P){
    int guess[P];
    int ans_match[P];
    int guess_match[P];
    int h,x;
    do{
        h = 0;
        x = 0;
        Reset(ans_match,guess_match,guess,P);
        h = ComputeH(ans_match,ans,guess_match,guess,P);
        x = ComputeX(ans_match,ans,guess_match,guess,P);
        printf("%dH %dX\n",h,x);
    }while(h!=P);

}

int * SetAns(int *ans,int P,int N){
    while(!SetData(ans,"ans: ",P)||!Check(ans,N,P))
        printf("The answer is  illegal,  please  reset  the  answer.\n");
    return ans;
}

int main(int argc, char const *argv[])
{
    /* code */
    if(argc < 3){
        printf("Arguments are not enough to do this program\n");
        exit(0);
    }else{
        int N = atoi(argv[1]);
        int P = atoi(argv[2]);
        int ans[100];
        printf("You set N=%d, P=%d\n",N,P);
        SetAns(ans,P,N);
        PlayGame(ans,P);
    }
    return 0;
}
