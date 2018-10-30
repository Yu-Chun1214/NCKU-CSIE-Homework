#include<stdio.h>
#include<stdlib.h>


// input function
int SetData(int data[],const char *choice,int P){
    int i;
    int scf;
    printf("%s",choice);
    for(i = 0; i < P; i++){
        scanf("%d",&data[i]);
    }
    while ((getchar()) != '\n');// clear the buffer
    return 1;
}


// Check if input is legal or not
int Check(int data[],int H,int P){
    int i = 0;
    for(i = 0;i < P; i++){
        if(data[i] < 1 || data[i] > H)
            return 0; // if it is illegal the function return 0
    }
    return 1;// return 1 finally , means that all number is legal
}


// array initialize
void Reset(int data[],int size){ 
    for(int i = 0;i < size; i++){
        data[i] = 0;
    }
}


// compute h and x
void HX(int ans[],int P){
    int ans_match[P];
    int guess[P];
    // ans_match and guess_match are set to record match to avoid computing in "x" again.
    int guess_match[P];
    int h,x;

    do{
        h = 0;
        x = 0;
        Reset(ans_match,P); // reset ans_match
        Reset(guess_match,P);// reset guess_match
        SetData(guess,"guess:",P);//input guess
        for(int i = 0;i < P; i++){
            if(guess[i] == ans[i]){
                // if guess[i] match to ans[i] ans_match[i] and guess_match[i] are assigned 1
                // this assignment is to avoid computing in "x" again
                ans_match[i]= guess_match[i] = 1;
                h++;
            }
        }

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
        printf("%dH%dX\n",h,x);
    }while(h!=P);// do until h == P
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
